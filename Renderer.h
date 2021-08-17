#pragma once
#include <glad/glad.h>
#include "vmath.h"

class Renderer {
private:
	GLuint rendering_program;
	GLuint vertex_array_object;
	vmath *matrixMaker;
public:
	Renderer();
	~Renderer();
	void render();
};
