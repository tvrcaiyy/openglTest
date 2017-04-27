// /*
// * 绘制10个立方体，并随着时间旋转
// */
// 
// // Std.Includes
// #include <iostream>
// #include <string>
// 
// // SOIL
// #include <SOIL.h>
// // GLEW
// #define GLEW_STATIC
// #include <GL/glew.h>
// // GLFW
// #include <GLFW/glfw3.h>
// // GLM
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// // Other includes
// #include "Shader.h"
// #include "Camera.h"
// 
// // Window dimensions
// const GLuint screenWidth = 800, screenHeight = 600;
// // Holds uniform value of texture mix
// GLfloat mixValue = 0.2f;
// 
// // function prototype
// void key_callback (GLFWwindow * window, int key, int scancode, int action, int mode);
// void mouse_callback (GLFWwindow* window, double xpos, double ypos);
// void scroll_callback (GLFWwindow* window, double xoffset, double yoffset);
// void Do_movement ();
// 
// //// 定义一些摄像机变量
// //glm::vec3 cameraPos = glm::vec3 (0.0f, 0.0f, 3.0f);
// //glm::vec3 cameraFront = glm::vec3 (0.0f, 0.0f, -1.0f);		// 从摄像头到目标的方向向量
// //glm::vec3 cameraUp = glm::vec3 (0.0f, 1.0f, 0.0f);
// //GLfloat lastX = WIDTH / 2.0;
// //GLfloat lastY = HEIGHT / 2.0;
// //GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
// //GLfloat pitch = 0.0f;
// //GLfloat aspect = 45.0f;
// //bool keys[1024];
// 
// // Camera
// Camera camera (glm::vec3 (0.0f, 0.0f, 3.0f));
// bool keys[1024];
// GLfloat lastX = screenWidth / 2.0;
// GLfloat lastY = screenWidth / 2.0;
// bool firstMouse = true;
// 
// 
// // 我们要用两个全局变量来计算出deltaTime值
// GLfloat deltaTime = 0.0f;   // 当前帧与上一帧的时间差
// GLfloat lastFrame = 0.0f;   // 上一帧的时间
// 
// int main1 ()
// {
// 	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
// 	// Init GLFW
// 	glfwInit ();
// 	// Set all the required options for GLFW
// 	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
// 	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// 	glfwWindowHint (GLFW_RESIZABLE, GL_FALSE);
// 	glfwWindowHint (GLFW_SAMPLES, 4);	// ???
// 	// Create a GLFWwindow object that we can use for GLFW's functions
// 	GLFWwindow* window = glfwCreateWindow (screenWidth, screenHeight, "Spinning boxes!", nullptr, nullptr);
// 	if (window == nullptr)
// 	{
// 		std::cout << "Failed to create GLFW window" << std::endl;
// 		glfwTerminate ();
// 		return -1;
// 	}
// 	glfwMakeContextCurrent (window);
// 
// 	// Set the required callback functions
// 	glfwSetKeyCallback (window, key_callback);
// 	glfwSetCursorPosCallback (window, mouse_callback);
// 	glfwSetScrollCallback (window, scroll_callback);
// 
// 	// GLFW Options
// 	glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
// 
// 	//  let glew use a modern approach to retrieving function pointers and extensions
// 	glewExperimental = GL_TRUE;
// 	if (glewInit () != GLEW_OK)
// 	{
// 		std::cout << "Failed to initialize GLEW" << std::endl;
// 		return -1;
// 	}
// 
// 	// Define the viewport dimensions
// 	glViewport (0, 0, screenWidth, screenHeight);
// 
// 	// Setup some OpenGL options
// 	glEnable (GL_DEPTH_TEST);
// 
// 	// Build and compile our shader program
// 	Shader ourShader ("shaders/textures.vert", "shaders/textures.frag");
// 
// 	// 36个顶点，绘制一个立方体
// 	GLfloat vertices[] = {
// 		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
// 		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
// 		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
// 
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
// 		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 
// 		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 
// 		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
// 		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
// 		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
// 	};
// 
// 	// 绘制10个立方体
// 	glm::vec3 cubePositions[] =
// 	{
// 		glm::vec3 (0.0f, 0.0f, 0.0f),
// 		glm::vec3 (2.0f, 5.0f, -15.0f),
// 		glm::vec3 (-1.5f, -2.2f, -2.5f),
// 		glm::vec3 (-3.8f, -2.0f, -12.3f),
// 		glm::vec3 (2.4f, -0.4f, -3.5f),
// 		glm::vec3 (-1.7f, 3.0f, -7.5f),
// 		glm::vec3 (1.3f, -2.0f, -2.5f),
// 		glm::vec3 (1.5f, 2.0f, -2.5f),
// 		glm::vec3 (1.5f, 0.2f, -1.5f),
// 		glm::vec3 (-1.3f, 1.0f, -1.5f)
// 	};
// 
// 	// VAO, VBO
// 	GLuint VAO, VBO;
// 	glGenVertexArrays (1, &VAO);
// 	glGenBuffers (1, &VBO);
// 	glBindVertexArray (VAO);
// 	glBindBuffer (GL_ARRAY_BUFFER, VBO);
// 	glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);		// 试一下GL_DYNAMIC_DRAW，和GL_STREAM_DRAW
// 	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (GLfloat), (GLvoid*) 0);
// 	glEnableVertexAttribArray (0);
// 	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (GLfloat), (GLvoid*) (3 * sizeof (GLfloat)));
// 	glEnableVertexAttribArray (1);
// 	glBindBuffer (GL_ARRAY_BUFFER, 0);
// 	glBindVertexArray (0);
// 
// 	// Textures
// 	GLuint texture1;
// 	glGenTextures (1, &texture1);
// 	glBindTexture (GL_TEXTURE_2D, texture1);
// 	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	int width, height;
// 	unsigned char* image = SOIL_load_image ("1.jpg", &width, &height, 0, SOIL_LOAD_RGB);
// 	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 	glGenerateMipmap (GL_TEXTURE_2D);
// 	SOIL_free_image_data (image);
// 	glBindTexture (GL_TEXTURE_2D, 0);
// 
// 	GLuint texture2;
// 	glGenTextures (1, &texture2);
// 	glBindTexture (GL_TEXTURE_2D, texture2);
// 	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	image = SOIL_load_image ("2.png", &width, &height, 0, SOIL_LOAD_RGB);
// 	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 	glGenerateMipmap (GL_TEXTURE_2D);
// 	SOIL_free_image_data (image);
// 	glBindTexture (GL_TEXTURE_2D, 0);
// 
// 	while (!glfwWindowShouldClose (window))
// 	{
// 		// 在每一帧中我们计算出新的deltaTime以备后用======================
// 		GLfloat currentFrame = glfwGetTime ();
// 		deltaTime = currentFrame - lastFrame;
// 		lastFrame = currentFrame;
// 
// 		glfwPollEvents ();
// 		Do_movement ();
// 
// 		glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
// 		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 		ourShader.Use ();
// 
// 		// 先绑定两个纹理到相应的纹理单元，然后定义哪个uniform采样器对应哪个纹理单元：
// 		glActiveTexture (GL_TEXTURE0);
// 		glBindTexture (GL_TEXTURE_2D, texture1);
// 		glUniform1i (glGetUniformLocation (ourShader.Program, "ourTexture1"), 0);
// 		glActiveTexture (GL_TEXTURE1);
// 		glBindTexture (GL_TEXTURE_2D, texture2);
// 		glUniform1i (glGetUniformLocation (ourShader.Program, "ourTexture2"), 1);
// 
// 		glUniform1f (glGetUniformLocation (ourShader.Program, "mixValue"), mixValue);
// 
// 		// transformations
// 		glm::mat4 view;
// 		view = camera.GetViewMatrix ();
// 		glm::mat4 projection;
// 		projection = glm::perspective (camera.Zoom, (float) screenWidth / (float) screenHeight, 0.1f, 1000.0f);
// 
// 
// 		glUniformMatrix4fv (glGetUniformLocation (ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr (view));
// 		glUniformMatrix4fv (glGetUniformLocation (ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr (projection));
// 
// 		glBindVertexArray (VAO);
// 		for (GLint i = 0; i < 10; i++)
// 		{
// 			glm::mat4 model;
// 			model = glm::translate (model, cubePositions[i]);
// 			GLfloat angle = 20.0f * i;
// 			model = glm::rotate (model, angle, glm::vec3 (1.0, 0.3, 0.5));
// 			model = glm::rotate (model, (GLfloat) glfwGetTime () * glm::radians (50.0f), glm::vec3 (0.5f, 1.0f, 0.0f));
// 			glUniformMatrix4fv (glGetUniformLocation (ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr (model));
// 
// 			//	glBindVertexArray (VAO);
// 			glDrawArrays (GL_TRIANGLES, 0, 36);
// 			model = glm::mat4 ();
// 		}
// 		glBindVertexArray (0);
// 		glfwSwapBuffers (window);
// 	}
// 
// 	glDeleteVertexArrays (1, &VAO);
// 	glDeleteBuffers (1, &VBO);
// 	glfwTerminate ();
// 
// 	return 0;
// }
// 
// void key_callback (GLFWwindow * window, int key, int scancode, int action, int mode)
// {
// 	if (key >= 0 && key <= 1024)
// 	{
// 		if (action == GLFW_PRESS)
// 			keys[key] = true;
// 		else if (action == GLFW_RELEASE)
// 			keys[key] = false;
// 	}
// 
// 
// 	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
// 		glfwSetWindowShouldClose (window, GL_TRUE);
// }
// 
// void Do_movement ()
// {
// 	// 现在我们有了deltaTime在计算速度的时候可以使用了：
// 	GLfloat cameraSpeed = 2.0f * deltaTime;
// 	if (keys[GLFW_KEY_W])
// 		camera.ProcessKeyboard (FORWARD, deltaTime);
// 	if (keys[GLFW_KEY_S])
// 		camera.ProcessKeyboard (BACKWARD, deltaTime);
// 	if (keys[GLFW_KEY_A])
// 		camera.ProcessKeyboard (LEFT, deltaTime);
// 	if (keys[GLFW_KEY_D])
// 		camera.ProcessKeyboard (RIGHT, deltaTime);
// 	if (keys[GLFW_KEY_UP])
// 	{
// 		mixValue += 0.1f;
// 		if (mixValue >= 1.0f)
// 			mixValue = 1.0f;
// 		if (mixValue <= 0.0f)
// 			mixValue = 0.0f;
// 	}
// }
// 
// void mouse_callback (GLFWwindow* window, double xpos, double ypos)
// {
// 	if (firstMouse)
// 	{
// 		lastX = xpos;
// 		lastY = ypos;
// 		firstMouse = false;
// 	}
// 
// 	GLfloat xoffset = xpos - lastX;		
// 	GLfloat yoffset = lastY - ypos;		// Reversed since y-coordinates range from bottom to top
// 	lastX = xpos;
// 	lastY = ypos;
// 
// 	camera.ProcessMouseMovement (xoffset, yoffset);
// }
// 
// void scroll_callback (GLFWwindow* window, double xoffset, double yoffset)
// {
// 	camera.ProcessMouseScroll (yoffset);
// }