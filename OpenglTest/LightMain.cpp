/*
* 绘制10个立方体，并随着时间旋转
*/
//#include "glad/glad.h"
// Std.Includes
#include <iostream>
#include <string>

// SOIL
#include <SOIL.h>
// GLEW
#define GLEW_STATIC
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Other includes
#include "Shader.h"
#include "Camera.h"

//#pragma comment(lib,"glew32.lib")
// Window dimensions
const GLuint screenWidth = 800, screenHeight = 600;
// Holds uniform value of texture mix
GLfloat mixValue = 0.2f;

// function prototype
void key_callback (GLFWwindow * window, int key, int scancode, int action, int mode);
void mouse_callback (GLFWwindow* window, double xpos, double ypos);
void scroll_callback (GLFWwindow* window, double xoffset, double yoffset);
void Do_movement ();

//// 定义一些摄像机变量
//glm::vec3 cameraPos = glm::vec3 (0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3 (0.0f, 0.0f, -1.0f);		// 从摄像头到目标的方向向量
//glm::vec3 cameraUp = glm::vec3 (0.0f, 1.0f, 0.0f);
//GLfloat lastX = WIDTH / 2.0;
//GLfloat lastY = HEIGHT / 2.0;
//GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
//GLfloat pitch = 0.0f;
//GLfloat aspect = 45.0f;
//bool keys[1024];

// Camera
Camera camera (glm::vec3 (0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = screenWidth / 2.0;
GLfloat lastY = screenWidth / 2.0;
bool firstMouse = true;


// 我们要用两个全局变量来计算出deltaTime值
GLfloat deltaTime = 0.0f;   // 当前帧与上一帧的时间差
GLfloat lastFrame = 0.0f;   // 上一帧的时间
glm::vec3 lightPos (1.2f, 1.0f, 2.0f);
int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit ();
	// Set all the required options for GLFW
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint (GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint (GLFW_SAMPLES, 4);	// ???
	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow (screenWidth, screenHeight, "learning opengl !", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate ();
		return -1;
	}
	glfwMakeContextCurrent (window);

	// Set the required callback functions
	glfwSetKeyCallback (window, key_callback);
	glfwSetCursorPosCallback (window, mouse_callback);
	glfwSetScrollCallback (window, scroll_callback);

	// GLFW Options
	//glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//  let glew use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	if (glewInit () != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	glViewport (0, 0, screenWidth, screenHeight);

	// Setup some OpenGL options
	glEnable (GL_DEPTH_TEST);

	// Build and compile our shader program
	Shader lightingShader ("shaders/lighting.vert", "shaders/lighting.frag");
	Shader lampShader ("shaders/lamp.vert", "shaders/lamp.frag");

	// 36个顶点，绘制一个立方体
	GLfloat vertices[] = {
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

	// 绘制10个立方体
	glm::vec3 cubePositions[] =
	{
		glm::vec3 (0.0f, 0.0f, 0.0f),
		glm::vec3 (2.0f, 5.0f, -15.0f),
		glm::vec3 (-1.5f, -2.2f, -2.5f),
		glm::vec3 (-3.8f, -2.0f, -12.3f),
		glm::vec3 (2.4f, -0.4f, -3.5f),
		glm::vec3 (-1.7f, 3.0f, -7.5f),
		glm::vec3 (1.3f, -2.0f, -2.5f),
		glm::vec3 (1.5f, 2.0f, -2.5f),
		glm::vec3 (1.5f, 0.2f, -1.5f),
		glm::vec3 (-1.3f, 1.0f, -1.5f)
	};

	// VAO, VBO
	GLuint containerVAO, VBO;
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(containerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (GLfloat), (GLvoid*)(3 * sizeof (GLfloat)));	// 法向量坐标
	glEnableVertexAttribArray (1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint lampVAO;
	glGenVertexArrays(1, &lampVAO);
	glBindVertexArray(lampVAO);
	// 只需要绑定VBO不用再次设置VBO的数据，因为容器(物体)的VBO数据中已经包含了正确的立方体顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 设置灯立方体的顶点属性指针(仅设置灯的顶点数据)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	
	/*lightingShader.Use();
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);*/
	GLint objectColorLoc = glGetUniformLocation(lightingShader.Program,"objectColor");
	GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");

	while (!glfwWindowShouldClose (window))
	{
		// 在每一帧中我们计算出新的deltaTime以备后用======================
		GLfloat currentFrame = glfwGetTime ();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents ();
		Do_movement ();

		glClearColor (0.1f, 0.1f, 0.1f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//object
		lightingShader.Use ();
		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		lightPos.x = 1.0f + sin (glfwGetTime ()) * 2.0f;
		lightPos.y = sin (glfwGetTime () / 2.0f) * 1.0f;
		// transformations
		glm::mat4 model;
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective( camera.Zoom, (GLfloat) screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projectionLoc = glGetUniformLocation(lightingShader.Program, "projection");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3f(glGetUniformLocation(lightingShader.Program, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		glBindVertexArray (containerVAO);
		glDrawArrays (GL_TRIANGLES, 0, 36);
		glBindVertexArray (0);

		//lamp
		lampShader.Use();
		
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		view = glm::mat4();
		view = camera.GetViewMatrix();
		projection = glm::mat4();
		projection = glm::perspective (camera.Zoom, (GLfloat) screenWidth / (GLfloat) screenHeight, 0.1f, 100.0f);
		modelLoc = glGetUniformLocation (lampShader.Program, "model");
		viewLoc = glGetUniformLocation (lampShader.Program, "view");
		projectionLoc = glGetUniformLocation (lampShader.Program, "projection");

		glUniformMatrix4fv (modelLoc, 1, GL_FALSE, glm::value_ptr (model));
		glUniformMatrix4fv (viewLoc, 1, GL_FALSE, glm::value_ptr (view));
		glUniformMatrix4fv (projectionLoc, 1, GL_FALSE, glm::value_ptr (projection));

		// Draw the light object (using light's vertex attributes)
		glBindVertexArray (lampVAO);
		glDrawArrays (GL_TRIANGLES, 0, 36);
		glBindVertexArray (0);

		glfwSwapBuffers (window);
	}

	glDeleteVertexArrays (1, &containerVAO);
	glDeleteVertexArrays (1, &lampVAO);
	glDeleteBuffers (1, &VBO);
	glfwTerminate ();

	return 0;
}

void key_callback (GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}


	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose (window, GL_TRUE);
}

void Do_movement ()
{
	// 现在我们有了deltaTime在计算速度的时候可以使用了：
	GLfloat cameraSpeed = 2.0f * deltaTime;
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard (FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard (BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard (LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard (RIGHT, deltaTime);
	if (keys[GLFW_KEY_UP])
	{
		mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}

void mouse_callback (GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;		
	GLfloat yoffset = lastY - ypos;		// Reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement (xoffset, yoffset);
}

void scroll_callback (GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll (yoffset);
}