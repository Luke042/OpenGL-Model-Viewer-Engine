#include "../engine/engine.h"
#include "../gui/gui.h"
#include "../input/input.h"
#include "../shaderLoader/shaderLoader.h"
#include "../renderer/renderer.h"
#include "../mesh/mesh.h"

int main() {
	Engine engine;
	Input input;
	Renderer renderer(engine);
	Mesh mesh;

	engine.Init();
	GLFWwindow* window = engine.GetWindow();
	GUI::InitImgui(window);

	mesh.LoadTextureFromFile("ak-47.jpg", engine);
	mesh.MakeMesh("Ak_47\\Ak-47.obj");
	//mesh.MakeObjMesh("Remington_870\\shotgun.obj");

	//engine.DisableCursor(window);

	glfwSetCursorPosCallback(engine.GetWindow(), engine.MouseCallback);

	while (!engine.WindowShouldClose(window)) {
		glfwPollEvents();
		engine.speed = engine.GetSpeed();
		engine.delta_time = engine.startClock();

		engine.Clear();
		engine.UpdateViewPort(window);
		input.UpdateInput(&engine);
		glfwSetCursorPosCallback(window, input.MouseCallback);
		engine.UpdateMVP();

		mesh.Draw(engine.shaderProgram, engine);
		GUI::Render(engine, window);

		engine.SwapBuffers(window);
	}

	engine.Terminate();
	return 0;
}