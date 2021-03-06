#include "window.h"
#include <iostream>

namespace octo
{
	namespace core
	{
#define MAJOR_GL_VERSION 3
#define MINOR_GL_VERSION 2

		//Window::Window(int width, int height, const std::string& title)
		Window::Window(int width, int height, const std::string& title, int monitorID)
			: m_Width(width), m_Height(height)
		{
			

			// start GL context and O/S window using the GLFW helper library
			if (!glfwInit())
			{
				fprintf(stderr, "ERROR: could not start GLFW3\n");
				glfwTerminate();
				return;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_GL_VERSION);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_GL_VERSION);
			glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
			glfwSetErrorCallback(Window::errorCallback);

			// Create the window

			int monitorCount;
			GLFWmonitor** monitorList = glfwGetMonitors(&monitorCount);

			if (monitorID > monitorCount - 1)
			{
				std::cerr << "Monitor " << monitorID << " is not a valid monitor." << std::endl;
				monitorID = -1;
			}

			m_Window = glfwCreateWindow(width, height, title.c_str(),
			                            ((monitorID > -1) ? monitorList[monitorID] : NULL),
			                            NULL);

			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (!m_Window)
			{
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
			printf("Running in %s .\n", (monitorID > -1 ? "FullScreen mode" : "Windowd mode"));
		}

		Window::~Window()
		{
			glfwMakeContextCurrent(NULL);
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		void Window::clear() const
		{
			glEnable(GL_DEPTH_TEST);
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

		void Window::errorCallback(int error, const char* description)
		{
			std::cerr << "GLFW error " << error << ": " << description << std::endl;
		}
	}
}
