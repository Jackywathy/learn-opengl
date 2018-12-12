#include <iostream>
#include <math.h>


#include "engine.h"
#include "shader.h"
#include "program.h"

typedef Shader* ShaderP;

void processInput(GLFWwindow *window);


int main(int argc, char*argv[]) {
	

	Engine *eng = new Engine(200, 200, "Hewwo");


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

	Shader *basicVertex = new Shader(shaderSource, GL_VERTEX_SHADER);
	

	// fragment shader
	shaderSource = "\
#version 400 core \n\
in vec4 ourColor; \
out vec4 FragColor;\
uniform vec4 leftColor;\
void main(){\
FragColor = ourColor;\
}";
	Shader *greenFragment = new Shader(shaderSource, GL_FRAGMENT_SHADER);


	shaderSource = "\
#version 400 core \n\
in vec4 ourColor; \
out vec4 FragColor;\
uniform vec4 rightColor;\
void main(){      \
FragColor = ourColor;\
}";
	Shader *orangeFragment = new Shader(shaderSource, GL_FRAGMENT_SHADER);
	
	Program *greenProgram = new Program();
	ShaderP multipleShaders[2];
	multipleShaders[0] = basicVertex;
	multipleShaders[1] = greenFragment;
	// linking program
	std::cout << basicVertex->shaderId << std::endl;
	std::cout << multipleShaders[0]->shaderId << std::endl;
	greenProgram->addShaders(multipleShaders, 2);

	
	Program *orangeProgram = new Program();
	multipleShaders[1] = orangeFragment;
	orangeProgram->addShaders(multipleShaders, 2);
	
	
	delete basicVertex;
	delete orangeFragment;
	delete greenFragment;
	
	greenProgram->useProgram();

	
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
	
	auto leftColor = glGetUniformLocation(greenProgram->programId, "leftColor");
	auto rightColor = glGetUniformLocation(orangeProgram->programId, "rightColor");

	GLFWwindow* window = eng->window;
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// create colors
		float timeValue = glfwGetTime();
		auto sinVal = abs(sin(timeValue));
		auto cosVal = abs(cos(timeValue));
		
		
		// render commands
		

		glClear(GL_COLOR_BUFFER_BIT);

		greenProgram->useProgram();
		glUniform4f(leftColor, cosVal, cosVal, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		orangeProgram->useProgram();
		glUniform4f(rightColor, sinVal, 0.0f, sinVal, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) (3*sizeof(GLuint)));

		
		

		// draw events, and poll inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
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
