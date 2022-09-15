#ifndef CS3_INCLUDED
#define CS3_INCLUDED

#include "vec3.h"

//система координат
struct CS3
{
	vec3 center;
	vec3 x,y,z;

	CS3();
	CS3(vec3 nc,vec3 nx,vec3 ny,vec3 nz);

	CS3 _1();
	vec3 GetCoords(vec3 pt);
	vec3 GetCoordsRot(vec3 pt);

	void Build(vec3 c,vec3 _z,vec3 u);
	void Build(vec3 c,vec3 _z);

};


#endif