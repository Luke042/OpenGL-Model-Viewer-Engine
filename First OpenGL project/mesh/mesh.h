#pragma once
#include "../engine/engine.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

struct Engine;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	
};

struct Mesh {
public:
	std::vector<Vertex>			vertices;
	std::vector<unsigned int>	indices;
	unsigned int VBO, VAO, EBO;
	unsigned int textureID = 0;

	std::vector<std::string> split(std::string line, std::string delimiter);
	void MakeMesh(std::string filename);
	void Draw(unsigned int shaderProgram, Engine& engine);
	///void SetScale(glm::vec3 _scale);
	void LoadTextureFromFile(const char* filename, Engine& engine);
private:
	unsigned int Ak47TextureID;
};