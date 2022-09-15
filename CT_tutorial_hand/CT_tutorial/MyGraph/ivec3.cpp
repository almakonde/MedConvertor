#include "AllInc.h"

#include "vec3.h"
#include "ivec3.h"
#include "AllDef.h"
#include <Math.h>



ivec3::ivec3(int n_x,int n_y,int n_z)
{
	x=n_x;
	y=n_y;
	z=n_z;
}
void ivec3::set(int n_x,int n_y,int n_z)
{
	x=n_x;
	y=n_y;
	z=n_z;
}
void ivec3::add(int n_x,int n_y,int n_z)
{
	x+=n_x;
	y+=n_y;
	z+=n_z;
}
ivec3 ivec3::operator * (int op)
{
	return ivec3(x*op,y*op,z*op);
}
ivec3 ivec3::operator * (ivec3& op)
{
	return ivec3(x*op.x , y*op.y , z*op.z);
}
ivec3 ivec3::operator + (ivec3 op)
{
	return ivec3(x + op.x , y + op.y , z + op.z);
}
ivec3 ivec3::operator / (int op)
{
	return ivec3(x/op,y/op,z/op);
}
ivec3 ivec3::operator % (int op)
{
	return ivec3(x%op,y%op,z%op);
}
ivec3 ivec3::operator - (ivec3 op)
{
	return ivec3(x - op.x , y - op.y , z - op.z);
}
void ivec3::operator *= (int op)
{
	x *= op;
	y *= op;
	z *= op;
}
void ivec3::operator /= (int op)
{
	x /= op;
	y /= op;
	z /= op;
}

int ivec3::lengthSQR()
{
	return (x*x+y*y+z*z);
}

int ivec3::lengthSQR(ivec3& v)
{
	return ((x-v.x)*(x-v.x)+(y-v.y)*(y-v.y)+(z-v.z)*(z-v.z));
}



void ivec3::operator += (ivec3& op)
{
	x += op.x;
	y += op.y;
	z += op.z;
}
void ivec3::operator -= (ivec3& op)
{
	x -= op.x;
	y -= op.y;
	z -= op.z;
}
bool ivec3::operator == (ivec3& op)
{
	return (x == op.x)&&(y == op.y)&&(z == op.z);
}


void ivec3::Inv()
{
	x=-x;
	y=-y;
	z=-z;
}
ivec3 ivec3::rnd(ivec3 c,ivec3 d)
{
	return c + ivec3(RNDINT(d.x),RNDINT(d.y),RNDINT(d.z));
}

ivec3 ivec3::Min(ivec3 a,ivec3 b)
{
	return ivec3(min(a.x,b.x),min(a.y,b.y),min(a.z,b.z));
}

ivec3 ivec3::Max(ivec3 a,ivec3 b)
{
	return ivec3(max(a.x,b.x),max(a.y,b.y),max(a.z,b.z));
}


bool ivec3::InBounds(ivec3 a,ivec3 b)
{
	return (x>=a.x)&&(x<b.x)&&(y>=a.y)&&(y<b.y)&&(z>=a.z)&&(z<b.z);
}
int ivec3::dot(ivec3& v1,ivec3& v2)
{
	return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

ivec3 ivec3::Clamp(int min,int max,ivec3 v)
{
	return ivec3(clamp(min,max,v.x),clamp(min,max,v.y),clamp(min,max,v.z));
}
ivec3 ivec3::Clamp(ivec3 min,ivec3 max,ivec3 v)
{
	return ivec3(clamp(min.x,max.x,v.x),clamp(min.y,max.y,v.y),clamp(min.z,max.z,v.z));
}
ivec3 ivec3::Abs(ivec3 a)
{
	return ivec3(abs(a.x),abs(a.y),abs(a.z));
}
