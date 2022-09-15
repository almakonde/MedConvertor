#ifndef VEC_INCLUDED
#define VEC_INCLUDED


#include <stdlib.h>
#include <vector>
#include "vec3.h"
#include "ivec3.h"

typedef std::vector<bool> bvec;
typedef std::vector<int> ivec;
typedef std::vector<float> vec;

typedef std::vector<vec2> v2vec;
typedef std::vector<vec3> v3vec;
typedef std::vector<ivec3> iv3vec;
typedef std::vector<std::string> svec;
/*
template <class T>
void DeleteElement(std::vector<T>& v, int id)
{
	if(id<v.size())
	{
		std::vector<T>::erase(
		v.
	}
}
*/
#endif