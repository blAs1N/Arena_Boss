#pragma once

#include <string>
#include <vector>

namespace ArenaBoss
{
	class Scene
	{
	public:
		Scene() = delete;
		
		Scene(const Scene&) = delete;
		Scene(Scene&&) = default;

		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) = default;

		~Scene() = default;

		void Init();
		bool Update();
		void Release();

	private:
		friend bool operator==(const Scene& lhs, const Scene& rhs);
		friend bool operator<(const Scene& lhs, const Scene& rhs);

		friend bool operator==(const Scene& lhs, const std::string& rhs);
		friend bool operator<(const Scene& lhs, const std::string& rhs);

		friend bool operator==(const std::string& lhs, const Scene& rhs);
		friend bool operator<(const std::string& lhs, const Scene& rhs);

		friend class SceneManager;
		Scene(const std::string& inName);

		std::string name;
		std::vector<class Entity> entities;
	};

	inline bool operator==(const Scene& lhs, const std::string& rhs) { return lhs.name == rhs; }
	inline bool operator!=(const Scene& lhs, const std::string& rhs) { return !(lhs == rhs); }
	inline bool operator<(const Scene& lhs, const std::string& rhs) { return lhs.name < rhs; }
	inline bool operator>(const Scene& lhs, const std::string& rhs) { return rhs < lhs; }
	inline bool operator<=(const Scene& lhs, const std::string& rhs) { return !(rhs < lhs); }
	inline bool operator>=(const Scene& lhs, const std::string& rhs) { return !(lhs < rhs); }

	inline bool operator==(const std::string& lhs, const Scene& rhs) { return lhs == rhs.name; }
	inline bool operator!=(const std::string& lhs, const Scene& rhs) { return !(lhs == rhs); }
	inline bool operator<(const std::string& lhs, const Scene& rhs) { return lhs < rhs.name; }
	inline bool operator>(const std::string& lhs, const Scene& rhs) { return rhs < lhs; }
	inline bool operator<=(const std::string& lhs, const Scene& rhs) { return !(rhs < lhs); }
	inline bool operator>=(const std::string& lhs, const Scene& rhs) { return !(lhs < rhs); }

	inline bool operator==(const Scene& lhs, const Scene& rhs) { return lhs.name == rhs.name; }
	inline bool operator!=(const Scene& lhs, const Scene& rhs) { return !(lhs == rhs); }
	inline bool operator<(const Scene& lhs, const Scene& rhs) { return lhs.name < rhs.name; }
	inline bool operator>(const Scene& lhs, const Scene& rhs) { return rhs < lhs; }
	inline bool operator<=(const Scene& lhs, const Scene& rhs) { return !(rhs < lhs); }
	inline bool operator>=(const Scene& lhs, const Scene& rhs) { return !(lhs < rhs); }
}