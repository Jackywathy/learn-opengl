#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"


Shader::Shader(char const* source, GLenum type) {
	int success;
	char msg[512];

	// create a new shader of type given (fragment, vertex etc)
	this->shaderId = glCreateShader(type);

	// set the sauce
	glShaderSource(this->shaderId, 1, &source, NULL);

	// compile the bad boi
	glCompileShader(this->shaderId);

	// check fur errors
	glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->shaderId, 512, NULL, msg);

		throw msg;
	}


}

Shader::~Shader() {
	glDeleteShader(this->shaderId);

}