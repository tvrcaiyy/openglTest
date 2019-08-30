#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../ShaderManager.h"
#include "../CameraManager.h"
#include <iostream>

const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 300;

void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height);
void processInput(GLFWwindow* pWindow);
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
void mouse_button_callback(GLFWwindow* pWindow,int button, int action, int mods);
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

unsigned int indice[] = {
	0,1,3,
	1,2,3
};

float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
float lastPosx = SCR_WIDTH / 2;
float lastPosy = SCR_HEIGHT / 2;

CameraManager pCamera(glm::vec3(0.0f,0.0f,5.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Colors",NULL,NULL);
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

	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);
	glfwSetCursorPosCallback(pWindow,mouseMove_callback);
	glfwSetMouseButtonCallback(pWindow,mouse_button_callback);
	glfwSetScrollCallback(pWindow,mouseScroll_callback);

	unsigned int VAO,VBO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indice),indice,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	//------------------------------------------------------
	unsigned int lightVAO,lightVBO;
	glGenVertexArrays(1,&lightVAO);
	glGenBuffers(1,&lightVBO);

	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER,lightVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	ShaderManager pShader("vertex.vs","fragment.fs");
	ShaderManager pLightShader("LightVertex.vs","LightFragment.fs");
	glEnable(GL_DEPTH_TEST);
	while(!glfwWindowShouldClose(pWindow))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		processInput(pWindow);

		//Render
		glClearColor(0.33f,0.33f,0.33f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float camx = sin(glfwGetTime()) * 2;
		float camz = cos(glfwGetTime()) * 2;
		pShader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = pCamera.GetLookAt();
		projection = glm::perspective(glm::radians(pCamera.Zoom),(float)SCR_WIDTH/SCR_HEIGHT,0.1f,100.0f);
		pShader.setMat4("model",model);
		pShader.setMat4("view",view);
		pShader.setMat4("projection",projection);
		pShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
		pShader.setVec3("objectColor",1.0f, 0.5f, 0.31f);
		pShader.setVec3("lightColor",1.0f,1.0f,1.0f);
		pShader.setVec3("LightPosition",camx, 0.0f, camz);
		pShader.setVec3("viewPos",pCamera.Position);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,36);
		//------------------------------------------------------
		pLightShader.use();
		model = glm::translate(model,glm::vec3(camx, 0.0f, camz));
		model = glm::scale(model,glm::vec3(0.2f));
		pLightShader.setMat4("model",model);
		pLightShader.setMat4("view",view);
		pLightShader.setMat4("projection",projection);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES,0,36);

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}

	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height)
{
	glViewport(0,0,width,height);
}

void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy)
{
	pCamera.ProcessMouseMovement(posx - lastPosx,lastPosy - posy);
	lastPosx = posx;
	lastPosy = posy;
}

void mouse_button_callback(GLFWwindow* pWindow,int button, int action, int mods)
{
	switch(button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		{
			if (action == GLFW_PRESS)
			{
				pCamera.bMove = true;
			}
			else if(action == GLFW_RELEASE)
			{
				pCamera.bMove = false;
			}
		}
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		{
			if (action == GLFW_PRESS)
			{
				pCamera.bRotate = true;
			}
			else if(action == GLFW_RELEASE)
			{
				pCamera.bRotate = false;
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
	pCamera.ProcessMouseScroll(offsety);
}

void processInput(GLFWwindow* pWindow)
{
	if (glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GLFW_TRUE)
	{
		glfwSetWindowShouldClose(pWindow,GLFW_TRUE);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_W) == GLFW_TRUE)
	{
		pCamera.ProcessKeyboardInput(CameraMoveForward,deltaTime);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_S) == GLFW_TRUE)
	{
		pCamera.ProcessKeyboardInput(CameraMoveBackward,deltaTime);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_A) == GLFW_TRUE)
	{
		pCamera.ProcessKeyboardInput(CameraMoveLeft,deltaTime);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_D) == GLFW_TRUE)
	{
		pCamera.ProcessKeyboardInput(CameraMoveRight,deltaTime);
	}
}