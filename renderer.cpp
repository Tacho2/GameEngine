#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vmath.h"
#include "C:/Users/Cameron Egbert/Downloads/vmath/vmath-0.13/src/vmath.h"

GLuint compile_shaders();

Renderer::Renderer() 
{
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

	//generate some data and put it into a buffer
	GLuint buffer;
	//generates 1 buffer at adress of "buffer"
	glGenBuffers(1, &buffer);
	//bind to contex
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//put in the information
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW);

	//set up vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	//build proj matrix
	proj_matrix = Matrix4<float>::createFrustum(-5, 5, -5, 5, 1, 50);
}

void Renderer::render() 
{
	//specify color of background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//clean back buffer
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(rendering_program);
	
	//build model view matrix
	mv_matrix = Matrix4<float>::createTranslation(0.0f, 0.0f, -4.0f) * Matrix4<float>::createRotationAroundAxis(0.0f, 45.0f, 30.0f); // *Matrix4<float>::createScale(2, 2, 2);
	
	GLuint mv_location = glGetUniformLocation(rendering_program, "mv_matrix");
	GLuint proj_location = glGetUniformLocation(rendering_program, "proj_matrix");
	std::cout << mv_location << " " << proj_location << std::endl;

	glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);

	glDrawArrays(GL_TRIANGLES, 0, 36);

}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
	glDeleteVertexArrays(1, &vertex_array_object);
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
		"in vec4 position;								\n"
		"												\n"
		"out VS_OUT										\n"
		"{												\n"
		"	vec4 color;									\n"
		"} vs_out;												\n"
		"												\n"
		"uniform mat4 mv_matrix;						\n"
		"uniform mat4 proj_matrix;						\n"
		"												\n"
		"void main(void)								\n"
		"{												\n"		
		"												\n"
		"	gl_Position = proj_matrix * mv_matrix * position;						\n"
		"   vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);			\n"
		"												\n"
		"}												\n"

	};

	//fragment shader code
	static const GLchar * fragment_shader_source[] =
	{
		"#version 450 core								\n"
		"												\n"
		"out vec4 color;								\n"
		"												\n"
		"in VS_OUT										\n"
		"{												\n"
		"	vec4 color;									\n"
		"} fs_in;										\n"

		"void main(void)								\n"
		"{												\n"
		"	color = fs_in.color;				 		\n"
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