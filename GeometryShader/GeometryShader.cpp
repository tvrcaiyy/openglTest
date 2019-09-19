#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include <wtypes.h>
#include "glm/gtc/matrix_transform.hpp"
#include "../utility/CameraManager.h"
#include "../utility/ShaderManager.h"
#include "../utility/Model.h"

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height);
void processInput(GLFWwindow* pWindow);
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);
void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods);

float points[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
	0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
};



CameraManager pCamera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);
int fps;
float deltaTime;
float lastTIme;
double lastPosx = SCR_WIDTH * 0.5f;
double lastPosy = SCR_HEIGHT * 0.5f;
int showType;
int main()
{
	string path = "..\\";
	SetDllDirectory(path.c_str());

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
	glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(2*sizeof(GL_FLOAT)));
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	unsigned int ubo;
	glGenBuffers(1,&ubo);
	glBindBuffer(GL_UNIFORM_BUFFER,ubo);
	glBufferData(GL_UNIFORM_BUFFER,2 * sizeof(glm::mat4),NULL,GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	glBindBufferRange(GL_UNIFORM_BUFFER,1,ubo,0,2 * sizeof(glm::mat4));

	ShaderManager pShader("../shaders/GeometryShader/vertex.vs","../shaders/GeometryShader/fragment.fs","../shaders/GeometryShader/geometry.gs");
	ShaderManager ourShader("../shaders/GeometryShader/modelVertex.vs", "../shaders/GeometryShader/modelFragment.fs","../shaders/GeometryShader/modelGeometry.gs");
	ShaderManager pNormalShader("../shaders/GeometryShader/visualNormalVertex.vs", "../shaders/GeometryShader/visualNormalFragment.fs","../shaders/GeometryShader/visualNormalGeometry.gs");
	Model ourModel("../resource/objects/nanosuit/nanosuit.obj");

	//glPointSize(10);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - lastTIme;
		lastTIme = glfwGetTime();
		processInput(pWindow);
		fps = (int)(1.0f / deltaTime);
		string str = "GeometryShader ! fps:" + std::to_string(fps);
		glfwSetWindowTitle(pWindow,str.c_str());

		processInput(pWindow);

		glClearColor(0.33f,0.33f,0.33f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = pCamera.GetLookAt();
		glm::mat4 projection = glm::perspective(glm::radians(pCamera.Zoom),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);
		glBindBuffer(GL_UNIFORM_BUFFER,ubo);
		glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(projection));

		pShader.use();
		glm::mat4 model(1.0);
		model = glm::translate(model,glm::vec3(2.0,0.0,0.0));
		pShader.setMat4("model",model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS,0,4);

		ourShader.use();
		ourShader.setFloat("time", glfwGetTime());
		ourShader.setInt("type", showType);
		// render the loaded model
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.3f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		ourModel.Draw(ourShader);

		if (showType == 1)
		{
			pNormalShader.use();
			// render the loaded model
			pNormalShader.setMat4("model", model);
			ourModel.Draw(pNormalShader);
		}

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
		showType = 0;
	}
	if(glfwGetKey(pWindow,GLFW_KEY_1) == GLFW_TRUE)
	{
		showType = 1;
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