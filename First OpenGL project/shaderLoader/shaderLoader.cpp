#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../includes/GLFW/glfw3.h"
#include "shaderLoader.h"

std::string Shader::LoadShaderSource(const std::string& filename) {
    std::string path = ("Assets\\shaders\\" + filename).c_str();

    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader: " << path << std::endl;
        return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    std::string source = buffer.str();
    file.close();

    std::cout << "Loaded shader: " << path << " (" << source.size() << " bytes)" << std::endl;

    return source;
}

void Shader::GenShaders() {
    Shader::LoadShaderSource("vertex.glsl");
    Shader::LoadShaderSource("fragment.glsl");
}
