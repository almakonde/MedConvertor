#include "vec4.h"
#include "vec3.h"

#include "AllDef.h"
#include <Math.h>


vec4::vec4(float n_x,float n_y,float n_z,float n_w)
{
	x=n_x;
	y=n_y;
	z=n_z;
	w=n_w;
}

void vec4::set(float n_x,float n_y,float n_z,float n_w)
{
	x=n_x;
	y=n_y;
	z=n_z;
	w=n_w;
}
void vec4::add(float n_x,float n_y,float n_z,float n_w)
{
	x+=n_x;
	y+=n_y;
	z+=n_z;
	w+=n_w;
}
vec4 vec4::operator * (float op)
{
	return vec4(x*op,y*op,z*op,w*op);
}
vec4 vec4::operator * (vec4& op)
{
	return vec4(x*op.x , y*op.y , z*op.z , w*op.w);
}
vec4 vec4::operator + (vec4 op)
{
	return vec4(x + op.x , y + op.y , z + op.z , w + op.w);
}
vec4 vec4::operator / (float op)
{
	return vec4(x/op,y/op,z/op,w/op);
}
vec4 vec4::operator - (vec4 op)
{
	return vec4(x - op.x , y - op.y , z - op.z , w - op.w);
}
void vec4::operator *= (float op)
{
	x *= op;
	y *= op;
	z *= op;
	w *= op;
}
void vec4::operator /= (float op)
{
	x /= op;
	y /= op;
	z /= op;
	w /= op;
}

float vec4::lengthSQR()
{
	return (x*x+y*y+z*z+w*w);
}
float vec4::length()
{
	return sqrt(x*x+y*y+z*z+w*w);
}
float vec4::length(vec4& v)
{
	return sqrt(lengthSQR(v));
}
float vec4::lengthSQR(vec4& v)
{
	return ((x-v.x)*(x-v.x)+(y-v.y)*(y-v.y)+(z-v.z)*(z-v.z)+(w-v.w)*(w-v.w));
}

void vec4::operator += (vec4& op)
{
	x += op.x;
	y += op.y;
	z += op.z;
	w += op.w;
}
void vec4::operator -= (vec4& op)
{
	x -= op.x;
	y -= op.y;
	z -= op.z;
	w -= op.w;
}
bool vec4::operator == (vec4& op)
{
	return (x == op.x)&&(y == op.y)&&(z == op.z)&&(w == op.w);
}


void vec4::Inv()
{
	x=-x;
	y=-y;
	z=-z;
	w=-w;
}
void vec4::normalize()
{
	float l=lengthSQR();
	if(l) *this = (*this * (1.0f/sqrt(l)));
}


float vec4::line_vec(vec4 c,vec4 b)
{
	float l=b.lengthSQR();
	if(!l)return c.lengthSQR();
	return (c-b*((c*b)/l)).lengthSQR();
}

void vec4::RotateOij(float&sina,float&cosa,int i,int j)
{
	float oi=BY_ID(i),oj=BY_ID(j);
    BY_ID(i) = -oj*sina + oi*cosa;
	BY_ID(j) = oi*sina + oj*cosa;
}

vec4 vec4::rnd(vec4 c,vec4 d)
{
	return c + vec4(RND01*d.x,RND01*d.y,RND01*d.z,RND01*d.w);
}
vec4 vec4::rnd()
{
	return vec4(RND01,RND01,RND01,RND01);
}

float vec4::dot(vec4& v1,vec4& v2)
{
	return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z+v1.w*v2.w;
}
vec4 vec4::Clamp(float min,float max,vec4 v)
{
	return vec4(clamp(min,max,v.x),clamp(min,max,v.y),clamp(min,max,v.z),clamp(min,max,v.w));
}
vec4 vec4::Clamp(vec4 min,vec4 max,vec4 v)
{
	return vec4(clamp(min.x,max.x,v.x),clamp(min.y,max.y,v.y),clamp(min.z,max.z,v.z),clamp(min.w,max.w,v.w));
}