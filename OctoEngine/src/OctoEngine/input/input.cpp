#include "input.h"
#include "../core/window.h"

namespace octo {
	namespace input {

		Input* Input::INSTANCE = nullptr;

		Input::Input(){
			// initialize all the buttons and keys to false
			memset(m_Keys, false, MAX_KEYBOARD_KEYS);
			memset(m_MouseButtons, false, MAX_MOUSE_BUTTONS);
		}

		Input::~Input()
		{
			//TODO:  implement a static descructor method
		}

		void Input::init(const octo::core::Window& window)
		{
			if (Input::INSTANCE == nullptr)
				Input::INSTANCE = new Input();

			// Register input callbacks
			glfwSetKeyCallback((GLFWwindow*)window.GetWindowID(), Input::key_callback);
			glfwSetMouseButtonCallback((GLFWwindow*)window.GetWindowID(), &Input::mouse_button_callback);
			glfwSetCursorPosCallback((GLFWwindow*)window.GetWindowID(), &Input::cursor_position_callback);
		}

		void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Input::INSTANCE->m_Keys[key] = action;
		}

		void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			//printf("MOUSE X=%f Y=%f\n", xpos, ypos);
			Input::INSTANCE->m_MousePos.x = xpos;
			Input::INSTANCE->m_MousePos.y = ypos;
		}

		void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			//printf("MOUSE BUTTON=%D ACTION=%d MODS=%d\n", button, action, mods);
			Input::INSTANCE->m_MouseButtons[button] = action;
		}

		bool Input::getKey(int key)
		{
			if (key >= 0 && key < MAX_KEYBOARD_KEYS)
			return  (Input::INSTANCE->m_Keys[key] != GLFW_RELEASE);

			return false;
		}

		bool Input::getKeyDown(int key)
		{
			if (key >= 0 && key < MAX_KEYBOARD_KEYS)
			{
				return (Input::INSTANCE->m_Keys[key] == GLFW_PRESS);
			}

			return false;
		}

		// Mouse
		glm::vec2 Input::getMousePos()
		{
			return Input::INSTANCE->m_MousePos;
		}

		bool Input::getMouseButton(int key)
		{
			if (key >= 0 && key < MAX_MOUSE_BUTTONS)
			return  Input::INSTANCE->m_MouseButtons[key] != GLFW_RELEASE;

			return false;
		}

		bool Input::getMouseButtonDown(int key)
		{
			if (key >= 0 && key < MAX_MOUSE_BUTTONS)
			return  Input::INSTANCE->m_MouseButtons[key] == GLFW_PRESS;

			return false;
		}

	}
}