#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include <iostream>

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height);


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(SRC_WIDTH,SRC_HEIGHT,"HelloTriangle",NULL,NULL);
	if(pWindow == NULL)
	{
		std::cout << "create window failed !!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(pWindow);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initilize GLAD !" << std::endl;
		return -1;
	}
	
	glViewport(0,0,SRC_WIDTH,SRC_HEIGHT);

	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);

	return 0;
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height)
{
	glViewport(0,0,width,height);
}