#include "SimText3D.h"
#pragma comment(lib,"glew32.lib")
#include <windows.h>
/*
GLenum texture_target=GL_TEXTURE_RECTANGLE_ARB;
GLenum internal_format=GL_RGBA32F_ARB;
GLenum texture_format=GL_RGBA;
*/
void checkGLErrors (const char *label);

void SimText3D::setupTexture(GLuint texID)
{
    // make active and bind
    glBindTexture(texture_target,texID);
    // turn off filtering and wrap modes

	glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, linear?GL_LINEAR:GL_NEAREST);
    glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, linear?GL_LINEAR:GL_NEAREST);
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_R, GL_CLAMP);
    
	//static PFNGLTEXIMAGE3DPROC glTexImage3D = (PFNGLTEXIMAGE3DPROC) wglGetProcAddress("glTexImage3D");
	// define texture with floating point format
	//glTexImage3D(texture_target,0,internal_format,width,height,depth,0,texture_format,GL_FLOAT,0);

}

void SimText3D::Upload1(int z1,int z2) 
{
    glBindTexture(texture_target, texture);

	static PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) wglGetProcAddress("glTexSubImage3D");
	//glTexSubImage3D(texture_target,0,0,0,z1,width,height,z2-z1,texture_format,t_type,((BYTE*)arr+(z1*width*height*3*sizeof(float))));
	glTexSubImage3D(texture_target,0,0,0,z1,width,height,z2-z1,texture_format,t_type,((float*)arr) + width*height*3*z1);
}
void SimText3D::Upload(int id,int num) 
{
	int step=depth/num;
	Upload1(id*step,(id+1)*step);
}



int texture_target1;
int width1,height1,depth1,internal_format1,type1,texture_format1;
void*arr1;
//bool up_done=1;
void UploadToTexture(void *v) 
{
	static PFNGLTEXIMAGE3DPROC glTexImage3D = (PFNGLTEXIMAGE3DPROC) wglGetProcAddress("glTexImage3D");

	glTexImage3D(texture_target1,0,internal_format1,width1,height1,depth1,0,texture_format1,GL_FLOAT,arr1);

}


void SimText3D::transferToTexture(GLuint texID) 
{
	if(texID==-1)texID=texture;
    glBindTexture(texture_target, texID);

//	static PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) wglGetProcAddress("glTexSubImage3D");
	//glTexSubImage3D(texture_target,0,0,0,0,width,height,depth,texture_format,t_type,arr);
	static PFNGLTEXIMAGE3DPROC glTexImage3D = (PFNGLTEXIMAGE3DPROC) wglGetProcAddress("glTexImage3D");

	glTexImage3D(texture_target,0,internal_format,width,height,depth,0,texture_format,t_type,arr);

}

// создание 3Д текстуры
// w, h,d - размеры
// pixel_size - кол-во каналов (от 1 до 4, сколько чисел хранит каждый воксель)
// data - исходные данные 
// n_ID_to_use - индекс (до 7) 
// n_linear - делать ли линейную фильтрацию (интерполяцию)
// nt_type - тип данных
			
SimText3D::SimText3D(int w,int h,int d,int pixel_size,void* data,int n_ID_to_use,bool n_linear,int nt_type):ID_to_use(n_ID_to_use),linear(n_linear),t_type(nt_type)
{
	//while(!up_done){}
//	shader_program = spr;
	glActiveTexture(GL_TEXTURE0+ID_to_use);
	glEnable(GL_TEXTURE_3D);
	arr=data;
//	arr = new float[128*128*128*3];
//	memcpy(arr,data,128*128*128*3);
	texture_target=GL_TEXTURE_3D;
	if(pixel_size==1)
	{
		
		if(t_type==GL_FLOAT)
		{
//			internal_format=GL_ALPHA16F_ARB;
//			texture_format=GL_ALPHA;
			internal_format=GL_LUMINANCE32F_ARB;
			texture_format=GL_LUMINANCE;//GL_ALPHA;
		}else
		if(t_type==GL_UNSIGNED_BYTE)
		{
			internal_format=GL_LUMINANCE8;
			texture_format=GL_LUMINANCE;
		}else
		{
			//internal_format=GL_LUMINANCE16;
			internal_format=GL_LUMINANCE16F_ARB;
			texture_format=GL_LUMINANCE;
		}
		
	}else
	if(pixel_size==3)
	{
		
		if(t_type==GL_FLOAT)
		{
			internal_format=GL_RGB16F_ARB;
			texture_format=GL_RGB;
		}else
		if(t_type==GL_UNSIGNED_BYTE)
		{
			internal_format=GL_RGB8;
			texture_format=GL_RGB;
		}else
		{
			internal_format=GL_RGB16;
			texture_format=GL_RGB;
		}
	}
	else
	{
		//if(pixel_size!=4)std::cout << "WARNING: Unable to create (" << pixel_size << ")-pixeled texture.";
		if(t_type==GL_FLOAT)
		{
			internal_format=GL_RGBA32F_ARB;
			texture_format=GL_RGBA;
		}else
		{
			internal_format=GL_RGBA8;
			texture_format=GL_RGBA;
		}
	}

	width=w;
	height=h;
	depth=d;

    glGenTextures(1, &texture);

    setupTexture(texture);


    transferToTexture(texture);

	
	glDisable(GL_TEXTURE_3D);
	glActiveTexture(GL_TEXTURE0);
};

SimText3D::~SimText3D()
{
	//delete[] arr;
    glDeleteTextures (1,&texture);
	glDeleteFramebuffersEXT (1,&fb);
}
GLuint SimText3D::GetTexture()
{
	return texture;
}