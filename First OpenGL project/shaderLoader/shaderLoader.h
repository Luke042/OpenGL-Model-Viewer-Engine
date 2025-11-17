#pragma once
#include <string>

class Shader {
public:
	std::string LoadShaderSource(const std::string& filename);
	void GenShaders();
};
