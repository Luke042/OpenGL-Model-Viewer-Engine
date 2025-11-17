#include "mesh.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"
#include "../gui/gui.h"
#include <map>
#include <tuple>
//#define STB_IMAGE_IMPLEMENTATION
//#include "../includes/stb_image.h"

std::vector<std::string>Mesh::split(std::string line, std::string delimiter) {
	std::vector<std::string> splitline;

	size_t pos = 0;
	std::string token;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		splitline.push_back(token);
		line.erase(0, pos + delimiter.size());
	}

	splitline.push_back(line);

	return splitline;
}

void Mesh::MakeMesh(std::string filename) {
	std::string path = "Assets\\models\\" + filename;
	std::ifstream file(path.c_str());

	if (!file.is_open()) {
		std::cout << "Could not open " << path << "\n";
		return;
	}

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	vertices.clear();
	indices.clear();
	std::map<std::tuple<int, int, int>, unsigned int> vertexMap;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string type;
		ss >> type;

		if (type == "v") {
			glm::vec3 pos;
			ss >> pos.x >> pos.y >> pos.z;
			positions.push_back(pos);
		}
		else if (type == "vt") {
			glm::vec2 uv;
			ss >> uv.x >> uv.y;
			uv.y = 1.0f - uv.y;
			texCoords.push_back(uv);
		}
		else if (type == "vn") {
			glm::vec3 normal;
			ss >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (type == "f") {
			std::string vertexData;
			for (int i = 0; i < 3; i++) {
				ss >> vertexData;
				auto parts = split(vertexData, "/");

				int vi = std::stoi(parts[0]) - 1;
				int ti = (parts.size() > 1 && !parts[1].empty()) ? std::stoi(parts[1]) - 1 : -1;
				int ni = (parts.size() > 2 && !parts[2].empty()) ? std::stoi(parts[2]) - 1 : -1;

				auto key = std::make_tuple(vi, ti, ni);

				if (vertexMap.find(key) == vertexMap.end()) {
					Vertex v{};
					v.position = positions[vi];
					if (ti >= 0) v.texCoords = texCoords[ti];
					if (ni >= 0) v.normal = normals[ni];
					vertices.push_back(v);
					vertexMap[key] = static_cast<unsigned int>(vertices.size() - 1);
				}

				indices.push_back(vertexMap[key]);
			}
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	std::cout << "Loaded mesh: " << path << " (" << vertices.size() << " vertices)\n";
}


void Mesh::Draw(unsigned int shaderProgram, Engine& engine)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Ak47TextureID);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	
}


/*
void Mesh::SetScale(glm::vec3 _scale) {
	this->scale = _scale;
}
*/

void Mesh::LoadTextureFromFile(const char* filename, Engine& engine) {
	textureID = engine.LoadTexture(filename);
	Ak47TextureID = textureID;
}