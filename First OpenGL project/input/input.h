#pragma once
#include "../includes/GLFW/glfw3.h"

class Input {
public:
	int KeyPressed(GLFWwindow* window, int key);
	void UpdateInput(Engine* engine);
	static void MouseCallback(GLFWwindow* window, double x, double y);
};