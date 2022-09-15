#ifndef AllDefinitions_h_Included
#define AllDefinitions_h_Included

#include "AllInc.h"
#include <stdlib.h>
#include <windows.h>

#define EPSILON 0.0001f
#ifdef _DEBUG
	#define MY_ASSERT(a) if(!(a))throw
#else
	#define MY_ASSERT(a) 
#endif

#define PI180 57.295779f
#define RND01 (((float)rand())/RAND_MAX)
#define RNDINT(a) (rand()%a)
#define RND11 (((float)((int)(rand()-(RAND_MAX>>1))))/(RAND_MAX>>1))

#define NOTNULL(a) ((a)?(a):0.000001f)
#define SGN(a) ((a>0)?1:((a<0)?-1:0))

#define M_E        2.71828182845904523536
#define HALF_PI 1.570796326

#define PI 3.141592653
#define DOUBLE_PI 6.283185307
#define PI_180 0.017453292
#define SQ2 1.414213562373
#define SQ3 1.732050807568
#define SQ7 2.645751311064
#define TAN_22_5 0.4142135623731f

#ifndef max
	#define max(a,b) ((a)>(b))?(a):(b)
#endif
#ifndef min
	#define min(a,b) ((a)<(b))?(a):(b)
#endif

#define sqr(a) ((a)*(a))

template<class T>
void swap(T&a,T&b)
{
	T tmp = a;
	a = b;
	b = tmp;
}
template<class T,int N>
void swap(T*a,T*b)
{
	for(int i=0;i<N;i++,a++,b++)
	{
		T tmp = *a;
		*a = *b;
		*b = tmp;
	}
}
template<class T>
T clamp(T min,T max, T val)
{
	if(val>=max) return max;
	if(val<=min) return min;
	return val;
}



#endif