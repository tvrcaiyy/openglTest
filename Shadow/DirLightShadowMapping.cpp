/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ShaderManager.h"
#include "../CameraManager.h"
#include "../Model.h"

#include <iostream>
#include <map>

void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);
void mouseMove_callback(GLFWwindow* pWindow, double xpos, double ypos);
void mouseScroll_callback(GLFWwindow* pWindow, double xoffset, double yoffset);
void mouseButton_callback(GLFWwindow* pWindow,int button,int action,int mods);
void processInput(GLFWwindow* pWindow);
unsigned int loadTexture(const char* path,bool isGamma = false);
void RenderScene(ShaderManager& pShader,bool drawLight);
// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
	// Front face
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
	// Left face
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
	// Right face
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
	// Top face
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left        
};
float planeVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

	25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
	25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f

};
float ScreenTextureVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
	1.0f, -1.0f, 0.0f,  1.0f, 0.0f,

	-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
	1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
	1.0f,  1.0f, 0.0f,  1.0f, 1.0f

};
glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
unsigned int cubeVAO,planeVAO,cubeTexture,floorTexture,shaderTexture,lightingVAO;
// camera
CameraManager pCamera(glm::vec3(0.0f,2.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),SLG);
float lastPosx = (float)SCR_WIDTH  / 2.0;
float lastPosy = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
GLfloat near_plane = 0.1f, far_plane = 100.0f;
bool showShadowMapping = false;
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES,4);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (pWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindow);
	glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
	glfwSetCursorPosCallback(pWindow, mouseMove_callback);
	glfwSetScrollCallback(pWindow, mouseScroll_callback);
	glfwSetMouseButtonCallback(pWindow,mouseButton_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_MULTISAMPLE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CW);
	// build and compile shaders
	// -------------------------
	ShaderManager pShader("../shaders/Shadow/dirLightVertex.vs", "../shaders/Shadow/dirLightFragment.fs");
	ShaderManager pShadowShader("../shaders/Shadow/shadowVertex.vs", "../shaders/Shadow/shadowFragment.fs");
	ShaderManager pScreenShader("../shaders/Shadow/screenVertex.vs", "../shaders/Shadow/screenFragment.fs");
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	unsigned int cubeVBO;
	glGenVertexArrays(1,&cubeVAO);
	glGenBuffers(1,&cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),cubeVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
	glBindVertexArray(0);
	//------------------------------------------------------
	unsigned int planeVBO;
	glGenVertexArrays(1,&planeVAO);
	glGenBuffers(1,&planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER,planeVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(planeVertices),planeVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
	glBindVertexArray(0);
	//------------------------------------------------------
	unsigned int lightingVBO;
	glGenVertexArrays(1,&lightingVAO);
	glGenBuffers(1,&lightingVBO);
	glBindVertexArray(lightingVAO);
	glBindBuffer(GL_ARRAY_BUFFER,lightingVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),cubeVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
	//------------------------------------------------------
	unsigned int shaderFrameBuffer;
	unsigned int textureSize = 1024;
	glGenTextures(1,&shaderTexture);
	glBindTexture(GL_TEXTURE_2D,shaderTexture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,textureSize,textureSize,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindTexture(GL_TEXTURE_2D,0);

	glGenFramebuffers(1,&shaderFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER,shaderFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,shaderTexture,0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	//------------------------------------------------------
	unsigned int screenVAO,screenVBO;
	glGenVertexArrays(1,&screenVAO);
	glGenBuffers(1,&screenVBO);
	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER,screenVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(ScreenTextureVertices),ScreenTextureVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3 * sizeof(GL_FLOAT)));
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	//------------------------------------------------------
	cubeTexture = loadTexture("../resource/textures/container2.png",false);
	floorTexture = loadTexture("../resource/textures/wood.png",false);
	// shader configuration
	// --------------------
	pShader.use();
	pShader.setInt("texture1", 0);
	pShader.setInt("shadowTexture",1);
	pShader.setFloat("material.shininess", 32.0);
	pShader.setVec3("lightDir", lightPos);
	pShader.setVec3("lighting.ambient", glm::vec3(0.1,0.1,0.1));
	pShader.setVec3("lighting.diffuse", glm::vec3(0.5,0.5,0.5));
	pShader.setVec3("lighting.specular", glm::vec3(1.0,1.0,1.0));
	pScreenShader.setInt("textrue1",0);
	
	pScreenShader.setFloat("near_plane", near_plane);
	pScreenShader.setFloat("far_plane", far_plane);
	//------------------------------------------------------
	unsigned int ubo;
	glGenBuffers(1,&ubo);
	glBindBuffer(GL_UNIFORM_BUFFER,ubo);
	glBufferData(GL_UNIFORM_BUFFER,sizeof(glm::mat4)*2,NULL,GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER,0,ubo,0,sizeof(glm::mat4)*2);
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	//------------------------------------------------------
	//glEnable(GL_FRAMEBUFFER_SRGB);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	// render loop
	// -----------
	while(!glfwWindowShouldClose(pWindow))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//------------------------------------------------------
		string str = "near_plane = " + to_string(near_plane);
		glfwSetWindowTitle(pWindow,str.c_str());
		// input
		processInput(pWindow);
		//------------------------------------------------------
		glCullFace(GL_FRONT);
		glm::mat4 view;
		glm::mat4 projection;
		lightPos = glm::vec3(sin(glfwGetTime()) * 7,abs(cos(glfwGetTime())) * 7,0);
		pShader.use();
		pShader.setVec3("lightPos", lightPos);
		//first pass:shadow mapping
		view = glm::lookAt(lightPos,glm::vec3(0.0),glm::vec3(0.0,1.0,0.0));
		//projection = glm::ortho(-10.0,10.0,-10.0,10.0,near_plane,far_plane);
		projection = glm::perspective(glm::radians(90.0f), 1.0f, near_plane, far_plane);
		//pShadowShader.setMat4("view",view);
		//pShadowShader.setMat4("projection",projection);
		glm::mat4 lightSpaceMatrix = projection * view;
		glBindBuffer(GL_UNIFORM_BUFFER,ubo);
		glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(projection));
		glBindBuffer(GL_UNIFORM_BUFFER,0);

		glBindFramebuffer(GL_FRAMEBUFFER,shaderFrameBuffer);
		glViewport(0,0,textureSize,textureSize);
		glClear(GL_DEPTH_BUFFER_BIT);
		RenderScene(pShadowShader,false);
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glCullFace(GL_BACK);
		//------------------------------------------------------
		//draw screen vao
		if (showShadowMapping)
		{
			glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
			glClearColor(0.1,0.1,0.1,1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindVertexArray(screenVAO);
			pScreenShader.use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,shaderTexture);
			glDrawArrays(GL_TRIANGLES,0,6);
			glBindVertexArray(0);
		}
		else
		{
			//------------------------------------------------------
			//draw scene
			view = pCamera.GetLookAt();
			projection = glm::perspective(glm::radians(pCamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near_plane, far_plane);
			glBindBuffer(GL_UNIFORM_BUFFER,ubo);
			glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(view));
			glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(projection));
			glBindBuffer(GL_UNIFORM_BUFFER,0);

			glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			pShader.use();
			pShader.setMat4("lightSpaceMatrix",lightSpaceMatrix);
			RenderScene(pShader,true);
			// -------------------------------------------------------------------------------
		}
		
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &planeVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &planeVBO);

	glfwTerminate();
	return 0;
}
//------------------------------------------------------
void RenderScene(ShaderManager& pShader,bool drawLight)
{
	pShader.use();
	pShader.setVec3("viewPos",pCamera.Position);
	glm::mat4 model = glm::mat4(1.0f);
	// cubes
	glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	if (drawLight)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shaderTexture); 
	}
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
	pShader.setMat4("model", model);
	pShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	pShader.setMat4("model", model);
	pShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.5));
	pShader.setMat4("model", model);
	pShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	// floor
	glBindVertexArray(planeVAO);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, floorTexture);
	model = glm::mat4(1.0f);
	pShader.setMat4("model", model);
	pShader.setMat3("normalMatrix",glm::mat3(glm::transpose(glm::inverse(model))));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	if (drawLight)
	{
		glm::mat4 lightModel(1.0f);
		lightModel = glm::translate(lightModel,lightPos);
		lightModel = glm::scale(lightModel,glm::vec3(0.2f,0.2f,0.2f));
		pShader.setMat4("model",lightModel);
		glBindVertexArray(lightingVAO);
		glDrawArrays(GL_TRIANGLES,0,36);
		glBindVertexArray(0);
	}
	glBindVertexArray(0);
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *pWindow)
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
	if(glfwGetKey(pWindow,GLFW_KEY_B) == GLFW_TRUE)
	{
		showShadowMapping = !showShadowMapping;
	}
	if(glfwGetKey(pWindow,GLFW_KEY_E) == GLFW_TRUE)
	{
		near_plane += 0.01;
	}
	if(glfwGetKey(pWindow,GLFW_KEY_R) == GLFW_TRUE)
	{
		near_plane -= 0.01;
	}
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouseMove_callback(GLFWwindow* window, double posx, double posy)
{
	pCamera.ProcessMouseMovement(posx - lastPosx,lastPosy - posy);
	lastPosx = posx;
	lastPosy = posy;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void mouseScroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	pCamera.ProcessMouseScroll(yoffset);
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
unsigned int loadTexture(char const *path,bool isGamma)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum internalFormat;
		GLenum dataFormat;
		if (nrComponents == 1)
		{
			internalFormat = dataFormat = GL_RED;
		}
		else if (nrComponents == 3)
		{
			internalFormat = isGamma ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			internalFormat = isGamma ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
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
}*/