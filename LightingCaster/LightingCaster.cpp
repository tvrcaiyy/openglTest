#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include "stb_image.h"
#include "..\CameraManager.h"
#include "..\ShaderManager.h"

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

void processInput(GLFWwindow* pWindow);
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods);
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);
void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height);
unsigned int loadTexture(const char *path);

float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
float lastPosx = SCR_WIDTH / 2;
float lastPosy = SCR_HEIGHT / 2;

CameraManager pCamera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Lighting Map",NULL,NULL);
	if(!pWindow)
	{
		std::cout << "create window failed !" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "initialize glad failed !" << std::endl;
		return - 1;
	}

	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);
	glfwSetCursorPosCallback(pWindow,mouseMove_callback);
	glfwSetMouseButtonCallback(pWindow,mouseButton_callback);
	glfwSetScrollCallback(pWindow,mouseScroll_callback);

	unsigned int VAO,VBO,lightVAO,lightVBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(GL_FLOAT),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(GL_FLOAT),(void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(GL_FLOAT),(void*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);


	glGenVertexArrays(1,&lightVAO);
	glGenBuffers(1,&lightVBO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER,lightVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(GL_FLOAT),(void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	unsigned int texture1 = loadTexture("../resource/textures/container2.png");
	unsigned int texture2 = loadTexture("../resource/textures/container2_specular.png");

	ShaderManager pShader("vertex.vs","fragment.fs");
	pShader.use();
	glUniform1i(glGetUniformLocation(pShader.ID,"texture1"),0);
	// material properties
	pShader.setInt("material.diffuse",  0);
	pShader.setInt("material.specular", 1);
	pShader.setFloat("material.shininess", 64.0f);
	// light properties
	pShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f); 
	pShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	pShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	pShader.setVec3("light.position",lightPos);
	//pShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
	pShader.setFloat("light.constant",  1.0f);
	pShader.setFloat("light.linear",    0.14f);
	pShader.setFloat("light.quadratic", 0.07f);


	ShaderManager pLightShader("lightVertex.vs","lightFragment.fs");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(pWindow))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		processInput(pWindow);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		pShader.use();

		glm::mat4 view = glm::mat4(1.0f);
		view = pCamera.GetLookAt();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(pCamera.Zoom),(float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f,100.0f);
		pShader.setMat4("view",view);
		pShader.setMat4("projection",projection);
		pShader.setVec3("viewPos",pCamera.Position);

		glBindVertexArray(VAO);
		for (int i = 0; i < 10;i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model,glm::vec3(cubePositions[i]));
			model = glm::rotate(model,glm::radians(i * 20.0f),glm::vec3(1.0f, 0.3f, 0.5f));
			pShader.setMat4("model",model);
			pShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
			
			glDrawArrays(GL_TRIANGLES,0,36);
		}
		

		pLightShader.use();
		glm::mat4 lightModel(1.0f);
		lightModel = glm::translate(lightModel,lightPos);
		lightModel = glm::scale(lightModel,glm::vec3(0.2f,0.2f,0.2f));
		pLightShader.setMat4("model",lightModel);
		pLightShader.setMat4("view",view);
		pLightShader.setMat4("projection",projection);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES,0,36);

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}


	return 0;
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
	pCamera.ProcessMouseMovement(posx - lastPosx,lastPosy - posy);
	lastPosx = posx;
	lastPosy = posy;
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
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety)
{
	pCamera.ProcessMouseScroll(offsety);
}
void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height)
{
	glViewport(0,0,width,height);
}

unsigned int loadTexture(char const* path)
{
	unsigned int texture;
	glGenTextures(1,&texture);

	int imageWidth,imageHeight,nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load(path,&imageWidth,&imageHeight,&nrComponents,0);
	if (imageData)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D,texture);

		glTexImage2D(GL_TEXTURE_2D,0,format,imageWidth,imageHeight,0,format,GL_UNSIGNED_BYTE,imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

		stbi_image_free(imageData);
	}
	else
	{
		std::cout << "load Image: \""<< path << "\" Fialed !" << std::endl;
		stbi_image_free(imageData);
	}
	return texture;
}