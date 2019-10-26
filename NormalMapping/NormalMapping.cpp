//#include "glad/glad.h"
//#include "GLFW/glfw3.h"
//#include "glm/gtc/matrix_transform.hpp"
//#include "../CameraManager.h"
//#include "../Model.h"
//#include "../ShaderManager.h"
//
//#include <iostream>
//#include <string>
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height);
//void processInput(GLFWwindow* pWindow);
//void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy);
//void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods);
//void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety);
//unsigned int loadTexture(const char* path,bool isGamma = false);
//
//CameraManager pCamera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);
//int fps;
//float deltaTime;
//float lastTIme;
//double lastPosx = SCR_WIDTH * 0.5f;
//double lastPosy = SCR_HEIGHT * 0.5f;
//
//float cubeVertices[] = {
//	// positions          // normals           // texture co
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,  
//	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//};
//
//// positions
//glm::vec3 pos1(-1.0,  1.0, 0.0);
//glm::vec3 pos2(-1.0, -1.0, 0.0);
//glm::vec3 pos3(1.0, -1.0, 0.0);
//glm::vec3 pos4(1.0, 1.0, 0.0);
//// texture coordinates
//glm::vec2 uv1(0.0, 1.0);
//glm::vec2 uv2(0.0, 0.0);
//glm::vec2 uv3(1.0, 0.0);
//glm::vec2 uv4(1.0, 1.0);
//// normal vector
//glm::vec3 nm(0.0, 0.0, 1.0);
//
//glm::vec3 lightPos(2.0f, 1.0f, 1.0f);
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
//	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Normal Mapping",NULL,NULL);
//	if (!pWindow)
//	{
//		std::cout << "create window failed !" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(pWindow);
//
//	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
//	{
//		std::cout << "init glad failed !" << std::endl;
//		return -1;
//	}
//
//	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
//	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);
//	glfwSetMouseButtonCallback(pWindow,mouseButton_callback);
//	glfwSetCursorPosCallback(pWindow,mouseMove_callback);
//	glfwSetScrollCallback(pWindow,mouseScroll_callback);
//
//	// calculate tangent/bitangent vectors of both triangles
//	glm::vec3 tangent1, bitangent1;
//	glm::vec3 tangent2, bitangent2;
//	// triangle 1
//	// ----------
//	glm::vec3 edge1 = pos2 - pos1;
//	glm::vec3 edge2 = pos3 - pos1;
//	glm::vec2 deltaUV1 = uv2 - uv1;
//	glm::vec2 deltaUV2 = uv3 - uv1;
//
//	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
//
//	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
//	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
//	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
//	tangent1 = glm::normalize(tangent1);
//
//	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
//	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
//	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
//	bitangent1 = glm::normalize(bitangent1);
//
//	// triangle 2
//	// ----------
//	edge1 = pos3 - pos1;
//	edge2 = pos4 - pos1;
//	deltaUV1 = uv3 - uv1;
//	deltaUV2 = uv4 - uv1;
//
//	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
//
//	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
//	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
//	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
//	tangent2 = glm::normalize(tangent2);
//
//
//	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
//	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
//	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
//	bitangent2 = glm::normalize(bitangent2);
//
//	float plane[] = {
//		// positions            // normal         // texcoords  // tangent                          // bitangent
//		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//
//		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
//		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
//		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
//	};
//	
//
//	unsigned int VAO,VBO;
//	glGenVertexArrays(1,&VAO);
//	glGenBuffers(1,&VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER,VBO);
//	glBufferData(GL_ARRAY_BUFFER,sizeof(plane),&plane,GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,14 * sizeof(GL_FLOAT),(void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,14 * sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,14 * sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
//	glEnableVertexAttribArray(3);
//	glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,14 * sizeof(GL_FLOAT),(void*)(8*sizeof(GL_FLOAT)));
//	glEnableVertexAttribArray(4);
//	glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,14 * sizeof(GL_FLOAT),(void*)(11*sizeof(GL_FLOAT)));
//	glBindBuffer(GL_ARRAY_BUFFER,0);
//	glBindVertexArray(0);
//
//	unsigned int lightVAO,lightVBO;
//	glGenVertexArrays(1,&lightVAO);
//	glGenBuffers(1,&lightVBO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER,lightVBO);
//	glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),cubeVertices,GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(GL_FLOAT),0);
//	glBindBuffer(GL_ARRAY_BUFFER,0);
//	glBindVertexArray(0);
//
//	unsigned int UBO;
//	glGenBuffers(1,&UBO);
//	glBindBuffer(GL_UNIFORM_BUFFER,UBO);
//	glBufferData(GL_UNIFORM_BUFFER,sizeof(glm::mat4) * 2,NULL,GL_STATIC_DRAW);
//	glBindBufferRange(GL_UNIFORM_BUFFER,0,UBO,0,sizeof(glm::mat4) * 2);
//	glBindBuffer(GL_UNIFORM_BUFFER,0);
//
//	ShaderManager pShader("../shaders/NormalMapping/NormalMappint.vs", "../shaders/NormalMapping/NormalMappint.fs");
//	pShader.use();
//	pShader.setInt("texture1",0);
//	pShader.setInt("normalTexture",1);
//	unsigned int texture1 = loadTexture("../resource/textures/brickwall.jpg",false);
//	unsigned int normalTexture = loadTexture("../resource/textures/brickwall_normal.jpg",false);
//	ShaderManager pLightingShader("../shaders/NormalMapping/lighting.vs", "../shaders/NormalMapping/lighting.fs");
//
//	glEnable(GL_DEPTH_TEST);
//
//	while (!glfwWindowShouldClose(pWindow))
//	{
//		processInput(pWindow);
//
//		glClearColor(0.3,0.3,0.3,1.0);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glm::mat4 projection = glm::perspective(glm::radians(pCamera.Zoom),(float)SCR_WIDTH/(float)SCR_HEIGHT,1.0f,100.0f);
//		glm::mat4 view = pCamera.GetLookAt();
//
//		glBindBuffer(GL_UNIFORM_BUFFER,UBO);
//		glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(projection));
//		glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(view));
//		glBindBuffer(GL_UNIFORM_BUFFER,0);
//
//		pShader.use();
//		glm::mat4 model(1.0);
//		//model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); 
//		model = glm::rotate(model,glm::radians(-75.0f),glm::vec3(1.0f,0.0f,0.0f));
//		pShader.setMat4("model",model);
//		pShader.setMat3("NormalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
//		pShader.setVec3("viewPos",pCamera.Position);
//		pShader.setVec3("lightPos",lightPos);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D,texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D,normalTexture);
//		//plane
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES,0,6);
//		//light
//		pLightingShader.use();
//		model = glm::mat4(1.0f);
//		model = glm::translate(model,lightPos);
//		model = glm::scale(model,glm::vec3(0.1,0.1,0.1));
//		pLightingShader.setMat4("model",model);
//		glBindVertexArray(lightVAO);
//		glDrawArrays(GL_TRIANGLES,0,36);
//
//		glBindVertexArray(0);
//		glfwPollEvents();
//		glfwSwapBuffers(pWindow);
//	}
//
//	return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* pWindow,int width,int height)
//{
//	glViewport(0,0,width,height);
//}
//void processInput(GLFWwindow* pWindow)
//{
//	if(glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GLFW_TRUE)
//	{
//		glfwSetWindowShouldClose(pWindow,GLFW_TRUE);
//	}
//
//	if(glfwGetKey(pWindow,GLFW_KEY_W) == GLFW_TRUE)
//	{
//		pCamera.ProcessKeyboardInput(CameraMoveForward,deltaTime);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_S) == GLFW_TRUE)
//	{
//		pCamera.ProcessKeyboardInput(CameraMoveBackward,deltaTime);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_A) == GLFW_TRUE)
//	{
//		pCamera.ProcessKeyboardInput(CameraMoveLeft,deltaTime);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_D) == GLFW_TRUE)
//	{
//		pCamera.ProcessKeyboardInput(CameraMoveRight,deltaTime);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_0) == GLFW_TRUE)
//	{
//		pCamera.SwitchToFace(0);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_1) == GLFW_TRUE)
//	{
//		pCamera.SwitchToFace(1);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_2) == GLFW_TRUE)
//	{
//		pCamera.SwitchToFace(2);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_3) == GLFW_TRUE)
//	{
//		pCamera.SwitchToFace(3);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_4) == GLFW_TRUE)
//	{
//		pCamera.SwitchToFace(4);
//	}
//	if(glfwGetKey(pWindow,GLFW_KEY_5) == GLFW_TRUE)
//	{
//		pCamera.SwitchToFace(5);
//	}
//}
//void mouseMove_callback(GLFWwindow* pWindow,double posx,double posy)
//{
//	pCamera.ProcessMouseMovement(posx - lastPosx,lastPosy - posy);
//	lastPosx = posx;
//	lastPosy = posy;
//}
//void mouseScroll_callback(GLFWwindow* pWindow,double offsetx,double offsety)
//{
//	pCamera.ProcessMouseScroll(offsety);
//}
//void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods)
//{
//	switch (button)
//	{
//	case GLFW_MOUSE_BUTTON_LEFT:
//		if (action == GLFW_PRESS)
//		{
//			pCamera.bMove = true;
//		}
//		else if (action == GLFW_RELEASE)
//		{
//			pCamera.bMove = false;
//		}
//		break;
//	case GLFW_MOUSE_BUTTON_RIGHT:
//		if (action == GLFW_PRESS)
//		{
//			pCamera.bRotate = true;
//		}
//		else if (action == GLFW_RELEASE)
//		{
//			pCamera.bRotate = false;
//		}
//		break;
//	case GLFW_MOUSE_BUTTON_MIDDLE:
//		break;
//	}
//}
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const *path,bool isGamma)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum internalFormat;
//		GLenum dataFormat;
//		if (nrComponents == 1)
//		{
//			internalFormat = dataFormat = GL_RED;
//		}
//		else if (nrComponents == 3)
//		{
//			internalFormat = isGamma ? GL_SRGB : GL_RGB;
//			dataFormat = GL_RGB;
//		}
//		else if (nrComponents == 4)
//		{
//			internalFormat = isGamma ? GL_SRGB_ALPHA : GL_RGBA;
//			dataFormat = GL_RGBA;
//		}
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
