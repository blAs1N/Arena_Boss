#define _CRT_SECURE_NO_WARNINGS

#include "ConfigFile.h"
#include <algorithm>
#include <cassert>
#include <exception>
#include <fstream>
#include "Log.h"

#include <iostream>

namespace ArenaBoss
{
    const std::string* ConfigSection::operator[](const std::string& key) const
    {
        const auto it = data.find(key);
        if (it != data.cend())
            return &(it->second);
        return nullptr;
    }

    namespace
    {
        std::string TrimInline(const std::string& s)
        {
            auto begin = s.find_first_not_of(" \t");
            auto end = s.find_last_not_of(" \t");
            if (begin == std::string::npos || end == std::string::npos || begin > end)
                return "";
            return s.substr(begin, end - begin + 1);
        }
    }

    void ConfigFile::LoadFromFile(const std::string& fileName)
    {
        if (state != State::Uninitialized)
            throw std::exception{ "Not initialized" };

        try
        {
            std::ifstream fin("Config\\" + fileName);
            if (!fin) throw std::exception{ std::strerror(errno) };

            std::string section{ "Global" };
            std::map<std::string, std::string> sectionMap;
            std::string line;

            while (std::getline(fin, line))
            {
                if ((line = TrimInline(line)).empty() || line[0] == '#')
                    continue;

                if (line[0] == '[')
                {
                    const auto end = line.rfind(']');
                    if (end == std::string::npos || end == 1)
                        throw;

                    map.emplace(std::make_pair(section, ConfigSection{ sectionMap }));
                    section = TrimInline(line.substr(1, end - 1));
                }
                else
                {
                    const auto eq = line.find('=');
                    if (eq == std::string::npos || eq == 0 || eq == line.length() - 1)
                        throw;

                    const auto left = TrimInline(line.substr(0, eq));
                    const auto right = TrimInline(line.substr(eq + 1));

                    if (left.empty() || right.empty())
                        throw;

                    sectionMap.emplace(std::make_pair(left, right));
                }
            }

            map.emplace(std::make_pair(section, ConfigSection{ sectionMap }));
            state = State::Available;
        }
        catch (std::exception& e)
        {
            map.clear();
            state = State::Error;
            throw e;
        }
    }

    void ConfigFile::Clear()
    {
        map.clear();
        state = State::Uninitialized;
    }

    const std::string* ConfigFile::operator()(const std::string& sectionName, const std::string& keyName) const
    {
        const auto section = GetSection(sectionName);
        if (!section) return nullptr;
        return (*section)[keyName];
    }

    const ConfigSection* ConfigFile::GetSection(const std::string& section) const
    {
        const auto it = map.find(section);
        if (it != map.cend())
            return &(it->second);
        return nullptr;
    }
}