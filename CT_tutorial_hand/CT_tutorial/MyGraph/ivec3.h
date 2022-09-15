
#ifndef Iivec3_H_INCLUDED
#define Iivec3_H_INCLUDED



struct ivec3
{
	int x,y,z;

	ivec3(){}
	ivec3(int v){x=v;y=v;z=v;}
	ivec3(int n_x,int n_y,int n_z);

	void set(int n_x,int n_y,int n_z);
	void add(int n_x,int n_y,int n_z);
	int lengthSQR();
	int lengthSQR(ivec3& v);
	
	ivec3 operator * (int);
	ivec3 operator / (int);
	ivec3 operator % (int);
	ivec3 operator + (ivec3);
	ivec3 operator - (ivec3);

	void operator += (ivec3&);
	void operator -= (ivec3&);

	bool operator == (ivec3&);
	ivec3 operator * (ivec3&);
	void operator *= (int);
	void operator /= (int);
	
	void Inv();

	static int dot(ivec3& v1,ivec3& v2);

	bool InBounds(ivec3 a,ivec3 b);

	static ivec3 rnd(ivec3 c,ivec3 d);

	static ivec3 Min(ivec3 a,ivec3 b);
	static ivec3 Max(ivec3 a,ivec3 b);
	static ivec3 Abs(ivec3 a);

	static ivec3 Clamp(int min,int max,ivec3 v);
	static ivec3 Clamp(ivec3 min,ivec3 max,ivec3 v);

};


#endif