#include "AllInc.h"

#include "vec3.h"
#include "AllDef.h"
#include <Math.h>
#include "vec2.h"


vec3::vec3(float n_x,float n_y,float n_z)
{
	x=n_x;
	y=n_y;
	z=n_z;
}
vec3::vec3(vec2 v2,float n_z)
{
	x = v2.x;
	y = v2.y;
	z = n_z;
}

void vec3::set(float n_x,float n_y,float n_z)
{
	x=n_x;
	y=n_y;
	z=n_z;
}
void vec3::add(float n_x,float n_y,float n_z)
{
	x+=n_x;
	y+=n_y;
	z+=n_z;
}
vec3 vec3::operator * (float op)
{
	return vec3(x*op,y*op,z*op);
}
vec3 vec3::operator * (vec3& op)
{
	return vec3(x*op.x , y*op.y , z*op.z);
}
vec3 vec3::operator / (vec3& op)
{
	return vec3(x/op.x , y/op.y , z/op.z);
}
vec3 vec3::operator + (vec3 op)
{
	return vec3(x + op.x , y + op.y , z + op.z);
}
vec3 vec3::operator / (float op)
{
	return vec3(x/op,y/op,z/op);
}
vec3 vec3::operator - (vec3 op)
{
	return vec3(x - op.x , y - op.y , z - op.z);
}
void vec3::operator *= (float op)
{
	x *= op;
	y *= op;
	z *= op;
}
void vec3::operator /= (float op)
{
	x /= op;
	y /= op;
	z /= op;
}

float vec3::lengthSQR()
{
	return (x*x+y*y+z*z);
}
float vec3::length()
{
	return sqrt(x*x+y*y+z*z);
}
float vec3::length(vec3& v)
{
	return sqrt(lengthSQR(v));
}
float vec3::lengthSQR(vec3& v)
{
	return ((x-v.x)*(x-v.x)+(y-v.y)*(y-v.y)+(z-v.z)*(z-v.z));
}

vec3 vec3::vect_mult(vec3& v1,vec3& v2)
{
	return vec3( v2.y*v1.z-v2.z*v1.y , v2.z*v1.x-v2.x*v1.z , v2.x*v1.y-v2.y*v1.x);
}


void vec3::operator += (vec3& op)
{
	x += op.x;
	y += op.y;
	z += op.z;
}
void vec3::operator -= (vec3& op)
{
	x -= op.x;
	y -= op.y;
	z -= op.z;
}
bool vec3::operator == (vec3& op)
{
	return (x == op.x)&&(y == op.y)&&(z == op.z);
}


void vec3::Inv()
{
	x=-x;
	y=-y;
	z=-z;
}
void vec3::normalize()
{
	float l=lengthSQR();
	if(l) *this = (*this * (1.0f/sqrt(l)));
}
vec3 vec3::normalized()
{
	vec3 res = *this;
	res.normalize();
	return res;
}
vec3 vec3::proected_on(vec3 norm)
{
	return *this - norm*dot(*this,norm);
}
vec3 vec3::proected_on(vec3 a,vec3 b)
{
	vec3 ba = b-a;
	vec3 va = *this-a;
	return a-ba *( dot(va,ba)/ba.lengthSQR() );
}

float vec3::line_vec(vec3 c,vec3 b)
{
	float l=b.lengthSQR();
	if(!l)return c.lengthSQR();
	return (c-b*((c*b)/l)).lengthSQR();
}
vec3 vec3::flat_cross_line(flat f, vec3 l)
{
	float tmp=vec3::dot(l,f.n);
	if(!tmp)return f.d;
	return l*(vec3::dot(f.d,f.n)/tmp);
}


void vec3::RotateOij(float ang,int i,int j)
{
	float s = sin(ang),c = cos(ang);
	RotateOij(s,c,i,j);

}
void vec3::RotateOij(float&sina,float&cosa,int i,int j)
{
	float oi=BY_ID(i),oj=BY_ID(j);
    BY_ID(i) = -oj*sina + oi*cosa;
	BY_ID(j) = oi*sina + oj*cosa;
}
flat::flat(vec3 nd,vec3 nn)
{
	n=nn;
	d=nd;
}
float vec3::line_line(vec3& a1,vec3& a2,vec3& b1,vec3& b2)
{
	vec3 vm = vect_mult(a2-a1,b2-b1);
	float l = vm.lengthSQR(),res;
	if(!l)
	{
		if((a1==a2) && (b1==b2))return a1.lengthSQR(b1);
		return line_vec(b1-a1,a2-a1);

	}
	res = vec3::dot(a1-b1,vm);
	
	return (res*res)/l;
}
vec3 vec3::rnd(vec3 c,vec3 d)
{
	return c + vec3(RND11*d.x,RND11*d.y,RND11*d.z);
}
vec3 vec3::rnd01()
{
	return vec3(RND01,RND01,RND01);
}
vec3 vec3::Min(vec3 a,vec3 b)
{
	return vec3(min(a.x,b.x),min(a.y,b.y),min(a.z,b.z));
}

vec3 vec3::Max(vec3 a,vec3 b)
{
	return vec3(max(a.x,b.x),max(a.y,b.y),max(a.z,b.z));
}


vec2 vec3::XY()
{
	return vec2(x,y);
}
vec3 vec3::Clamp(vec3 min,vec3 max,vec3 v)
{
	return vec3(clamp(min.x,max.x,v.x),clamp(min.y,max.y,v.y),clamp(min.z,max.z,v.z));
}
vec3 vec3::Clamp(float min,float max,vec3 v)
{
	return vec3(clamp(min,max,v.x),clamp(min,max,v.y),clamp(min,max,v.z));
}
float vec3::dot(vec3& v1,vec3& v2)
{
	return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}
void vec3::MakeOrtDop(vec3& a,vec3& b)
{
	vec3 tmp(z,x,y);
	a = tmp - *this * (dot(*this,tmp)/lengthSQR());
	b = vec3::vect_mult(*this,a);
}
void vec3::MakeOrtDop(vec3& a)
{
	vec3 tmp(z,x,y);
	a = tmp - *this * (dot(*this,tmp)/lengthSQR());
	
}

void vec3::MakeOrtNormDop(vec3& a,vec3& b)
{
	vec3 tmp(z,x,y);
	a = tmp - *this * (dot(*this,tmp)/lengthSQR());
	a.normalize();
	b = vec3::vect_mult(*this,a);
}


//пересечение луча pos + t*nav  с кубом minimum,maximum
bool vec3::IntersectBox ( vec3 pos,vec3 nav, vec3 minimum, vec3 maximum, float& start, float& final )
{
	vec3 OMAX = ( minimum - pos ) / nav;
	
	vec3 OMIN = ( maximum - pos ) / nav;
	
	vec3 MAX = Max ( OMAX, OMIN );
	
	vec3 MIN = Min ( OMAX, OMIN );
	
	final = min ( MAX.x, min ( MAX.y, MAX.z ) );
	
	start = max ( max ( MIN.x, 0.0), max ( MIN.y, MIN.z ) );	
	
	return final > start;
}

/*

bool IntersectBox ( SRay ray, vec3 minimum, vec3 maximum, out float start, out float final )
{
	vec3 OMAX = ( minimum - ray.Origin ) / ray.Direction;
	
	vec3 OMIN = ( maximum - ray.Origin ) / ray.Direction;
	
	vec3 MAX = max ( OMAX, OMIN );
	
	vec3 MIN = min ( OMAX, OMIN );
	
	final = min ( MAX.x, min ( MAX.y, MAX.z ) );
	
	start = max ( max ( MIN.x, 0.0), max ( MIN.y, MIN.z ) );	
	
	return final > start;
}

//-------------------------------------------------------------------------------------------------

bool IntersectSphere ( SRay ray, float radius, out float start, out float final )
{
	float A = dot ( ray.Direction, ray.Direction );

	float B = dot ( ray.Direction, ray.Origin );

	float C = dot ( ray.Origin, ray.Origin ) - radius * radius;

	float D = B * B - A * C;
	
	if ( D > 0.0 )
	{
		D = sqrt ( D );

		start = max ( 0.0, ( -B - D ) / A );

		final = ( -B + D ) / A;

		return final > 0.0;
	}

	return false;
}
*/