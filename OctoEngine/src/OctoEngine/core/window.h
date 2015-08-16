#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace octo {
	namespace core {

		class Window
		{
		private:
			GLFWwindow* m_Window;
			int m_Width;
			int m_Height;
		public:
			Window(int width, int height, const std::string& title);
			inline int getWidth() const { return m_Width; }
			inline int getHeight() const { return m_Height; }
			inline int shouldClose() const { return glfwWindowShouldClose(m_Window); }
			void update();
			void clear() const;
			void setClearColor(const glm::vec3& color) const;
			~Window();
		private:
			static void errorCallback(int error, const char *description);
			Window(Window& other){};
			Window& operator=(Window& other){};
		};
	}
}