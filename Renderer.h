#pragma once
#include <glad/glad.h>


class Renderer {
private:
	GLuint rendering_program;
	GLuint vertex_array_object;
public:
	Renderer();
	~Renderer();
	void render();
};
