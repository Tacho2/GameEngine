#pragma once
#include <glad/glad.h>
#include "matrixMaker.h"
#include "vmath.h"

class Renderer {
private:
	GLuint rendering_program;
	GLuint vertex_array_object;
	matrixMaker *matrixMaker;
	
public:
	Renderer();
	~Renderer();
	void render();
	Matrix4<float> mv_matrix;
	Matrix4<float> proj_matrix;

};
