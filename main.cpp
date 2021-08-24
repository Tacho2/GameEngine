#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    //Initialize GLFW
    glfwInit();

    //Give GLFW hints about what version of opengl we are using
    //I'm using 3.3 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    //Using core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //create window object
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "First Window", NULL, NULL);

    //if something messed up and theres no window
    if (window == NULL)
    {
        std::cout << "rip" << std::endl;
        glfwTerminate();
        return -1;
    }

    //set window context to opengl
    glfwMakeContextCurrent(window);
    //sets viewport of window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialize glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    //initialize renderer
    Renderer* renderer = new Renderer();

    //while the window isnt closed
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        //render 
        renderer->render();
        


        //swap back buffer with front buffer
        glfwSwapBuffers(window);

        //take care of all opengl events
        glfwPollEvents();
    }

    //calling renderer's deconstructor
    delete renderer;

}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
