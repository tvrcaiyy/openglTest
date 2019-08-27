#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <iostream>
#include "../ShaderManager.h"
#include "glm/gtc/matrix_transform.inl"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height);
void processInput(GLFWwindow* pWindow);

float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

unsigned int indice[] = {
	0,1,3,
	1,2,3
};
float mixValue = 0.2f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Texture",NULL,NULL);
	if (pWindow == NULL)
	{
		std::cout << "create window failed !" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "glad initialize failed !" << std::endl;
		return -1;
	}

	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);

	unsigned int VAO,VBO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indice),indice,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	unsigned int texture1;
	glGenTextures(1,&texture1);
	glBindTexture(GL_TEXTURE_2D,texture1);
	
	/*float borderColor[] = {1.0f,1.0f,0.0f,1.0f};
	glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,borderColor);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);*/
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	int imageWidth,imageHeight,colorChannelCount;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load("../resource/textures/container.jpg",&imageWidth,&imageHeight,&colorChannelCount,0);
	if (imageData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(imageData);

	unsigned int texture2;
	glGenTextures(1,&texture2);
	glBindTexture(GL_TEXTURE_2D,texture2);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	imageData = stbi_load("../resource/textures/awesomeface.png",&imageWidth,&imageHeight,&colorChannelCount,0);
	if (imageData)
	{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageWidth,imageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(imageData);

	ShaderManager pShader("vertex.vs","fragment.fs");
	pShader.use();
	glUniform1i(glGetUniformLocation(pShader.ID,"texture1"),0);
	glUniform1i(glGetUniformLocation(pShader.ID,"texture2"),1);

	while (!glfwWindowShouldClose(pWindow))
	{
		processInput(pWindow);

		glClearColor(0.33f,0.33f,0.33f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		pShader.use();
		glm::mat4 tran = glm::mat4(1.0);
		//tran = glm::rotate(tran,(float)(glfwGetTime() * 0.3f),glm::vec3(0.0,0.0,1.0f));
		tran = glm::scale(tran,glm::vec3(0.5f,0.5f,0.5f));
		tran = glm::translate(tran,glm::vec3(0.5f,-0.5f,0));
		int tranformLocation = glGetUniformLocation(pShader.ID,"transform");
		glUniformMatrix4fv(tranformLocation,1,GL_FALSE,glm::value_ptr(tran));
		pShader.setFloat("mixValue",mixValue);
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH / SCR_HEIGHT,0.1f,100.0f);
		pShader.setMat4("view",view);
		pShader.setMat4("projection",projection);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);

		tran = glm::mat4(1.0f); // reset it to identity matrix
		tran = glm::translate(tran, glm::vec3(-0.5f, 0.5f, 0.0f));
		double scaleAmount = sin(glfwGetTime());
		tran = glm::scale(tran, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		glUniformMatrix4fv(tranformLocation, 1, GL_FALSE, &tran[0][0]); // this time take the matrix value array's first element as its memory pointer value

		// now with the uniform matrix being replaced with new transformations, draw it again.
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height)
{
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow* pWindow)
{
	if (glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GLFW_TRUE)
	{
		glfwSetWindowShouldClose(pWindow,GLFW_TRUE);
	}
	if (glfwGetKey(pWindow,GLFW_KEY_DOWN) == GLFW_TRUE)
	{
		mixValue -= 0.01f;
		if (mixValue < 0)
			mixValue = 0.0f;
	}
	if (glfwGetKey(pWindow,GLFW_KEY_UP) == GLFW_TRUE)
	{
		mixValue += 0.01f;
		if (mixValue > 1)
			mixValue = 1.0f;
	}
}