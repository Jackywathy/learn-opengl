#ifndef _ENGINE_H
#define _ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Engine {
public :
	Engine (int width, int height, char const* windowName);
	void setWindowSizeChangedCallback( void (*func)(GLFWwindow*, int , int ));


	GLFWwindow* window;
	private:
};



#endif