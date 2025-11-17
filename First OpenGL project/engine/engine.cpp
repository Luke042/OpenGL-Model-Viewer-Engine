#include "engine.h"
#include "../input/input.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../includes/stb_image.h"
#include "../shaderLoader/shaderLoader.h"
#include "../includes/IrrKlang/irrKlang.h"
#include <iostream>
#include <chrono>
#include <thread>

Input input;
Shader shader;

void Engine::Init() {
	system("color 6");

	std::string vertexSource = shader.LoadShaderSource("vertex2.glsl");
	std::string fragmentSource = shader.LoadShaderSource("fragment2.glsl");

	InitGlfw();
	CreateWindow();
	InitGlad();
	LoadTexture("container.jpg");
	if (audio.InitIrrKlang()) {
		audio.SetVolume(0.3);
		audio.StartBGMusic();
	}
	InitViewPort();
	InitClock();
	LoadShaders(vertexSource.c_str(), fragmentSource.c_str());
	UseProgram();
	BindTexture();
	InitCamera();
	CreateBuffers(vertices, sizeof(vertices));
	InitMVP();

}

void Engine::CreateBuffers(const float* vertices, size_t size) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Engine::LoadShaders(const char* vertexSource, const char* fragmentSource) {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
}

void Engine::UseProgram() {
	glUseProgram(shaderProgram);
}

void Engine::InitGlfw() {
	if (!glfwInit()) {
		std::cerr << "failed to initalise GLFW.\n";
	}
	else {
		std::cout << "Initalised GLFW.\n";
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool Engine::CreateWindow() {
	window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
	if (window == nullptr) {
		std::cerr << "Failed to create Window.\n";
		glfwTerminate();
		return false;
	}
	else {
		std::cout << "Created window.\n";
	}

	glfwMakeContextCurrent(window);
	return true;
}

int Engine::InitGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initalise glad.\n";
		return -1;
	}
	else {
		std::cout << "Initalised Glad.\n";
		glEnable(GL_DEPTH_TEST);
		return 0;
	}	
}

void Engine::InitViewPort() {
	glViewport(0, 0, 800, 600);
}

GLFWwindow* Engine::GetWindow() {
	return window;
}

void Engine::frameBufferCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool Engine::WindowShouldClose(GLFWwindow* window) {
	return glfwWindowShouldClose(window);
}

void Engine::Terminate() {
	audio.sound_engine->drop();

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (shaderProgram) glDeleteProgram(shaderProgram);
	if (vertexShader) glDeleteShader(vertexShader);
	if (fragmentShader) glDeleteShader(fragmentShader);
	if (VBO) glDeleteBuffers(1, &VBO);
	if (VAO) glDeleteVertexArrays(1, &VAO);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (window) glfwDestroyWindow(window);
	glfwTerminate();
}

void Engine::Clear() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::GenVBOBuffer() {
	glGenBuffers(1, &VBO);
}

unsigned int Engine::GetVBO() {
	return VBO;
}

unsigned int Engine::GenVertexShader() {
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	return vertex_shader;
}

unsigned int Engine::GetVertexShader() {
	return vertex_shader;
}

bool Engine::CheckShaderCompileStatus(unsigned int vertex_shader) {
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	return success;
}

int Engine::GetSuccess() {
	return success;
}

void Engine::InitClock() {
	using clock = std::chrono::high_resolution_clock;
	last_time = clock::now();
	speed = 1.0;

	std::cout << "Speed is set to: " << speed << "." << "\n";
}

float Engine::GetSpeed() {
	return speed;
}

float Engine::startClock() {
	using clock = std::chrono::high_resolution_clock;

	auto current_time = clock::now();

	std::chrono::duration<float> delta = current_time - last_time;
	float delta_time = delta.count();

	last_time = current_time;

	return delta_time;
}

void Engine::UpdateVertices(float* vertices, size_t size) {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}

void Engine::DisableCursor(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Engine::EnableCursor(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

int Engine::LoadTexture(const std::string& filename) {
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;

	const char* path = ("Assets\\textures\\" + filename).c_str();
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data) {
		std::cerr << "Failed to load texture: " << path << "\n";
		stbi_image_free(data);
		return -1;
	}
	else {
		std::cout << "Loaded texture: " << path << " (" << width << "x" << height << ", channels: " << nrChannels << ")\n";

		GLenum format = GL_RGB;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
		return textureID;
	}

}

unsigned int Engine::GetTextureID() {
	return textureID;
}

void Engine::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	pitch = std::clamp(pitch, -89.0f, 89.0f);

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}


void Engine::UpdateMouse() {

	glUseProgram(shaderProgram);
	// Compute matrices
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		(float)1920 / (float)1080, 0.1f, 100.0f);

	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

	// Send matrices to shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

glm::vec3 Engine::GetCameraPos() {
	return cameraPos;
}

glm::vec3 Engine::GetCameraUp() {
	return cameraUp;
}

glm::vec3 Engine::GetCameraFront() {
	return cameraFront;
}

void Engine::SwapBuffers(GLFWwindow* window) {
	glfwSwapBuffers(window);
	//glfwPollEvents();
}

void Engine::UpdateViewPort(GLFWwindow* window) {
	glfwSetFramebufferSizeCallback(window, Engine::frameBufferCallback);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	float rotx = sensitivity * (float)(x - (height / 2)) / height;
	float roty = sensitivity * (float)(y - (height / 2)) / height;

	//glm::vec3 newOrientation = glm::rotate(camera, glm::radians(-rotx), glm::normalize(glm::cross(camera, cameraUp)));
}

void Engine::InitCamera() {
	Engine::camera = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
}

glm::mat4 Engine::GetCamera() {
	return camera;
}

void Engine::BindTexture() {
	glActiveTexture(GL_TEXTURE0);
	unsigned int textureID = GetTextureID();
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
}

void Engine::Update(GLFWwindow* window, Engine engine) {
	UpdateViewPort(window);
	input.UpdateInput(&engine);
}

void Engine::InitMVP() {
	mvpLocID = glGetUniformLocation(shaderProgram, "mvp");
}

void Engine::UpdateMVP() {
	glm::vec3 position = glm::vec3(AK47_posX, AK47_posY, AK47_posZ);

	glm::vec3 axis = glm::normalize(glm::vec3(rotateX, rotateY, rotateZ));
	float time = glfwGetTime();

	model = glm::mat4(1.0f);

	if (!UseLockedScale) {
		model = glm::scale(model, glm::vec3(AK47_scaleX, AK47_scaleY, AK47_scaleZ));
	}
		
	else {
		model = glm::scale(model, glm::vec3(Ak47_LockedScale));
	}

	model = glm::translate(model, position);
	if (rotateX != 0.0f || rotateY != 0.0f || rotateZ != 0.0f) {
		model = glm::rotate(model, time * speed, axis);
	}
	camera = GetCamera();

	//camera = glm::rotate(glm::mat4(1.0f), (float)1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mvp = projection * camera * model;
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(mvpLocID, 1, GL_FALSE, glm::value_ptr(mvp));
}