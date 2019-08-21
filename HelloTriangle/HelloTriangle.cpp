#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height);
void processInput(GLFWwindow* pWindow);
void display();

float vertices[] = {
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
};

unsigned int indices[] = {
	0,1,3,
	1,2,3
};

const char* vertexShaderSource = "#version 330 core\n"
	"layout(location = 0) in vec3 Pos;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(Pos.x,Pos.y,Pos.z,1.0);\n"
	"}\n";
const char* fragShaderSource = "#version 330 core\n"
	"out vec4 FragColor;"
	"void main()\n"
	"{\n"
	"FragColor = vec4(1.0,0,0,1.0);\n"
	"}\n";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(SRC_WIDTH,SRC_HEIGHT,"HelloTriangle",NULL,NULL);
	if(pWindow == NULL)
	{
		std::cout << "create window failed !!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(pWindow);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initilize GLAD !" << std::endl;
		return -1;
	}

	glViewport(0,0,SRC_WIDTH,SRC_HEIGHT);

	glfwSetFramebufferSizeCallback(pWindow,framebuffer_size_callback);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	GLint success;
	char infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		std::cout << "Error: Vertex Shader Compile Failed:\n" << infoLog << std::endl;
	}

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader,1,&fragShaderSource,NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(fragShader,512,NULL,infoLog);
		std::cout << "Error: Frag Shader Compile Failed:\n" << infoLog << std::endl;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program,vertexShader);
	glAttachShader(program,fragShader);
	glLinkProgram(program);
	glGetProgramiv(program,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetProgramInfoLog(program,512,NULL,infoLog);
		std::cout << "Error: Link Program Failed:\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	GLuint vao,vbo,ebo;
	glGenVertexArrays(1,&vao);
	glGenBuffers(1,&vbo);
	glGenBuffers(1,&ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(pWindow))
	{
		processInput(pWindow);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		glfwPollEvents();
		glfwSwapBuffers(pWindow);
	}

	glfwTerminate();

	return 0;
}

void display()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width,int height)
{
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow* pWindow)
{
	if(glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GL_TRUE)
	{
		glfwSetWindowShouldClose(pWindow,GL_TRUE);
	}
}