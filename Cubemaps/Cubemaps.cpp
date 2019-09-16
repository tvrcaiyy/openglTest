#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "../CameraManager.h"
#include "../ShaderManager.h"
#include "../Model.h"
#include "glm/gtc/matrix_transform.hpp"
#include <wtypes.h>

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height);
void processInput(GLFWwindow* pWindow);
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);
void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods);

unsigned int loadTexture(char const *path);
unsigned int loadCubemap(vector<std::string> faces);

float deltaTime;
float lastTIme;
double lastPosx = SCR_WIDTH * 0.5f;
double lastPosy = SCR_HEIGHT * 0.5f;
CameraManager pCamera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);
CameraManager pEnvironmentCamera(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);

float cubeVertices[] = {
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
float planeVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,


	5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f

};

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

int main()
{
	string path = "..\\";
	SetDllDirectory(path.c_str());

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Cube Map !",NULL,NULL);
	if (!pWindow)
	{
		std::cout << "create window failed !" << std::endl;
		glfwTerminate();
		return -1;
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
	glfwSetMouseButtonCallback(pWindow,mouseButton_callback);
	glfwSetScrollCallback(pWindow,mouseScroll_callback);

	//unsigned int planeVAO,planeVBO;
	//glGenVertexArrays(1,&planeVAO);
	//glGenBuffers(1,&planeVBO);
	//glBindVertexArray(planeVAO);
	//glBindBuffer(GL_ARRAY_BUFFER,planeVBO);
	//glBufferData(GL_ARRAY_BUFFER,sizeof(planeVertices),planeVertices,GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
	//glBindVertexArray(0);
	// cube VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	unsigned int skyboxVAO,skyboxVBO;
	glGenVertexArrays(1,&skyboxVAO);
	glGenBuffers(1,&skyboxVBO);

	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER,skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	unsigned int cubeTexture = loadTexture("../resource/textures/container.jpg");
	unsigned int floorTexture = loadTexture("../resource/textures/marbel.jpg");

	vector<std::string> faces;
	faces.push_back("../resource/textures/skybox/right.jpg");
	faces.push_back("../resource/textures/skybox/left.jpg");
	faces.push_back("../resource/textures/skybox/top.jpg");
	faces.push_back("../resource/textures/skybox/bottom.jpg");
	faces.push_back("../resource/textures/skybox/front.jpg");
	faces.push_back("../resource/textures/skybox/back.jpg");
	unsigned int cubemapTexture = loadCubemap(faces);

	ShaderManager pCubeShader("shaders/cubeVertex.vs", "shaders/cubeFragment.fs");
	ShaderManager pModelShader("shaders/modelVertex.vs", "shaders/modelFragment.fs");
	ShaderManager pSkyShader("shaders/skyboxVertex.vs", "shaders/skyboxFragment.fs");
	pSkyShader.use();
	pSkyShader.setInt("skybox",0);
	pCubeShader.use();
	pCubeShader.setInt("texture1",0);
	pModelShader.use();
	pModelShader.setInt("texture1",4);

	unsigned int fbo;
	glGenFramebuffers(1,&fbo);
	glBindFramebuffer(GL_FRAMEBUFFER,fbo);
	unsigned int framebufferTexture;
	glGenTextures(1,&framebufferTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP,framebufferTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	for (int i = 0;i < 6;i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,GL_RGB,SCR_WIDTH,SCR_WIDTH,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP,0);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X,framebufferTexture,0);

	unsigned int rbo;
	glGenRenderbuffers(1,&rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,SCR_WIDTH,SCR_WIDTH);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "error::framebuffer:: framebuffer is not complete !" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	//ShaderManager ourShader("vertex.vs", "fragment.fs");
	//Model ourModel("../resource/objects/nanosuit_reflection/nanosuit.obj");
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - lastTIme;
		lastTIme = glfwGetTime();
		processInput(pWindow);
		
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = pEnvironmentCamera.GetLookAt();
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);

		//draw cube map
		{
			glViewport(0, 0, (GLsizei)SCR_WIDTH, (GLsizei)SCR_WIDTH);

			glBindFramebuffer(GL_FRAMEBUFFER,fbo);
			glBindTexture(GL_TEXTURE_CUBE_MAP,0);
			
			for (int i = 0;i < 6;i++)
			{
				pEnvironmentCamera.SwitchToFace(i);
				glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,framebufferTexture,0);

				glClearColor(0.33f,0.33f,0.33f,1.0f);
				glClear(GL_DEPTH_BUFFER_BIT);

				//pModelShader.use();
				//model = glm::mat4(1.0f);
				//model = glm::translate(model,glm::vec3(3.0,0.0,0.0));
				//model = glm::scale(model,glm::vec3(0.2f,0.2f,0.2f));
				//pModelShader.setMat4("model", model);
				//pModelShader.setMat4("view", view);
				//pModelShader.setMat4("projection", projection);
				//pModelShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
				//pModelShader.setVec3("viewPos",pEnvironmentCamera.Position);
				//glActiveTexture(GL_TEXTURE4);
				//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
				//ourModel.Draw(pModelShader);

				glBindVertexArray(0);
				glDepthFunc(GL_LEQUAL);
				pSkyShader.use();
				view = glm::mat4(glm::mat3(pEnvironmentCamera.GetLookAt()));
				pSkyShader.setMat4("view",view);
				pSkyShader.setMat4("projection",projection);
				glBindVertexArray(skyboxVAO);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);
				glDrawArrays(GL_TRIANGLES,0,36);
				glDepthFunc(GL_LESS);
			}
		}
		
		glViewport(0, 0, (GLsizei)SCR_WIDTH, (GLsizei)SCR_HEIGHT);
		view = pCamera.GetLookAt();
		glm::mat4 objProjection = glm::perspective(glm::radians(pCamera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glClearColor(0.33f,0.33f,0.33f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// draw scene as normal
		pCubeShader.use();
		pCubeShader.setMat4("model", model);
		pCubeShader.setMat4("view", view);
		pCubeShader.setMat4("projection", objProjection);
		pCubeShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
		pCubeShader.setVec3("viewPos",pCamera.Position);
		// cubes
		//glBindVertexArray(cubeVAO);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);

		//pModelShader.use();
		//model = glm::mat4(1.0f);
		//model = glm::translate(model,glm::vec3(3.0,0.0,0.0));
		//model = glm::scale(model,glm::vec3(0.2f,0.2f,0.2f));
		//pModelShader.setMat4("model", model);
		//pModelShader.setMat4("view", view);
		//pModelShader.setMat4("projection", objProjection);
		//pModelShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
		//pModelShader.setVec3("viewPos",pCamera.Position);
		//glActiveTexture(GL_TEXTURE4);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		//ourModel.Draw(pModelShader);

		// floor
		//glBindVertexArray(planeVAO);
		//glBindTexture(GL_TEXTURE_2D, floorTexture);
		//pCubeShader.setMat4("model", glm::mat4(1.0f));
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);
		glDepthFunc(GL_LEQUAL);
		pSkyShader.use();
		view = glm::mat4(glm::mat3(pCamera.GetLookAt()));
		pSkyShader.setMat4("view",view);
		pSkyShader.setMat4("projection",objProjection);
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP,framebufferTexture);
		glDrawArrays(GL_TRIANGLES,0,36);
		glDepthFunc(GL_LESS);

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}

	glDeleteVertexArrays(1,&skyboxVAO);
	glDeleteBuffers(1,&skyboxVBO);

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
// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const *path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int cubemapTexture;
	glGenTextures(1,&cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);

	int width,height,nrComponents;
	for (int i = 0;i < faces.size();i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(),&width,&height,&nrComponents,0);
		GLenum format;
		if(nrComponents == 1)
			format = GL_RED;
		else if(nrComponents == 3)
			format = GL_RGB;
		else if(nrComponents == 4)
			format = GL_RGBA;
		if(data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	return cubemapTexture;
}