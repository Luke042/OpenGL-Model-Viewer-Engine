#pragma once
#include "../includes/imgui/imgui.h"
#include "../includes/imgui/imgui_impl_glfw.h"
#include "../includes/imgui/imgui_impl_opengl3.h"
//#include "../includes/imgui/ImGuizmo.h"

#include "../includes/GLAD/glad.h"
#include "../includes/GLFW/glfw3.h"
#include <chrono>
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"
#include <algorithm>
#include <string>
#include <iostream>
#include "../audio/audio.h"
#include "../mesh/mesh.h"

struct Engine {
public:

	void Init();

	void InitGlfw();
	bool CreateWindow();
	int InitGlad();
	void InitViewPort();
	void InitClock();
	void SwapBuffers(GLFWwindow* window);

	void CreateBuffers(const float* vertices, size_t size);
	void LoadShaders(const char* vertexSource, const char* fragmentSource);
	bool WindowShouldClose(GLFWwindow* window);
	void Terminate();
	static void frameBufferCallback(GLFWwindow* window, int width, int height);
	void Clear();
	void GenVBOBuffer();
	unsigned int GenVertexShader();
	float startClock();
	bool CheckShaderCompileStatus(unsigned int vertex_shader);
	void UpdateVertices(float* vertices, size_t size);
	void DisableCursor(GLFWwindow* window);
	void EnableCursor(GLFWwindow* window);
	void UseProgram();
	int LoadTexture(const std::string& filename);
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	void UpdateMouse();
	void UpdateViewPort(GLFWwindow* window);
	void InitCamera();
	void BindTexture();
	void Update(GLFWwindow* window, Engine engine);
	void InitMVP();
	void UpdateMVP();

	GLFWwindow* GetWindow();
	unsigned int GetVBO();
	unsigned int GetVertexShader();
	float GetSpeed();
	int GetSuccess();
	glm::vec3 GetCameraPos();
	glm::vec3 GetCameraUp();
	glm::vec3 GetCameraFront();
	unsigned int GetTextureID();
	glm::mat4 GetCamera();

	int width, height;

	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;
	unsigned int shaderProgram = 0;
	unsigned int textureID = 0;
	unsigned int mvpLocID = 0;

	bool UseLockedScale = false;

	float Ak47_LockedScale = 1.0f;

	float AK47_posX = 0.0f, AK47_posY = 0.0f, AK47_posZ = 0.0f;

	float AK47_scaleX = 1.0f, AK47_scaleY = 1.0f, AK47_scaleZ = 1.0f;

	bool wireframe = false;
	float delta_time;
	float speed;
	glm::mat4 camera;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 model = glm::mat4(1.0f);

	//float rotateX = 0.0f, rotateY = 0.0f, rotateZ = 0.0f;
	int rotateX = false, rotateY = 0, rotateZ = false;

private:
	unsigned char* texture_data;

	GLFWwindow* window;
	unsigned int vertex_shader = 0;
	unsigned int fragment_shader = 0;
	int success = 0;

	std::chrono::high_resolution_clock::time_point last_time;

	inline static float yaw = -90.0f;
	inline static float pitch = 0.0f;

	inline static float lastX = 800.0f / 2.0;
	inline static float lastY = 600.0f / 2.0;

	inline static float sensitivity = 100.0f;

	inline static bool firstMouse = true;

	inline static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::vec3();
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

	static constexpr float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.0f,  0.5f, -0.5f,  0.5f, 1.0f,

	 //back triangle
	 -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,
	  0.5f, -0.5f, 0.5f,   1.0f, 0.0f,
	  0.0f,  0.5f, 0.5f,   0.5f, 1.0f,

	  //bottom rectangle
	  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  1.0f, 1.0f,

	  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

	  //right rectangle
	   0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	   0.0f,  0.5f, -0.5f,  1.0f, 0.0f,
	   0.0f,  0.5f,  0.5f,  1.0f, 1.0f,

	   0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	   0.0f,  0.5f,  0.5f,  1.0f, 1.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

	   //left rectangle
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.0f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.0f,  0.5f,  0.5f,  1.0f, 1.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.0f,  0.5f,  0.5f,  1.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f
	};

	glm::vec3 WedgePos;
	glm::vec3 WedgeVelocity;
	glm::vec3 WedgeAcceleration;

};