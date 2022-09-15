#include "vec3.h"
#include "ivec2.h"
#include "AllDef.h"
#include <Math.h>



ivec2::ivec2(int n_x,int n_y)
{
	x=n_x;
	y=n_y;
}
void ivec2::set(int n_x,int n_y)
{
	x=n_x;
	y=n_y;
}
ivec2 ivec2::operator * (int op)
{
	return ivec2(x*op,y*op);
}
ivec2 ivec2::operator * (ivec2& op)
{
	return ivec2(x*op.x , y*op.y );
}
ivec2 ivec2::operator + (ivec2 op)
{
	return ivec2(x + op.x , y + op.y );
}
ivec2 ivec2::operator / (int op)
{
	return ivec2(x/op,y/op);
}
ivec2 ivec2::operator % (int op)
{
	return ivec2(x%op,y%op);
}
ivec2 ivec2::operator - (ivec2 op)
{
	return ivec2(x - op.x , y - op.y);
}
void ivec2::operator *= (int op)
{
	x *= op;
	y *= op;
}
void ivec2::operator /= (int op)
{
	x /= op;
	y /= op;
}

int ivec2::lengthSQR()
{
	return (x*x+y*y);
}

int ivec2::lengthSQR(ivec2& v)
{
	return ((x-v.x)*(x-v.x)+(y-v.y)*(y-v.y));
}



void ivec2::operator += (ivec2& op)
{
	x += op.x;
	y += op.y;
}
void ivec2::operator -= (ivec2& op)
{
	x -= op.x;
	y -= op.y;
}
bool ivec2::operator == (ivec2& op)
{
	return (x == op.x)&&(y == op.y);
}


void ivec2::Inv()
{
	x=-x;
	y=-y;
}
ivec2 ivec2::rnd(ivec2 c,ivec2 d)
{
	return c + ivec2(RNDINT(d.x),RNDINT(d.y));
}

ivec2 ivec2::Min(ivec2 a,ivec2 b)
{
	return ivec2(min(a.x,b.x),min(a.y,b.y));
}

ivec2 ivec2::Max(ivec2 a,ivec2 b)
{
	return ivec2(max(a.x,b.x),max(a.y,b.y));
}


bool ivec2::InBounds(ivec2 a,ivec2 b)
{
	return (x>=a.x)&&(x<b.x)&&(y>=a.y)&&(y<b.y);
}
int ivec2::dot(ivec2& v1,ivec2& v2)
{
	return v1.x*v2.x+v1.y*v2.y;
}