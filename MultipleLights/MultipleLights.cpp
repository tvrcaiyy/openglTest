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

// positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3( 0.7f,  0.2f,  2.0f),
	glm::vec3( 2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3( 0.0f,  0.0f, -3.0f)
};

void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height);
void processInput(GLFWwindow* pWindow);
void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);
void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods);
unsigned int loadTexture(const char *path);

CameraManager pCamera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);

float deltaTime = 0.0f;
float lastTime = 0.0f;
float lastPosx = SCR_WIDTH * 0.5f;
float lastPosy = SCR_HEIGHT * 0.5f;
float linear = 0.22f;
float quadratic = 0.20f;
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

	unsigned int texture1 = loadTexture("../resource/textures/container2.png");
	unsigned int texture2 = loadTexture("../resource/textures/container2_specular.png");

	ShaderManager pLampShader("lampVertex.vs","lampFragment.fs");
	ShaderManager pShader("vertex.vs","fragment.fs");
	pShader.use();

	pShader.setInt("material.diffuse", 0);
	pShader.setInt("material.specular", 1);
	pShader.setFloat("material.shininess", 64.0f);
	// directional light
	pShader.setVec3("dirLight.lightDir", -0.2f, -1.0f, -0.3f);
	pShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	pShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	pShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	pShader.setVec3("pointLights[0].lightPos", pointLightPositions[0]);
	pShader.setVec3("pointLights[0].ambient", 0.05f, 0.0f, 0.0f);
	pShader.setVec3("pointLights[0].diffuse", 0.8f, 0.0f, 0.0f);
	pShader.setVec3("pointLights[0].specular", 1.0f, 0.0f, 0.0f);
	pShader.setFloat("pointLights[0].constant", 1.0f);
	pShader.setFloat("pointLights[0].linear", linear);
	pShader.setFloat("pointLights[0].quadratic", quadratic);
	// point light 2
	pShader.setVec3("pointLights[1].lightPos", pointLightPositions[1]);
	pShader.setVec3("pointLights[1].ambient", 0.0f, 0.05f, 0.00f);
	pShader.setVec3("pointLights[1].diffuse", 0.0f, 0.8f, 0.0f);
	pShader.setVec3("pointLights[1].specular", 0.0f, 1.0f, 0.0f);
	pShader.setFloat("pointLights[1].constant", 1.0f);
	pShader.setFloat("pointLights[1].linear", linear);
	pShader.setFloat("pointLights[1].quadratic", quadratic);
	// point light 3
	pShader.setVec3("pointLights[2].lightPos", pointLightPositions[2]);
	pShader.setVec3("pointLights[2].ambient", 0.0f, 0.0f, 0.05f);
	pShader.setVec3("pointLights[2].diffuse", 0.0f, 0.0f, 0.8f);
	pShader.setVec3("pointLights[2].specular", 0.0f, 0.0f, 1.0f);
	pShader.setFloat("pointLights[2].constant", 1.0f);
	pShader.setFloat("pointLights[2].linear", linear);
	pShader.setFloat("pointLights[2].quadratic", quadratic);
	// point light 4
	pShader.setVec3("pointLights[3].lightPos", pointLightPositions[3]);
	pShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.0f);
	pShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.0f);
	pShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 0.0f);
	pShader.setFloat("pointLights[3].constant", 1.0f);
	pShader.setFloat("pointLights[3].linear", linear);
	pShader.setFloat("pointLights[3].quadratic", quadratic);
	// spotLight
	pShader.setVec3("spotLight.ambient", 0.1f, 0.1f, 0.1f);
	pShader.setVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
	pShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	pShader.setFloat("spotLight.constant", 1.0f);
	pShader.setFloat("spotLight.linear", 0.14f);
	pShader.setFloat("spotLight.quadratic", 0.07f);
	pShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	pShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));  

	glm::vec3 lightPos(1.2f,1.0f,2.0f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		processInput(pWindow);

		glClearColor(0.1f,0.1f,0.1f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//cubes
		glActiveTexture(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glm::mat4 view(1.0f);
		view = pCamera.GetLookAt();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(pCamera.Zoom),(float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f,100.0f);
		pShader.use();
		pShader.setMat4("view",view);
		pShader.setMat4("projection",projection);
		pShader.setVec3("spotLight.lightPos", pCamera.Position);
		pShader.setVec3("spotLight.direction", pCamera.Front);
		pShader.setVec3("viewPos", pCamera.Position);

		glBindVertexArray(VAO);
		for (int i = 0; i < 10;i++)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model,cubePositions[i]);
			model = glm::rotate(model,glm::radians(i*20.0f),glm::vec3(1.0f, 0.3f, 0.5f));
			pShader.setMat4("model",model);
			pShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
			glDrawArrays(GL_TRIANGLES,0,36);
		}

		//lamb
		pLampShader.use();
		pLampShader.setMat4("view",view);
		pLampShader.setMat4("projection",projection);
		glBindVertexArray(lambVAO);
		for (int i = 0; i< 4;i++)
		{
			glm::mat4 lambModel(1.0f);
			lambModel = glm::translate(lambModel,glm::vec3(pointLightPositions[i]));
			lambModel = glm::scale(lambModel,glm::vec3(0.1f));
			pLampShader.setMat4("model",lambModel);
			glDrawArrays(GL_TRIANGLES,0,36);
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

unsigned int loadTexture(const char *path)
{
	unsigned int texture;

	stbi_set_flip_vertically_on_load(true);
	int imageWidth,imageHeight,nrComponent;
	unsigned char* imageData = stbi_load(path,&imageWidth,&imageHeight,&nrComponent,0);
	if (imageData)
	{
		GLenum format;
		if (nrComponent == 1)
			format = GL_RED;
		if (nrComponent == 3)
			format = GL_RGB;
		if (nrComponent == 4)
			format = GL_RGBA;

		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexImage2D(GL_TEXTURE_2D,0,format,imageWidth,imageHeight,0,format,GL_UNSIGNED_BYTE,imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

		stbi_image_free(imageData);
	}
	else
	{
		std::cout << "load image failed : " << path << std::endl;
		stbi_image_free(imageData);
	}
	return texture;
}