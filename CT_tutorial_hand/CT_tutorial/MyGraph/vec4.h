#ifndef VEC4_INCLUDED
#define VEC4_INCLUDED

#include "vec4.h"


struct ivec4
{
	int x,y,z,w;

	ivec4(){}
	ivec4(int _x,int _y,int _z,int _w){x=_x;y=_y;z=_z;z=_w;}
	ivec4(int v){x=v;y=v;z=v;w=v;}
};

struct vec4
{
	float x,y,z,w;

	vec4(){}
	vec4(float v){x=v;y=v;z=v;w=v;}
	vec4(float n_x,float n_y,float n_z,float n_w);
	void set(float n_x,float n_y,float n_z,float n_w);
	void add(float n_x,float n_y,float n_z,float n_w);
	float lengthSQR();
	float length();
	float length(vec4& v);
	float lengthSQR(vec4& v);
	
	vec4 operator * (float);
	vec4 operator / (float);
	vec4 operator + (vec4);
	vec4 operator - (vec4);

	void operator += (vec4&);
	void operator -= (vec4&);

	bool operator == (vec4&);
	vec4 operator * (vec4&);
	void operator *= (float);
	void operator /= (float);
	
	void Inv();

	void RotateOij(float&sina,float&cosa,int i,int j);//поворот в плоскости координатных осей i,j

	void normalize();

	static vec4 rnd(vec4 c,vec4 d);
	static vec4 rnd();
	static float dot(vec4& c,vec4& d);


	static float line_vec(vec4 c,vec4 b);//расстояние(квадрат) от точки c до прямой Ob

	static vec4 Clamp(float min,float max,vec4 v);
	static vec4 Clamp(vec4 min,vec4 max,vec4 v);

	
	
};


#endif