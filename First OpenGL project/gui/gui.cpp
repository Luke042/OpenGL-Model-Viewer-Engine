#include "gui.h"

void GUI::InitImgui(GLFWwindow* window) {
	static ImGuiIO& io = ImGui::GetIO();

	IMGUI_CHECKVERSION();
	std::cout << "ImGui Version: " << ImGui::GetVersion() << "\n";
	ImGui::CreateContext();
	(void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	std::cout << "Initalised ImGui.\n";

	ImGui::SetNextWindowSize({ width, height });
}

void GUI::NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGuizmo::BeginFrame();
}

void GUI::CreateContext(Engine& engine) {
	ImGui::Begin("Inspector");
	//ImGui::SliderFloat("Timer Speed", &speed, 0.0f, 10.0f, " % .2f", NULL);
	//ImGui::NewLine();

	if (ImGui::BeginTabBar("tabs")) {

		if (ImGui::BeginTabItem("Rotate")) {
			ImGui::Text("Rotate Object");
			ImGui::SliderInt("X", &engine.rotateX, -1.0f, 1.0f);
			ImGui::SliderInt("Y", &engine.rotateY, -1.0f, 1.0f);
			ImGui::SliderInt("Z", &engine.rotateZ, -1.0f, 1.0f);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Transform")) {
			ImGui::Text("Transform Object");
			ImGui::SliderFloat("X  ", &engine.AK47_scaleX, 0.01f, 10.0f);
			ImGui::SliderFloat("Y  ", &engine.AK47_scaleY, 0.01f, 10.0f);
			ImGui::SliderFloat("Z  ", &engine.AK47_scaleZ, 0.01f, 10.0f);

			ImGui::NewLine();		

			ImGui::Checkbox("Use Locked Scale", &engine.UseLockedScale); 
			if (engine.UseLockedScale) {
				ImGui::SliderFloat("Locked Scale", &engine.Ak47_LockedScale, 0.01f, 10.0);
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Translate")) {
			ImGui::Text("Translate Object");
			ImGui::SliderFloat("X ", &engine.AK47_posX, -10.0f, 10.0f);
			ImGui::SliderFloat("Y ", &engine.AK47_posY, -10.0f, 10.0f);
			ImGui::SliderFloat("Z ", &engine.AK47_posZ, -10.0f, 10.0f);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Misc")) {
			ImGui::SliderFloat("Timer Speed", &engine.speed, 0.0f, 10.0f, " % .2f", NULL);
			ImGui::Text("Mute Audio: M");
			ImGui::Text("Toggle Wireframe: F");

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}

void GUI::RenderContext(GLFWwindow* window) {
	int display_w, display_h;

	ImGui::Render();
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Render(Engine& engine, GLFWwindow* window) {
	NewFrame();
	CreateContext(engine);
	RenderContext(window);
}