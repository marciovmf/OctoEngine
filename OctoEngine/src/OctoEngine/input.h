#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>


namespace octo {

	namespace core { class Window; }

	namespace input {

		class Input
		{

#define MAX_KEYBOARD_KEYS 1024
#define MAX_MOUSE_BUTTONS 8
		private:
			static Input* INSTANCE;
			int m_Keys[MAX_KEYBOARD_KEYS];
			int m_MouseButtons[MAX_MOUSE_BUTTONS];
			glm::dvec2 m_MousePos;

		public:
			static void init(const octo::core::Window& window);
			// keyboard input
			static bool getKey(int key);
			//static bool getKeyUp(int key);
			static bool getKeyDown(int key);

			// Mouse
			static glm::vec2 getMousePos();
			static bool getMouseButton(int key);
			//static bool getMouseButtonUp(int key);
			static bool getMouseButtonDown(int key);

			//TODO: Joystick input

		private:
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			static  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		private:
			Input();
			~Input();
		};
	}
}