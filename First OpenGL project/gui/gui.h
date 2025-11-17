#pragma once
#include "../engine/engine.h"

namespace GUI {
	void InitImgui(GLFWwindow* window);
	void NewFrame();
	void CreateContext(Engine& engine);
	void RenderContext(GLFWwindow* window);
	void Render(Engine& engine, GLFWwindow* window);

	static float width = 300, height = 250;
}