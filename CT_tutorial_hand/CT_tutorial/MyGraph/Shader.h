#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "AllInc.h"

#include "vec3.h"
#include "vec4.h"
#include <vector>
#include <assert.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <ctime>



class ShaderProgram
{
public:
	ShaderProgram(const GLchar*vs,const GLchar*fs);
	~ShaderProgram();
	void Use();
	void UnUse();
//	void PrintLog();

	
	void SetVar(const GLchar *name,vec3 val);
	void SetVar(const GLchar *name,vec4 val);
	void SetVar(const GLchar *name,float val);
	void SetVar(const GLchar *name,unsigned int val);
	void SetMatrix3(const GLchar *name,float*m);

private:
	GLint getUniLoc(const GLchar *name);
	GLuint h_vert;
    GLuint h_frag;
    GLuint h_program;

};

#endif