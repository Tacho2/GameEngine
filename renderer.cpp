#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vmath.h"

GLuint compile_shaders();

Renderer::Renderer() 
{
	matrixMaker = new vmath();
	//create rendering program
	rendering_program = compile_shaders();
	//create objects
	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	static const GLfloat cubePositions[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	matrixMaker->buildProjectionMatrix();
}

void Renderer::render() 
{
	glUseProgram(rendering_program);

	//build model view matrix
	matrixMaker->buildViewMatrix();
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
	glDeleteVertexArrays(1, &vertex_array_object);
	delete matrixMaker;
}

GLuint compile_shaders() 
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	//vertex shader code
	static const GLchar * vertex_shader_source[] =
	{
		"#version 450 core								\n"
		"												\n"
		"uniform float projectionMatrix;					\n"
		"												\n"
		"												\n"
		"void main(void)								\n"
		"{												\n"
		"	vec4 vertices[3] = vec4[3](vec4( 0.5 + projectionMatrix, -0.5, 0.5, 1.0), \n"
		"	vec4(-0.5, -0.5, 0.5, 1.0),				\n"
		"	vec4(0.5, 0.25, 0.5, 1.0));				\n"			
		"												\n"
		"	gl_Position = vertices[gl_VertexID] -   vec4(projectionMatrix, 0, 0, 0);	\n"
		"}												\n"

	};

	//fragment shader code
	static const GLchar * fragment_shader_source[] =
	{
		"#version 450 core								\n"
		"												\n"
		"out vec4 color;								\n"
		"												\n"
		"void main(void)								\n"
		"{												\n"
		"	color = vec4(0.0, 0.0, 1.0, 1.0); 		\n"
		"}												\n"

	};

	//create a vertex shader and put it in the vertex_shader variable
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	//put the vertex shader code into the vertex_shader variable
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	//compile vertex_shader into a useable program
	glCompileShader(vertex_shader);

	//do the same process with the fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	//create program (i think it can be thought of as the rendering pipeline) 
	program = glCreateProgram();
	//attach the shaders to the program
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	//links the shaders together i think, or maybe it links the program to the gpu.
	glLinkProgram(program);

	GLuint projLocation = glGetUniformLocation(program, "projectionMatrix");
	glUniform1f(projLocation, -0.25f);

	//the shaders are on the program now and now we cleanup the initial instantiations because we have the copys on teh program
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}