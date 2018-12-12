#ifndef _SHADER_H
#define _SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:

	unsigned int shaderId;

	Shader(char const* sz, GLenum type);

	~Shader();
};






#endif