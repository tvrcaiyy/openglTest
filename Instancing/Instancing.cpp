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

float quadVertices[] = {
	// 位置          // 颜色
	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
	0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
	-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
	0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
	0.05f,  0.05f,  0.0f, 1.0f, 1.0f                   
};  



CameraManager pCamera(glm::vec3(0.0f,10.0f,100.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);
int fps;
float deltaTime;
float lastTIme;
double lastPosx = SCR_WIDTH * 0.5f;
double lastPosy = SCR_HEIGHT * 0.5f;
int showType = 1;
int main()
{
	string path = "..\\";
	SetDllDirectory(path.c_str());

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Instancing !",NULL,NULL);
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

	glm::vec2 translations[100];
	int index = 0;
	for (int i = -5;i<5;i++)
	{
		for (int j = -5;j<5;j++)
		{
			glm::vec2 offset;
			offset.x = i * 0.2 + 0.1;
			offset.y = j * 0.2 + 0.1;
			translations[index++] = offset;
		}
	}

	unsigned int instanceVBO;
	glGenBuffers(1,&instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER,instanceVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2)*100,&translations[0],GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	unsigned int VAO,VBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),quadVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(2*sizeof(GL_FLOAT)));
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); 
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,2*sizeof(float),0);
	glVertexAttribDivisor(2,1);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);

	unsigned int ubo;
	glGenBuffers(1,&ubo);
	glBindBuffer(GL_UNIFORM_BUFFER,ubo);
	glBufferData(GL_UNIFORM_BUFFER,2 * sizeof(glm::mat4),NULL,GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	glBindBufferRange(GL_UNIFORM_BUFFER,1,ubo,0,2 * sizeof(glm::mat4));
	
	int mount = 100000;
	glm::mat4* modelMatrices = new glm::mat4[mount];
	float radius = 100;
	float offset = 25;
	srand(glfwGetTime());
	for (int i = 0;i < mount;i++)
	{
		glm::mat4 model(1.0);
		float angle = (float)i / (float)mount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100 - offset;
		float posx = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100 - offset;
		float posy = displacement * 0.4f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100 - offset;
		float posz = cos(angle) * radius + displacement;
		model = glm::translate(model,glm::vec3(posx,posy,posz));

		// 2. 缩放：在 0.05 和 0.25f 之间缩放
		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		modelMatrices[i] = model;
	}
	unsigned int modelMatricesVBO;
	glGenBuffers(1,&modelMatricesVBO);
	glBindBuffer(GL_ARRAY_BUFFER,modelMatricesVBO);
	glBufferData(GL_ARRAY_BUFFER,mount * sizeof(glm::mat4),&modelMatrices[0],GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	ShaderManager pShader("../shaders/Instancing/vertex.vs","../shaders/Instancing/fragment.fs");
	ShaderManager pPlantShader("../shaders/Instancing/plantVertex.vs","../shaders/Instancing/plantFragment.fs");
	ShaderManager pRockShader("../shaders/Instancing/rockVertex.vs","../shaders/Instancing/plantFragment.fs");
	//pShader.use();
	//for (int i = 0;i < 100;i++)
	//{
	//	string str = "offsets[" + to_string(i) + "]";
	//	pShader.setVec2(str,translations[i]);
	//}
	Model plantModel("../resource/objects/planet/planet.obj");
	Model rockModel("../resource/objects/rock/rock.obj");

	for (int i = 0;i < rockModel.meshes.size();i++)
	{
		glBindVertexArray(rockModel.meshes[i].VAO);
		glBindBuffer(GL_ARRAY_BUFFER,modelMatricesVBO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3,4,GL_FLOAT,GL_FALSE,4*sizeof(glm::vec4),(void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4,4,GL_FLOAT,GL_FALSE,4*sizeof(glm::vec4),(void*)sizeof(glm::vec4));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5,4,GL_FLOAT,GL_FALSE,4*sizeof(glm::vec4),(void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6,4,GL_FLOAT,GL_FALSE,4*sizeof(glm::vec4),(void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(3,1);
		glVertexAttribDivisor(4,1);
		glVertexAttribDivisor(5,1);
		glVertexAttribDivisor(6,1);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);
	}
	//glPointSize(10);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - lastTIme;
		lastTIme = glfwGetTime();
		processInput(pWindow);
		fps = (int)(1.0f / deltaTime);
		string str = "Instancing ! fps:" + std::to_string(fps);
		glfwSetWindowTitle(pWindow,str.c_str());

		processInput(pWindow);

		glClearColor(0.33f,0.33f,0.33f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = pCamera.GetLookAt();
		glm::mat4 projection = glm::perspective(glm::radians(pCamera.Zoom),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,1000.0f);
		glBindBuffer(GL_UNIFORM_BUFFER,ubo);
		glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(projection));

		//pShader.use();
		//glBindVertexArray(VAO);
		//glDrawArraysInstanced(GL_TRIANGLES,0,6,100);
		pPlantShader.use();
		glm::mat4 model(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		pPlantShader.setMat4("model",model);
		plantModel.Draw(pPlantShader);

		pRockShader.use();
		pRockShader.setInt("type",showType);
		if (showType == 0)
		{
			for (int i = 0;i < mount;i++)
			{
				model = modelMatrices[i];
				pRockShader.setMat4("model",model);
				rockModel.Draw(pRockShader);
			}
		}
		else if(showType == 1)
		{
			pRockShader.setInt("texture_diffuse1", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, rockModel.textures_loaded[0].id);
			for (int i = 0;i < rockModel.meshes.size();i++)
			{
				glBindVertexArray(rockModel.meshes[i].VAO);
				glDrawElementsInstanced(GL_TRIANGLES,rockModel.meshes[i].indices.size(),GL_UNSIGNED_INT,0,mount);
			}
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