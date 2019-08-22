#include "glad/glad.h"
#include "GLFW/glfw3.h"
//#include <GL/glu.h>
#include <iostream>
#include <string>


GLvoid PrintVersion()
{
	const GLubyte* name = glGetString(GL_VENDOR);            //返回负责当前OpenGL实现厂商的名字
	const GLubyte* biaoshifu = glGetString(GL_RENDERER);    //返回一个渲染器标识符，通常是个硬件平台
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);    //返回当前OpenGL实现的版本号
	const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);//返回着色预压编译器版本号
	//const GLubyte* gluVersion = gluGetString(GLU_VERSION);    //返回当前GLU工具库版本
	printf("OpenGL实现厂商的名字：%s\n", name);
	printf("渲染器标识符：%s\n", biaoshifu);
	printf("OpenGL实现的版本号：%s\n", OpenGLVersion);
	printf("OpenGL着色语言版本：%s\n\n", glsl);
	//printf("GLU工具库版本：%s\n", gluVersion);
}

GLenum glCheckError_(const char *file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

const unsigned int SCR_WIDTH = 200;
const unsigned int SCR_HEIGHT = 150;

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height);
void processInput(GLFWwindow* pWindow);

const char* vertexShaderSource = "#version 450 core\n"
	"layout(location = 0) in vec3 Pos;\n"
	"layout(location = 1) in vec3 ourColor;\n"
	"out vec4 VertexColor;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(Pos.xyz,1.0f);\n"
	"VertexColor = vec4(ourColor,1.0f);\n"
	"}\n";
const char* fragShaderSource = "#version 450 core\n"
	"out vec4 FragColor;"
	"in vec4 VertexColor;\n"
	"void main()\n"
	"{\n"
	"FragColor = VertexColor;\n"
	"}\n";
const char* fragShaderSourceYellow = "#version 450 core\n"
	"uniform float greenColor;\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"FragColor = vec4(1.0,greenColor,0,1.0f);\n"
	"}\n";


int main()
{
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE);
	
	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Test",NULL,NULL);
	if(pWindow == NULL)
	{
		std::cout << "create window failed !" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "glad initiate failed !" << std::endl;
		return - 1;
	}
	//放再前面点会报错
	glCheckError();
	PrintVersion();
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS,&flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		std::cout << "initialize context flag debug success !" << std::endl;
	}
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);
	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);

	int vertexShader,fragShader,fragYellowShader,program,yellowProgram;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		std::cout << "compile vertex shader failed:\n" << infoLog << std::endl;  
	}

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader,1,&fragShaderSource,NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(fragShader,512,NULL,infoLog);
		std::cout << "compile frag shader failed:\n" << infoLog << std::endl;  
	}

	fragYellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragYellowShader,1,&fragShaderSourceYellow,NULL);
	glCompileShader(fragYellowShader);
	glGetShaderiv(fragYellowShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(fragYellowShader,512,NULL,infoLog);
		std::cout << "compile frag Yellow Shader failed:\n" << infoLog << std::endl;  
	}
	

	program = glCreateProgram();
	glAttachShader(program,vertexShader);
	glAttachShader(program,fragShader);
	glLinkProgram(program);
	glGetProgramiv(program,GL_LINK_STATUS,&success);
	if (!success)
	{
		glGetProgramInfoLog(program,512,NULL,infoLog);
		std::cout << "link program failed:\n" << infoLog << std::endl;  
	}

	yellowProgram = glCreateProgram();
	glAttachShader(yellowProgram,vertexShader);
	glAttachShader(yellowProgram,fragYellowShader);
	glLinkProgram(yellowProgram);
	glGetProgramiv(yellowProgram,GL_LINK_STATUS,&success);
	if (!success)
	{
		glGetProgramInfoLog(yellowProgram,512,NULL,infoLog);
		std::cout << "link yellowProgram failed:\n" << infoLog << std::endl;  
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	glDeleteShader(fragYellowShader);

	/*float vertices[] = {
		0.5f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};*/
	float firstTriangle[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // 右下
		-0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		-0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
	};
	float secondTriangle[] ={
		// second triangle
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	}; 

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	unsigned int VAO[2],VBO[2],EBO;
	glGenVertexArrays(2,VAO);
	glGenBuffers(2,VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle),firstTriangle,GL_STATIC_DRAW);
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);*/
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);*/
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glCheckError();

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	int greenColorLocation = glGetUniformLocation(yellowProgram,"greenColor");
	while (!glfwWindowShouldClose(pWindow))
	{
		processInput(pWindow);

		//render
		glClearColor(0.33f,0.33f,0.33f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO[0]);
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
		glDrawArrays(GL_TRIANGLES,0,3);
		glUseProgram(yellowProgram);

		float greenColor = sin(glfwGetTime()) / 2 + 0.5f;
		if (greenColorLocation != -1)
		{
			glUniform1f(greenColorLocation,greenColor);
		}

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES,0,3);

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height)
{
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow* pWindow)
{
	if(glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GLFW_TRUE)
		glfwSetWindowShouldClose(pWindow,GLFW_TRUE);
}
