#ifndef _VERTEXBUFFER_H
#define _VERTEXBUFFER_H

#include "updateFrequency.h"

/* A buffer of triangles */
class VertexBuffer {
public:
	VertexBuffer(float *vertices[], unsigned int size, UpdateFrequency freq);

	void use();
	// stores the actual vertices
	unsigned int vbo;
	// stores configuration
	unsigned int vao;
	// stores ebo if required
	unsigned int ebo;
	// is ebo in use?
	bool IsEbo;
};


#endif