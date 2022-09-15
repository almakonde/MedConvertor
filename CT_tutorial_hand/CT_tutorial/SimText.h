#ifndef SIMTEXT_H
#define SIMTEXT_H

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

class SimText
{
public:
	SimText(const GLchar*t_name,int w,int h,ShaderProgram* spr,int ID_to_Use);
	~SimText();

	void Simulation(float* arr);
	void UploadTexture(float *arr);
	void UploadTexture1(float *arr);
	void DownloadTexture(float *arr);

	GLuint GetTexture();
private:
	void transferToTexture(GLuint texID,float*arr);

	void setupTexture(GLuint texID);

	const GLchar*tex_name;
	ShaderProgram* shader_program;

	GLuint texture[2];

	int writeTex,ID_to_use;
	int width,height;

	//GLfloat *arr;

	GLenum texture_target;
	GLenum internal_format;
	GLenum texture_format;

	GLuint fb;

};

class Text
{
public:
	void UploadTexture(float *arr);
	Text(int w,int h,float*arr);
	~Text();
	GLuint GetTexture();
private:
	void transferToTexture(GLuint texID,float*arr);

	void setupTexture(GLuint texID);

	GLuint texture;
	int width,height;
	GLenum texture_target;
	GLenum internal_format;
	GLenum texture_format;

};
#endif