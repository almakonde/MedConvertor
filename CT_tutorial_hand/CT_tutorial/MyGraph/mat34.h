#ifndef MATRIX34_INC
#define MATRIX34_INC

#include "vec3.h"
//#include "Geometry.h"
//struct Triangle;

class mat34
{
public:

	vec3 Mult(vec3 v);
	vec3 MultRot(vec3 v);//на вектор умножается только часть матрицы, чтобы не учитывать сдвиги. Только повороты.

//	void Mult(Triangle& t);

	void LoadGL();//взять текущую матрицу трансформации OpenGL.

	mat34(){}
	mat34(const mat34&mm);
	mat34(float angle, vec3 nav);//создать, как матрицу поворота на угол angle вокруг nav
	mat34(float cos_a,float sin_a, vec3 nav);//создать, как матрицу поворота
	void MultGL();// домножить матрицу на текущую матрицу трансформации OpenGL(изменится OpenGL-матрица)
	void SetAsReflection(vec3 v,vec3 norm);//как матрицу отражения относительно плоскости

protected:

	float m[4][3];

};


#endif