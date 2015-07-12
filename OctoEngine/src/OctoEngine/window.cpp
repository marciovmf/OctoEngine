#include "window.h"
#include <iostream>

namespace octo {
	namespace core {

#define MAJOR_GL_VERSION 3
#define MINOR_GL_VERSION 2

		Window::Window(int width, int height, const std::string& title)
			: m_Width(width), m_Height(height)
		{
			
			// start GL context and O/S window using the GLFW helper library
			if (!glfwInit()) {
				fprintf(stderr, "ERROR: could not start GLFW3\n");
				glfwTerminate();
				return;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_GL_VERSION);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_GL_VERSION);
			//glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
			glfwSetErrorCallback(Window::errorCallback);
			// Create the window
			m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

			if (!m_Window) {
				fprintf(stderr, "ERROR: could not open window with GLFW3\n");
				glfwTerminate();
			}
			glfwMakeContextCurrent(m_Window);

			// start GLEW extension handler
			glewExperimental = GL_TRUE;
			glewInit();

			// get version info
			const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
			const GLubyte* version = glGetString(GL_VERSION); // version as a string
			printf("Renderer: %s\n", renderer);
			printf("OpenGL version supported %s\n", version);
		}

		Window::~Window()
		{
			glfwMakeContextCurrent(NULL);
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::setClearColor(const glm::vec3& color) const
		{
			glClearColor((GLclampf)color.r, (GLclampf)color.g, (GLclampf)color.b, 0);
		}

		void Window::update()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		void Window::errorCallback(int error, const char *description)
		{
			std::cerr << "GLFW error " << error << ": " << description << std::endl;
		}
	}
}