#include <vector>
#include <iostream>

#include "shader.h"
#include "program.h"

Program::Program() {
	this->programId = glCreateProgram();
}


void Program::addShaders(Shader **shader, unsigned int length) {
	int success;
	char msg[512];

	for (unsigned int i = 0; i<length; i++) {
		glAttachShader(this->programId, (shader[i])->shaderId);
		std::cout << i << std::endl;
	}

	glLinkProgram(this->programId);
	glGetProgramiv(this->programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->programId, 512, NULL, msg);
		std::cout << msg << std::endl;
		throw msg;
	}

}

void Program::useProgram() {
	glUseProgram(this->programId);
}



Program::~Program() {
	glDeleteProgram(this->programId);
}