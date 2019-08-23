#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "../ShaderManager.h"

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height);
void processInput(GLFWwindow* pWindow);
void display();

float vertices[] = {
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};

unsigned int indices[] = {
	0,1,2,
	1,2,3
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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

	//ShaderManager* pShaderManager = new ShaderManager("vertex.vs","fragment.fs");
	ShaderManager pShaderManager ("vertex.vs","fragment.fs");

	GLuint vao,vbo,ebo;
	glGenVertexArrays(1,&vao);
	glGenBuffers(1,&vbo);
	glGenBuffers(1,&ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	
	while (!glfwWindowShouldClose(pWindow))
	{
		processInput(pWindow);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pShaderManager.use();
		pShaderManager.setFloat("offsetx",0.3);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}

	glfwTerminate();

	return 0;
}

void display()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height)
{
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow* pWindow)
{
	if(glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GL_TRUE)
	{
		glfwSetWindowShouldClose(pWindow,GL_TRUE);
	}
}