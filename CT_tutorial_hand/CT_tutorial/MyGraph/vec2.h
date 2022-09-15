#ifndef VEC2_INCLUDED
#define VEC2_INCLUDED

#include "vec3.h"



struct vec2
{
	float x,y;

	vec2(){}
	vec2(float v){x=v;y=v;}
	vec2(float n_x,float n_y);

	void set(float n_x,float n_y);
	void add(float n_x,float n_y);
	float lengthSQR();
	float length();
	float length(vec2& v);
	float lengthSQR(vec2& v);
	
	vec2 operator * (float);
	vec2 operator / (float);
	vec2 operator + (vec2);
	vec2 operator - (vec2);

	void operator += (vec2&);
	void operator -= (vec2&);

	bool operator == (vec2&);
	vec2 operator * (vec2&);
	vec2 operator / (vec2&);
	void operator *= (float);
	void operator /= (float);
	
	void Inv();
	

	void Rotate(float&sina,float&cosa);

	void normalize();

	static float dot(vec2& v1,vec2& v2);//скалярное произв.
	static float vect_mult(vec2& v1,vec2& v2);//векторное умножение
	static vec2 rnd(vec2 c,vec2 d);

	static float line_vec(vec2 c,vec2 b);//расстояние(квадрат) от точки c до прямой Ob

	static vec2 Max(vec2 a,vec2 b);
	static vec2 Min(vec2 a,vec2 b);
};
#endif