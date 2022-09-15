#include "vec2.h"
#include "AllDef.h"
#include <Math.h>



vec2::vec2(float n_x,float n_y)
{
	x=n_x;
	y=n_y;
}
void vec2::set(float n_x,float n_y)
{
	x=n_x;
	y=n_y;
}
void vec2::add(float n_x,float n_y)
{
	x+=n_x;
	y+=n_y;
}
vec2 vec2::operator * (float op)
{
	return vec2(x*op,y*op);
}
vec2 vec2::operator * (vec2& op)
{
	return vec2(x*op.x,y*op.y);
}
float vec2::dot(vec2& v1,vec2& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}
vec2 vec2::operator + (vec2 op)
{
	return vec2(x + op.x , y + op.y);
}
vec2 vec2::operator / (float op)
{
	return vec2(x/op,y/op);
}
vec2 vec2::operator - (vec2 op)
{
	return vec2(x - op.x , y - op.y);
}
vec2 vec2::operator / (vec2& op)
{
	return vec2(x / op.x , y / op.y);
}
void vec2::operator *= (float op)
{
	x *= op;
	y *= op;
}
void vec2::operator /= (float op)
{
	x /= op;
	y /= op;
}

float vec2::lengthSQR()
{
	return (x*x+y*y);
}
float vec2::length()
{
	return sqrt(x*x+y*y);
}
float vec2::length(vec2& v)
{
	return sqrt(lengthSQR(v));
}
float vec2::lengthSQR(vec2& v)
{
	return ((x-v.x)*(x-v.x)+(y-v.y)*(y-v.y));
}

float vec2::vect_mult(vec2& v1,vec2& v2)
{
	return v2.y*v1.x-v2.x*v1.y;
}


void vec2::operator += (vec2& op)
{
	x += op.x;
	y += op.y;
}
void vec2::operator -= (vec2& op)
{
	x -= op.x;
	y -= op.y;
}
bool vec2::operator == (vec2& op)
{
	return (x == op.x)&&(y == op.y);
}


void vec2::Inv()
{
	x=-x;
	y=-y;
}
void vec2::normalize()
{
	float l=lengthSQR();
	if(l) *this = (*this * (1.0f/sqrt(l)));
}


float vec2::line_vec(vec2 c,vec2 b)
{
	float l=b.lengthSQR();
	if(!l)return c.lengthSQR();
	return (c-b*((c*b)/l)).lengthSQR();
}


void vec2::Rotate(float&sina,float&cosa)
{
	float oi=x,oj=y;
    x = -oj*sina + oi*cosa;
	y = oi*sina + oj*cosa;
}
vec2 vec2::rnd(vec2 c,vec2 d)
{
	return c + vec2(RND11*d.x,RND11*d.y);
}

vec2 vec2::Max(vec2 a,vec2 b)
{
	return vec2(max(a.x,b.x),max(a.y,b.y));
}
vec2 vec2::Min(vec2 a,vec2 b)
{
	return vec2(min(a.x,b.x),min(a.y,b.y));
}
