#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <vector>
#include "shader.h"

class Program {
public:
	Program();
	unsigned int programId;

	~Program();

	void addShaders(Shader** shader, unsigned int length);

	void useProgram();


};

#endif