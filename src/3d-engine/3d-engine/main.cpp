#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_changed(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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

	
	glViewport(0, 0, 600, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_changed);
	

	// vertex shader
	auto shaderSource = "                  \
		#version 400 core				   \n\
		layout(location = 0) in vec3 aPos; \
		void main(){					   \
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \
		}\
		";
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -3;
	}

	

	// fragment shader
	shaderSource = "\
#version 400 core \n\
out vec4 FragColor;\
void main(){\
FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\
}";
	GLuint fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &shaderSource, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -4;
	}

	// linking program
	GLuint program;
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	
		// check for errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::LINK::LINK_FAILED\n" << infoLog << std::endl;
		return -5;
	}

	glUseProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	

	

	
	// bind our vao so that the configuration is saved
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	// bind data to vbo
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		1.0f, 0.5f, 0.0f
	};
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	unsigned int indices[] = {
		0, 1, 2,
		1,2,3
	};
	// bind our ebo
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// do configuration (saved into VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// set background color
	glClearColor(0.1f, 0.4f, 0.8f, 1.0f);
	
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// render commands
		

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		// glUseProgram(secondProgram);
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

GLuint crateShader(const char* source, GLenum type, int* success, char* msg, unsigned int length) {
	GLuint shader;
	shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, success);
	if (!*success) {
		// get reason for error
		glGetShaderInfoLog(shader, length, NULL, msg);
		
	}
	return shader;

}