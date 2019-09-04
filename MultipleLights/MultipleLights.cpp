#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "stb_image.h"
#include "..\ShaderManager.h"
#include "..\CameraManager.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height);
void processInput(GLFWwindow* pWindow);
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);
void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods);

CameraManager pCamera(glm::vec3(0.0f,0.0f,5.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);

float deltaTime = 0.0f;
float lastTime = 0.0f;
float lastPosx = SCR_WIDTH * 0.5f;
float lastPosy = SCR_HEIGHT * 0.5f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Multiple Lights!",NULL,NULL);
	glfwMakeContextCurrent(pWindow);
	if (!pWindow)
	{
		std::cout << "create window failed ! " << std::endl;
		glfwTerminate();
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "initialize glad failed !!" << std::endl;
		return -1;
	}

	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);
	glfwSetCursorPosCallback(pWindow,mouseMove_callback);
	glfwSetMouseButtonCallback(pWindow,mouseButton_callback);
	glfwSetScrollCallback(pWindow,mouseScroll_callback);


	unsigned int VAO,VBO,lambVAO,lambVBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1,&lambVAO);
	glGenBuffers(1,&lambVBO);

	glBindVertexArray(lambVAO);
	glBindBuffer(GL_ARRAY_BUFFER,lambVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	ShaderManager pLampShader("lampVertex.vs","lampFragment.fs");
	//ShaderManager pShader("vertex.vs","fragment.fs");

	glm::vec3 lightPos(1.2f,1.0f,2.0f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(pWindow))
	{
		processInput(pWindow);

		glClearColor(0.1f,0.1f,0.1f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 model(1.0f);
		model = glm::translate(model,glm::vec3(lightPos));
		model = glm::scale(model,glm::vec3(0.1f));
		glm::mat4 view(1.0f);
		view = pCamera.GetLookAt();
		glm::mat4 projection = glm::perspective(glm::radians(pCamera.Zoom),(float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f,100.0f);
		pLampShader.use();
		pLampShader.setMat4("model",model);
		pLampShader.setMat4("view",view);
		pLampShader.setMat4("projection",projection);

		glBindVertexArray(lambVAO);
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

void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy)
{
	pCamera.ProcessMouseMovement(posx - lastPosx,posy - lastPosy);

	lastPosx = posx;
	lastPosy = posy;
}

void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety)
{
	pCamera.ProcessMouseScroll(offsety);
}

void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods)
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