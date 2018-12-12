#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <math.h>

#include "engine.h"
#include "shader.h"


void framebuffer_size_changed(GLFWwindow* window, int width, int height);
unsigned int createShader(const char* source, GLenum type, int* success, char* msg, unsigned int maxLength);

static bool initCalled = false;


Engine::Engine (int width, int height, char const* windowName) {
	
	if (initCalled) {

		throw "Cannot call init multiple times";
	}
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	
	if (!window) {
		glfwTerminate();

		throw "could not create window";
	}
	
	// load glad as well
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();

		throw "Failed to initalize GLAD";
	}
	// set the viewport
	glViewport(0, 0, width, height);


	initCalled = true;
	this->window = window;

};

void Engine::setWindowSizeChangedCallback( void (*func)(GLFWwindow* window, int width, int height) ) {
	glfwSetFramebufferSizeCallback(this->window, func);
}



void framebuffer_size_changed(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}


unsigned int createShader(const char* source, GLenum type, int* success, char* msg, unsigned int maxLength) {
	GLuint shader;
	shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, success);
	if (!*success) {
		// get reason for error
		glGetShaderInfoLog(shader, maxLength, NULL, msg);
		
	}
	return shader;

}