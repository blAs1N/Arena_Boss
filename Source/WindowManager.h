#pragma once

#include <cstdint>
#include <GLFW/glfw3.h>
#include <string>
#include "Vector2.h"

namespace ArenaBoss
{
	enum class ScreenMode
	{
		Window,
		FullScreen,
		Borderless
	};

	class WindowManager final
	{
	public:
		WindowManager(const char* inTitle, uint32_t inWidth,
			uint32_t inHeight, ScreenMode inScreenMode);

		WindowManager(const WindowManager&) = delete;
		WindowManager(WindowManager&&) = delete;

		WindowManager& operator=(const WindowManager&) = delete;
		WindowManager& operator=(WindowManager&&) = delete;

		~WindowManager();

		inline void SwapBuffer() noexcept { glfwSwapBuffers(window); }

		const std::string& GetTitle() const noexcept { return title; }

		inline uint32_t GetWidth() const noexcept { return GetSize().x; }
		inline uint32_t GetHeight() const noexcept { return GetSize().y; }

		Math::UintVector2 GetSize() const noexcept;

		inline ScreenMode GetScreenMode() const noexcept
		{
			return screenMode;
		}

		inline void SetTitle(const std::string& inTitle) noexcept
		{
			title = inTitle;
			glfwSetWindowTitle(window, title.c_str());
		}

		inline void SetSize(uint32_t width, uint32_t height) noexcept
		{
			glfwSetWindowSize(window, width, height);
		}

		void SetScreenMode(ScreenMode inScreenMode) noexcept;

	private:
		GLFWwindow* window;
		std::string title;
		ScreenMode screenMode;
	};
}