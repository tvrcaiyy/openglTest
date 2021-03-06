#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include "glm/gtc/matrix_transform.hpp"
#include "../CameraManager.h"
#include "../ShaderManager.h"

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height);
void processInput(GLFWwindow* pWindow);
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);
void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods);

float vertices[] = {
	// Back face
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	// Front face
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	// Right face
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	// Top face
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left   
};

CameraManager pCamera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);
int fps;
float deltaTime;
float lastTIme;
double lastPosx = SCR_WIDTH * 0.5f;
double lastPosy = SCR_HEIGHT * 0.5f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Advanced GLSL !",NULL,NULL);
	if (!pWindow)
	{
		cout << "create window failed !" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "initialize glad Failed !" << endl;
		return -1;
	}

	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);
	glfwSetCursorPosCallback(pWindow,mouseMove_callback);
	glfwSetScrollCallback(pWindow,mouseScroll_callback);
	glfwSetMouseButtonCallback(pWindow,mouseButton_callback);

	unsigned int VAO,VBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	unsigned int ubo;
	glGenBuffers(1,&ubo);
	glBindBuffer(GL_UNIFORM_BUFFER,ubo);
	glBufferData(GL_UNIFORM_BUFFER,2 * sizeof(glm::mat4),NULL,GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER,0);

	ShaderManager pRedShader("../shaders/AdvancedGLSL/redVertex.vs","../shaders/AdvancedGLSL/fragment.fs");
	ShaderManager pGreenShader("../shaders/AdvancedGLSL/greenVertex.vs","../shaders/AdvancedGLSL/fragment.fs");
	ShaderManager pBlueShader("../shaders/AdvancedGLSL/blueVertex.vs","../shaders/AdvancedGLSL/fragment.fs");
	ShaderManager pYellowShader("../shaders/AdvancedGLSL/yellowVertex.vs","../shaders/AdvancedGLSL/fragment.fs");

	//if glUniformBlockBinding did not call,default binding is 0
	//unsigned int uniformIndex = glGetUniformBlockIndex(pShader.ID,"Matries");
	//glUniformBlockBinding(pShader.ID,uniformIndex,1);
	glBindBufferRange(GL_UNIFORM_BUFFER,1,ubo,0,2 * sizeof(glm::mat4));

	//glPointSize(10);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - lastTIme;
		lastTIme = glfwGetTime();
		processInput(pWindow);
		fps = (int)(1.0f / deltaTime);
		string str = "Cube Map ! fps:" + std::to_string(fps);
		glfwSetWindowTitle(pWindow,str.c_str());

		processInput(pWindow);

		glClearColor(0.33f,0.33f,0.33f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = pCamera.GetLookAt();
		glm::mat4 projection = glm::perspective(glm::radians(pCamera.Zoom),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);
		glBindBuffer(GL_UNIFORM_BUFFER,ubo);
		glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(projection));
		glBindVertexArray(VAO);

		pRedShader.use();
		glm::mat4 model(1.0);
		model = glm::translate(model,glm::vec3(-0.75f, 0.75f, 0.0f));
		pRedShader.setMat4("model",model);
		//pShader.setMat4("view",view);
		//pShader.setMat4("projection",projection);
		glDrawArrays(GL_TRIANGLES,0,36);

		pGreenShader.use();
		model = glm::mat4(1.0);
		model = glm::translate(model,glm::vec3(0.75f, 0.75f, 0.0f));
		pGreenShader.setMat4("model",model);
		glDrawArrays(GL_TRIANGLES,0,36);

		pBlueShader.use();
		model = glm::mat4(1.0);
		model = glm::translate(model,glm::vec3(-0.75f, -0.75f, 0.0f));
		pBlueShader.setMat4("model",model);
		glDrawArrays(GL_TRIANGLES,0,36);

		pYellowShader.use();
		model = glm::mat4(1.0);
		model = glm::translate(model,glm::vec3(0.75f, -0.75f, 0.0f));
		pYellowShader.setMat4("model",model);
		glDrawArrays(GL_TRIANGLES,0,36);

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height)
{
	glViewport(0,0,width,height);
}
void processInput(GLFWwindow* pWindow)
{
	if(glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GLFW_TRUE)
	{
		glfwSetWindowShouldClose(pWindow,GLFW_TRUE);
	}

	if(glfwGetKey(pWindow,GLFW_KEY_W) == GLFW_TRUE)
	{
		pCamera.ProcessKeyboardInput(CameraMoveForward,deltaTime);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_S) == GLFW_TRUE)
	{
		pCamera.ProcessKeyboardInput(CameraMoveBackward,deltaTime);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_A) == GLFW_TRUE)
	{
		pCamera.ProcessKeyboardInput(CameraMoveLeft,deltaTime);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_D) == GLFW_TRUE)
	{
		pCamera.ProcessKeyboardInput(CameraMoveRight,deltaTime);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_0) == GLFW_TRUE)
	{
		pCamera.SwitchToFace(0);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_1) == GLFW_TRUE)
	{
		pCamera.SwitchToFace(1);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_2) == GLFW_TRUE)
	{
		pCamera.SwitchToFace(2);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_3) == GLFW_TRUE)
	{
		pCamera.SwitchToFace(3);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_4) == GLFW_TRUE)
	{
		pCamera.SwitchToFace(4);
	}
	if(glfwGetKey(pWindow,GLFW_KEY_5) == GLFW_TRUE)
	{
		pCamera.SwitchToFace(5);
	}
}
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy)
{
	pCamera.ProcessMouseMovement(posx - lastPosx,lastPosy - posy);
	lastPosx = posx;
	lastPosy = posy;
}
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety)
{
	pCamera.ProcessMouseScroll(offsety);
}
void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		if (action == GLFW_PRESS)
		{
			pCamera.bMove = true;
		}
		else if (action == GLFW_RELEASE)
		{
			pCamera.bMove = false;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		if (action == GLFW_PRESS)
		{
			pCamera.bRotate = true;
		}
		else if (action == GLFW_RELEASE)
		{
			pCamera.bRotate = false;
		}
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		break;
	}
}