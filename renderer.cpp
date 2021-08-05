#include "Renderer.h"
#include <iostream>


Renderer::Renderer() 
{
	std::cout << "Initializing renderer" << std::endl;
}

void Renderer::render() 
{
	std::cout << "I am rendering something right now" << std::endl;
}

Renderer::~Renderer()
{
	std::cout << "Cleaning up the renderer" << std::endl;
}

