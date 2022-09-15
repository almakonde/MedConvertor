
#ifndef Iivec2_H_INCLUDED
#define Iivec2_H_INCLUDED



struct ivec2
{
	int x,y;

	ivec2(){}
	ivec2(int v){x=v;y=v;}
	ivec2(int n_x,int n_y);

	void set(int n_x,int n_y);
	int lengthSQR();
	int lengthSQR(ivec2& v);
	
	ivec2 operator * (int);
	ivec2 operator / (int);
	ivec2 operator % (int);
	ivec2 operator + (ivec2);
	ivec2 operator - (ivec2);

	void operator += (ivec2&);
	void operator -= (ivec2&);

	bool operator == (ivec2&);
	ivec2 operator * (ivec2&);
	void operator *= (int);
	void operator /= (int);
	
	void Inv();

	static int dot(ivec2& v1,ivec2& v2);

	bool InBounds(ivec2 a,ivec2 b);

	static ivec2 rnd(ivec2 c,ivec2 d);

	static ivec2 Min(ivec2 a,ivec2 b);
	static ivec2 Max(ivec2 a,ivec2 b);

};


#endif