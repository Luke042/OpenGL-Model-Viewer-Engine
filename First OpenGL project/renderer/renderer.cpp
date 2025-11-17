#include "renderer.h"
#include "../includes/glad/glad.h"
#include "../mesh/mesh.h"

//Model& model;

Renderer::Renderer(Engine& eng) : engine(eng) {}

void Renderer::RenderWedge(RenderMode mode, unsigned int shaderProgram, unsigned int textureID) {

	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glBindVertexArray(engine.VAO);

	if (mode == RenderMode::Fill) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(engine.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 24);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(1.0f);
		glBindVertexArray(engine.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 24);
	}
}

void Renderer::Render(unsigned int shaderProgram, unsigned int textureID) {
	if (!engine.wireframe) {
		RenderWedge(Renderer::RenderMode::Fill, shaderProgram, textureID);
	}
	else {
		RenderWedge(Renderer::RenderMode::Wireframe, shaderProgram, textureID);
	}
}

void Renderer::ToggleWireFrameMode() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);
	glBindVertexArray(engine.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 24);
}