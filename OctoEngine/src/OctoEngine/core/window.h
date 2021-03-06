#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../input/input.h"

namespace octo
{
	namespace core
	{
		class Window
		{
			friend class octo::input::Input;

		private:
			GLFWwindow* m_Window;
			int m_Width;
			int m_Height;
			int m_forceCloseWindow = 0;
		public:
			//Window(int width, int height, const std::string& title);
			Window(int width, int height, const std::string& title, int monitorID = -1);

			inline int getWidth() const
			{
				return m_Width;
			}

			inline int getHeight() const
			{
				return m_Height;
			}

			inline int shouldClose() const
			{
				return glfwWindowShouldClose(m_Window) | m_forceCloseWindow;
			}

			inline void forceCloseWindow()
			{
				m_forceCloseWindow = 1;
			}

			void update();
			void clear() const;
			void setClearColor(const glm::vec3& color) const;
			~Window();
		private:
			static void errorCallback(int error, const char* description);

			Window(Window& other)
			{
			};

			Window& operator=(Window& other)
			{
			};
		};
	}
}
