#ifndef SIMTEXT3D_H
#define SIMTEXT3D_H

//#include "define.h"

#include <vector>
#include <assert.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <ctime>

#include "Shader.h"

// класс для работы с 3д текстурой
class SimText3D
{
public:
	SimText3D(int w,int h,int d, int pixel_size,void* data,int n_ID_to_use,bool n_linear,int nt_type);
	~SimText3D();

	int ID_to_use;

	GLuint GetTexture();

	void Upload1(int z1,int z2);
	void Upload(int id,int num);
private:
	void transferToTexture(GLuint texID=-1);
	

	void setupTexture(GLuint texID);

//	const GLchar*tex_name;

	GLuint texture;

	
	int width,height,depth;
	bool linear;

	void *arr;

	GLenum t_type;
	GLenum texture_target;
	GLenum internal_format;
	GLenum texture_format;

	GLuint fb;

};
#endif