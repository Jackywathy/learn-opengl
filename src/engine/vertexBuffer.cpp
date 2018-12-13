#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertexBuffer.h"
#include "updateFrequency.h"
#include <exception>


VertexBuffer::VertexBuffer(float *vertices[], unsigned int size, UpdateFrequency freq) {
	// create a vbo
	// and a vao
	glGenBuffers(1, &(this->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	// generate a vertex array to store configuration
	glGenVertexArrays(1, &(this->vao));


	GLenum updateType;

	switch (freq) {
		case UpdateFrequency::LOW:
			updateType = GL_STATIC_DRAW;
			break;
		default:
			throw new std::exception();
	}

	glBufferData(GL_ARRAY_BUFFER, size, vertices, updateType);

}

VertexBuffer::addAttribute(unsigned int location, unsigned int length, unsigned int elementsPerPoint, unsigned int offset) {
	glBindVertexArray(VAO);
	glVertexAttribPointer(location, length, GL_FLOAT, elementsPerPoint * sizeof(float), (void*) offset);
}


VertexBuffer::UseIndices()

void VertexBuffer::use() {
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}