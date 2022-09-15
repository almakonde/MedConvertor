#include "AllInc.h"
#include "mat34.h"
#include "Math.h"
#include <memory.h>


vec3 mat34::Mult(vec3 v)
{
	return vec3(m[0][0]*v.x + m[1][0]*v.y + m[2][0]*v.z + m[3][0] , m[0][1]*v.x + m[1][1]*v.y + m[2][1]*v.z + m[3][1] , m[0][2]*v.x + m[1][2]*v.y + m[2][2]*v.z + m[3][2]);
}

vec3 mat34::MultRot(vec3 v)
{
	return vec3(m[0][0]*v.x + m[1][0]*v.y + m[2][0]*v.z  , m[0][1]*v.x + m[1][1]*v.y + m[2][1]*v.z , m[0][2]*v.x + m[1][2]*v.y + m[2][2]*v.z );
}

/*
void mat34::Mult(Triangle& t)
{
	for(int i=0;i<3;i++)
		t.v[i] = Mult(t.v[i]);
	t.norm = MultRot(t.norm);
}
*/

mat34::mat34(const mat34&mm)
{
	memcpy(m,mm.m,sizeof(m));
}

void mat34::LoadGL()
{
	int i,j;
	float mm[16];
	
	glGetFloatv(GL_MODELVIEW_MATRIX,mm);

	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			m[i][j]=mm[j + i*4];
	

}

mat34::mat34(float angle, vec3 nav)
{
	//mat34(cos(angle),sin(angle),nav);
	
	glPushMatrix();
	glLoadIdentity();
	glRotated(angle,nav.x,nav.y,nav.z);
	LoadGL();
	glPopMatrix();
	
	
}
mat34::mat34(float cos_a,float sin_a, vec3 nav)
{
	float c1=1-cos_a;
	m[0][0]=cos_a+c1*nav.x*nav.x;
	m[0][1]=c1*nav.x*nav.y+sin_a*nav.z;
	m[0][2]=c1*nav.x*nav.z-sin_a*nav.y;
	m[3][0]=0;
	m[1][0]=c1*nav.y*nav.x-sin_a*nav.z;
	m[1][1]=cos_a+c1*nav.y*nav.y;
	m[1][2]=c1*nav.y*nav.z+sin_a*nav.x;
	m[3][1]=0;
	m[2][0]=c1*nav.z*nav.x+sin_a*nav.y;
	m[2][1]=c1*nav.y*nav.z-sin_a*nav.x;
	m[2][2]=cos_a+c1*nav.z*nav.z;
	m[3][2]=0;
}
void mat34::SetAsReflection(vec3 v,vec3 norm)
{
	float pv = vec3::dot(v,norm);
  
	m[0][0] = 1 - 2 * norm.x*norm.x;
	m[1][0] = - 2 * norm.x*norm.y;
	m[2][0] = - 2 * norm.x*norm.z;
	m[3][0] = 2 * pv * norm.x;
	  
	m[0][1] = - 2 * norm.x*norm.y;
	m[1][1] = 1- 2 * norm.y*norm.y;
	m[2][1] = - 2 * norm.z*norm.y;
	m[3][1] = 2 * pv * norm.y;
  
	m[0][2] = - 2 * norm.x*norm.z;
	m[1][2] = - 2 * norm.y*norm.z;
	m[2][2] = 1 - 2 * norm.z*norm.z;
	m[3][2] = 2 * pv * norm.z;
  
}
void mat34::MultGL()
{
	float mm[4][4];
	for(int i=0;i<4;i++)
	for(int j=0;j<3;j++)
		mm[i][j]=m[i][j];

	mm[0][3] = 0;
	mm[1][3] = 0;
	mm[2][3] = 0;
	mm[3][3] = 1;

	glMultMatrixf((float*)mm);
}