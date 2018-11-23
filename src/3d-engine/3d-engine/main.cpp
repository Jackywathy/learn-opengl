#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define LOAD_RESOURCE(x) 
void framebuffer_size_changed(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int createShader(const char* source, GLenum type, int* success, char* msg, unsigned int maxLength);

int main(int argc, char*argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Hewwo!", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initalize GLAD" << std::endl;
		return -2;

	}
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "MAximum number of attributes" << nrAttributes << std::endl;

	
	glViewport(0, 0, 600, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_changed);
	

	// vertex shader
	auto shaderSource = "                  \
		#version 400 core				   \n\
		layout(location = 0) in vec3 aPos; \
		layout (location =1) in vec3 color; \
		out vec4 ourColor; \
		void main(){					   \
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \
			ourColor = vec4(color.xyz, 1.0f);\
		}\
		";
	
	int success;
	char msg[512];
	auto vertexShader = createShader(shaderSource, GL_VERTEX_SHADER, &success, msg, 512);
	if (!success) {
		std::cout << "ERROR::VERTEX::COMPILATION_FAILED::" << __LINE__ << "\n" << msg << std::endl;
		system("pause");
		return -2;
	}


	// fragment shader
	shaderSource = "\
#version 400 core \n\
in vec4 ourColor; \
out vec4 FragColor;\
uniform vec4 leftColor;\
void main(){\
FragColor = ourColor;\
}";
	auto greenShader = createShader(shaderSource, GL_FRAGMENT_SHADER, &success, msg, 512);
	if (!success) {
		std::cout << "ERROR::FRAGMENT::COMPILATION_FAILED::" << __LINE__ << "\n" << msg << std::endl;
		system("pause");
		return -2;
	}


	shaderSource = "\
#version 400 core \n\
in vec4 ourColor; \
out vec4 FragColor;\
uniform vec4 rightColor;\
void main(){      \
FragColor = ourColor;\
}";
	auto orangeShader = createShader(shaderSource, GL_FRAGMENT_SHADER, &success, msg, 512);
	if (!success) {
		std::cout << "ERROR::FRAGMENT::COMPILATION_FAILED::" << __LINE__ << "\n" << msg << std::endl;
		system("pause");
		return -2;
	}


	// linking program
	GLuint greenProgram;
	greenProgram = glCreateProgram();
	glAttachShader(greenProgram, vertexShader);
	glAttachShader(greenProgram, greenShader);
	glLinkProgram(greenProgram);

	glGetProgramiv(greenProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(greenProgram, 512, NULL, msg);
		std::cout << "ERROR::LINK::LINK_FAILED\n" << msg << std::endl;
		return -5;
	}

	GLuint orangeProgram;
	orangeProgram = glCreateProgram();
	glAttachShader(orangeProgram, vertexShader);
	glAttachShader(orangeProgram, orangeShader);
	glLinkProgram(orangeProgram);
	
		// check for errors
	glGetProgramiv(orangeProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(orangeProgram, 512, NULL, msg);
		std::cout << "ERROR::LINK::LINK_FAILED\n" << msg << std::endl;
		return -5;
	}

	glUseProgram(greenProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(orangeProgram);
	glDeleteShader(greenShader);

	

	

	
	// bind our vao so that the configuration is saved
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	// bind data to vbo
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	};
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	// bind our ebo
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// do configuration (saved into VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// set background color
	glClearColor(0.1f, 0.4f, 0.8f, 1.0f);
	
	auto leftColor = glGetUniformLocation(greenProgram, "leftColor");
	auto rightColor = glGetUniformLocation(orangeProgram, "rightColor");

	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// create colors
		float timeValue = glfwGetTime();
		auto sinVal = abs(sin(timeValue));
		auto cosVal = abs(cos(timeValue));
		
		
		// render commands
		

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(greenProgram);
		glUniform4f(leftColor, cosVal, cosVal, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glUseProgram(orangeProgram);
		glUniform4f(rightColor, sinVal, 0.0f, sinVal, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) (3*sizeof(GLuint)));

		
		

		// draw events, and poll inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void framebuffer_size_changed(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
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