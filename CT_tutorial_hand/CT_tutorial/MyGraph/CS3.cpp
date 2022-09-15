
#include "CS3.h"



CS3::CS3():center(0),x(1,0,0),y(0,1,0),z(0,0,1)
{}
CS3::CS3(vec3 nc,vec3 nx,vec3 ny,vec3 nz):center(nc),x(nx),y(ny),z(nz)
{}


void CS3::Build(vec3 c,vec3 _z,vec3 u)
{
	center = c;
	z = _z;
	x = u.proected_on(z).normalized();
	y = vec3::vect_mult(x,z);
}
void CS3::Build(vec3 c,vec3 _z)
{
	center = c;
	z = _z;
	z.MakeOrtNormDop(x,y);
}
vec3 CS3::GetCoords(vec3 pt)
{
	vec3 res;
	pt -= center;
	res.x = vec3::dot(pt,x);
	res.y = vec3::dot(pt,y);
	res.z = vec3::dot(pt,z);

	return res;
}
vec3 CS3::GetCoordsRot(vec3 pt)
{
	vec3 res;
	res.x = vec3::dot(pt,x);
	res.y = vec3::dot(pt,y);
	res.z = vec3::dot(pt,z);

	return res;
}

CS3 CS3::_1()
{
	CS3 res;
	res.center = GetCoords(vec3(0));
	res.x = GetCoordsRot(vec3(1,0,0));
	res.y = GetCoordsRot(vec3(0,1,0));
	res.z = GetCoordsRot(vec3(0,0,1));

	return res;
}