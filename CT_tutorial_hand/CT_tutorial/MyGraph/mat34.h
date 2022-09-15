#ifndef MATRIX34_INC
#define MATRIX34_INC

#include "vec3.h"
//#include "Geometry.h"
//struct Triangle;

class mat34
{
public:

	vec3 Mult(vec3 v);
	vec3 MultRot(vec3 v);//�� ������ ���������� ������ ����� �������, ����� �� ��������� ������. ������ ��������.

//	void Mult(Triangle& t);

	void LoadGL();//����� ������� ������� ������������� OpenGL.

	mat34(){}
	mat34(const mat34&mm);
	mat34(float angle, vec3 nav);//�������, ��� ������� �������� �� ���� angle ������ nav
	mat34(float cos_a,float sin_a, vec3 nav);//�������, ��� ������� ��������
	void MultGL();// ��������� ������� �� ������� ������� ������������� OpenGL(��������� OpenGL-�������)
	void SetAsReflection(vec3 v,vec3 norm);//��� ������� ��������� ������������ ���������

protected:

	float m[4][3];

};


#endif