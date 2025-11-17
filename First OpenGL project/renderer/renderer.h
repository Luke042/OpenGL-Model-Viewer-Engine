#pragma once
#include "../engine/engine.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

struct Renderer {
public:
	Renderer(Engine& eng);
	enum class RenderMode {
		Fill, Wireframe
	};

	void RenderWedge(RenderMode rendermode, unsigned int shaderProgram, unsigned int textureID);
	void Render(unsigned int shaderProgram, unsigned int textureID);
	void ToggleWireFrameMode();

private:
	Engine& engine;
};
