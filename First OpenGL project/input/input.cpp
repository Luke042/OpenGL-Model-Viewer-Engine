#include "../engine/engine.h"
#include "input.h"

Engine engine;

static float bottom_left_x = -0.5f;
static float bottom_left_y = -0.5f;

static float bottom_right_x = 0.5f;
static float bottom_right_y = -0.5f;

static float top_x = 0.0f;
static float top_y = 0.5f;

int Input::KeyPressed(GLFWwindow* window, int key) {
	return glfwGetKey(window, key);
}

void Input::UpdateInput(Engine* engine) {
	glm::mat4 camera = engine->GetCamera();
	GLFWwindow* window = engine->GetWindow();
	/*
	if (KeyPressed(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		engine->EnableCursor(window);
	else
		engine->EnableCursor(window);*/

	if (KeyPressed(window, GLFW_KEY_S) == GLFW_PRESS ||
		KeyPressed(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera = glm::translate(camera, glm::vec3(0.0f, 0.0f, -engine->speed * engine->delta_time));
	}

	if (KeyPressed(window, GLFW_KEY_W) == GLFW_PRESS ||
		KeyPressed(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera = glm::translate(camera, glm::vec3(0.0f, 0.0f, +engine->speed * engine->delta_time));
	}

	if (KeyPressed(window, GLFW_KEY_D) == GLFW_PRESS ||
		KeyPressed(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		camera = glm::translate(camera, glm::vec3(-engine->speed * engine->delta_time, 0.0f, 0.0f));
	}

	if (KeyPressed(window, GLFW_KEY_A) == GLFW_PRESS ||
		KeyPressed(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		camera = glm::translate(camera, glm::vec3(+engine->speed * engine->delta_time, 0.0f, 0.0f));
	}

	if (KeyPressed(window, GLFW_KEY_SPACE)) {
		camera = glm::translate(camera, glm::vec3(0.0f, -engine->speed * engine->delta_time, 0.0f));
	}

	if (KeyPressed(window, GLFW_KEY_LEFT_SHIFT)) {
		camera = glm::translate(camera, glm::vec3(0.0f, +engine->speed * engine->delta_time, 0.0f));
	}

	engine->camera = camera;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (KeyPressed(window, GLFW_KEY_M) == GLFW_PRESS) {
		audio.Mute();
	}

	static bool toggle = false;
	int state = KeyPressed(window, GLFW_KEY_F);
	if (state == GLFW_PRESS && !toggle) {
		engine->wireframe = !engine->wireframe;
	}
	toggle = (state == GLFW_PRESS);
}

void Input::MouseCallback(GLFWwindow* window, double x, double y) {
	ImGui_ImplGlfw_CursorPosCallback(window, x, y);
}