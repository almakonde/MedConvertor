#include "Iso.h"
#include "Shader.h"
#include "AllDef.h"
#include "Draw.h"
#include <windows.h>
#include "vec.h"
#include "str.h"

extern int stereo_on;

IsoViewer::IsoViewer():l1(0),b1(0),b2(1),st(0),st_i(0),st_n(0),ps(0)
{

	draw_frame_is=1;
	
	//загрузка исходников шедера из файла в GPU + компилляция шейдера
	ps = new ShaderProgram("rend_common.vs","opaque_surface.fs");
//	ps = new ShaderProgram("rend_common.vs", "MIP.fs");
	//ps = new ShaderProgram("rend_common.vs","semitransparent_surface.fs");
//	ps = new ShaderProgram("rend_common.vs","wlDVR.fs");	

	//инициализация uniform-переменных в шейдере
	SetAnag(0,0);
	SetBoundingBox(b1,b2);
	SetLevel(l1);

}



//установка изо-значения для изо-поверхности
void IsoViewer::SetLevel(float nl1)
{
	l1=clamp(0.0f,1.0f,nl1);

	ps->Use();
	ps->SetVar("level1", nl1);
	ps->UnUse();
}

//установка координат концов ограничивающей коробки
void IsoViewer::SetBoundingBox(vec3 a,vec3 b)
{
	
	b1=a;//vec3::Clamp(0,1,a);
	b2=b;//vec3::Clamp(0,1,b);

	ps->Use();
	ps->SetVar("box1",b1);
	ps->SetVar("box2",b2);
	ps->SetVar("step_length",0.003f);
	ps->UnUse();
}

//установка положения и ориентации камеры
void IsoViewer::ApplyCamera(Camera* c)
{
	ps->Use();
	ps->SetVar("pos",c->GetStereoPosition());
	ps->SetVar("nav",c->GetNav());
	ps->UnUse();
}

void IsoViewer::Draw(Camera* c)
{
	vec3 bb1=b1,bb2=b2;

	//вывод рамки
	if(stereo_on!=1 && draw_frame_is) 
	{
		glColor3f(0.5f,0.5f,0.5f);
		glDisable(GL_LIGHTING);
		DrawCubeFrame(bb1,bb2);
		glEnable(GL_LIGHTING);
		
	}

	ps->Use();
	ps->SetVar("box1",b1);
	ps->SetVar("box2",b2);
	ps->SetVar("scale",scale);
	ps->SetVar("size",vec3(size.x,size.y,size.z));
	DrawCube(bb1,bb2); //вывод коробки (т.е. наших объёмных данных, т.к. для закрашивания коробки используется шейдер трассировки луча)
	ps->UnUse();



}
IsoViewer::~IsoViewer()
{
	delete ps;
	if(st)delete st;
	if(st_i)delete st_i;
	if(st_n)delete st_n;
}


//загрузка исходных объёмных данных в GPU
void IsoViewer::UploadFieldData(void*data,ivec3 size, int type,vec3 scale1)
{
	scale=scale1;
	b2=scale;
	if(st)delete st;


	//в конструкторе происходит создание 3Д текстуры + её инициализация исходными данными
	st = new SimText3D(size.x,size.y,size.z,1,data,1,true,type);

	ps->Use();
	ps->SetVar("f_text",st->GetTexture());

	ps->UnUse();


}

//установить анаглиф типа s для левого(если left) или правого глаза
void IsoViewer::SetAnag(int s, bool left)
{
	
	switch(s)
	{
	case 0: // no stereo
		anag[0].set(1,0,0);
		anag[1].set(0,1,0);
		anag[2].set(0,0,1);
		break;
	case 1: // True anaglyh
		if(left)
		{
			anag[0].set(0.299,0.587,0.114);
			anag[1].set(0,0,0);
			anag[2].set(0,0,0);
		}else
		{
			anag[0].set(0,0,0);
			anag[1].set(0,0,0);
			anag[2].set(0.299,0.587,0.114);
		}
		break;
	case 2: // Gray anaglyh
		if(left)
		{
			anag[0].set(0.299,0.587,0.114);
			anag[1].set(0,0,0);
			anag[2].set(0,0,0);
		}else
		{
			anag[0].set(0,0,0);
			anag[1].set(0.299,0.587,0.114);
			anag[2].set(0.299,0.587,0.114);
		}
		break;
	case 3: // Color anaglyh
		if(left)
		{
			anag[0].set(1,0,0);
			anag[1].set(0,0,0);
			anag[2].set(0,0,0);
		}else
		{
			anag[0].set(0,0,0);
			anag[1].set(0,1,0);
			anag[2].set(0,0,1);
		}
		break;	
	case 4: // Half-Color anaglyh
		if(left)
		{
			anag[0].set(0.299,0.587,0.114);
			anag[1].set(0,0,0);
			anag[2].set(0,0,0);
		}else
		{
			anag[0].set(0,0,0);
			anag[1].set(0,1,0);
			anag[2].set(0,0,1);
		}
		break;	
	case 5: // Optimized anaglyh
		if(left)
		{
			anag[0].set(0,0.7,0.3);
			anag[1].set(0,0,0);
			anag[2].set(0,0,0);
		}else
		{
			anag[0].set(0,0,0);
			anag[1].set(0,1,0);
			anag[2].set(0,0,1);
		}
		break;	
	};

	ps->Use();
	ps->SetVar("RFrom",anag[0]);
	ps->SetVar("GFrom",anag[1]);
	ps->SetVar("BFrom",anag[2]);
	ps->UnUse();
}
