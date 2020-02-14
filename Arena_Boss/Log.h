#pragma once

#include <SDL2/SDL.h>
#include <utility>

template <class... Args>
void Log(const char* format, Args&&... args)
{
	SDL_Log(format, std::forward<Args>(args)...);
}