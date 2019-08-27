#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "stb_image.h"
#include <iostream>
#include "../ShaderManager.h"
#include "../CameraManager.h"
#include "glm\gtc\matrix_transform.hpp"

void processInput(GLFWwindow* pWindow);
void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height);
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
void mouse_button_callback(GLFWwindow* pWindow,int button, int action, int mods);
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);

glm::mat4 getLookAtMatrix(glm::vec3 cameraPos,glm::vec3 lookPos,glm::vec3 worldUp);

const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 300;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f), 
	glm::vec3( 2.0f,  5.0f, -15.0f), 
	glm::vec3(-1.5f, -2.2f, -2.5f),  
	glm::vec3(-3.8f, -2.0f, -12.3f),  
	glm::vec3( 2.4f, -0.4f, -3.5f),  
	glm::vec3(-1.7f,  3.0f, -7.5f),  
	glm::vec3( 1.3f, -2.0f, -2.5f),  
	glm::vec3( 1.5f,  2.0f, -2.5f), 
	glm::vec3( 1.5f,  0.2f, -1.5f), 
	glm::vec3(-1.3f,  1.0f, -1.5f)  
};

unsigned int indice[] = {
	0,1,3,
	1,2,3
};
float mixValue = 0.2f;
float fov = 45.0f;
float aspect = 1.33f;
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
float lastPosx = SCR_WIDTH / 2;
float lastPosy = SCR_HEIGHT / 2;
CameraManager camera = CameraManager(glm::vec3(0.0f,2.0f,10.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Coordinate and Camera",NULL,NULL);
	if (!pWindow)
	{
		std::cout << "create window failed !" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "initialize glad failed !" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);
	glfwSetCursorPosCallback(pWindow,mouseMove_callback);
	glfwSetMouseButtonCallback(pWindow,mouse_button_callback);
	glfwSetScrollCallback(pWindow,mouseScroll_callback);
	
	//glfwSetInputMode(pWindow,GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	unsigned int VAO,VBO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5 * sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice),indice,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int texture1,texture2;
	glGenTextures(1,&texture1);
	glBindTexture(GL_TEXTURE_2D,texture1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	int imageWidth,imageHeight,colorChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load("../resource/textures/container.jpg",&imageWidth,&imageHeight,&colorChannels,0);
	if (imageData)
	{
		//(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageWidth,imageHeight,0,GL_RGB,GL_UNSIGNED_BYTE,imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load Image Fialed !" << std::endl;
	}
	stbi_image_free(imageData);

	glGenTextures(1,&texture2);
	glBindTexture(GL_TEXTURE_2D,texture2);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	imageData = stbi_load("../resource/textures/awesomeface.png",&imageWidth,&imageHeight,&colorChannels,0);
	if (imageData)
	{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageWidth,imageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load Image Fialed !" << std::endl;
	}
	stbi_image_free(imageData);

	ShaderManager pShader("vertex.vs","fragment.fs");
	pShader.use();
	//pShader.setInt("texture1",0);
	//pShader.setInt("texture2",1);
	glUniform1i(glGetUniformLocation(pShader.ID,"texture1"),0);
	glUniform1i(glGetUniformLocation(pShader.ID,"texture2"),1);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(pWindow))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		processInput(pWindow);

		glClearColor(0.33f,0.33f,0.33f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		pShader.use();
		pShader.setFloat("mixValue",mixValue);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		float radius = 10.0f;
		float camx = sin(glfwGetTime()) * radius;
		float camz = cos(glfwGetTime()) * radius;
		view = camera.GetLookAt();
		projection = glm::perspective(glm::radians(camera.Zoom),aspect,0.1f,100.0f);
		pShader.setMat4("view",view);
		pShader.setMat4("projection",projection);
		glBindVertexArray(VAO);
		for (int i = 0;i < 10;i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model,cubePositions[i]);
			if (i != 0)
				model = glm::rotate(model,(float)glfwGetTime() * glm::radians(-55.0f),glm::vec3(0.5f,1.0f,0.0f));
			else
				model = glm::rotate(model,glm::radians(20.0f * i),glm::vec3(0.5f,1.0f,0.0f));
			pShader.setMat4("model",model);
			//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
			glDrawArrays(GL_TRIANGLES,0,36);
		}

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}

	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* pWindow)
{
	if (glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GLFW_TRUE)
	{
		glfwSetWindowShouldClose(pWindow,GLFW_TRUE);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_DOWN) == GLFW_TRUE)
	{
		//fov -= 0.1;
		aspect -= 0.1f;
		// 		mixValue -= 0.01;
		// 		if (mixValue <= 0)
		// 			mixValue = 0.0f;
	}
	if (glfwGetKey(pWindow,GLFW_KEY_UP) == GLFW_TRUE)
	{
		//fov += 0.1;
		aspect += 0.1f;
		// 		mixValue += 0.01;
		// 		if (mixValue >= 1)
		// 			mixValue = 1.0f;
	}
	if (glfwGetKey(pWindow,GLFW_KEY_W) == GLFW_TRUE)
	{
		camera.ProcessKeyboardInput(CameraMoveForward,deltaTime);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_S) == GLFW_TRUE)
	{
		camera.ProcessKeyboardInput(CameraMoveBackward,deltaTime);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_A) == GLFW_TRUE)
	{
		camera.ProcessKeyboardInput(CameraMoveLeft,deltaTime);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_D) == GLFW_TRUE)
	{
		camera.ProcessKeyboardInput(CameraMoveRight,deltaTime);
	}
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height)
{
	glViewport(0,0,width,height);
}

void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy)
{
	camera.ProcessMouseMovement(posx - lastPosx,lastPosy - posy);
	lastPosx = posx;
	lastPosy = posy;
}

void mouse_button_callback(GLFWwindow* pWindow,int button, int action, int mods)
{
	switch(button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		{
			if (action == GLFW_PRESS)
			{
				camera.bMove = true;
			}
			else if(action == GLFW_RELEASE)
			{
				camera.bMove = false;
			}
		}
		break;
	default:
		return;
	}
	return;
}

void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety)
{
	camera.ProcessMouseScroll(offsety);
}
