#line 1 "MyGraph\\CS3.cpp"

#line 1 "d:\\projects\\vr\\dvr up1\\ct_tutorial_hand\\ct_tutorial\\mygraph\\CS3.h"



#line 1 "d:\\projects\\vr\\dvr up1\\ct_tutorial_hand\\ct_tutorial\\mygraph\\vec3.h"








struct flat;
struct vec2;

struct vec3
{
	float x,y,z;

	vec3(){}
	vec3(float v){x=v;y=v;z=v;}
	
	vec3(float n_x,float n_y,float n_z);
	vec3(vec2 v2,float n_z);

	void set(float n_x,float n_y,float n_z);
	void add(float n_x,float n_y,float n_z);
	float lengthSQR();
	float length();
	float length(vec3& v);
	float lengthSQR(vec3& v);
	
	vec3 operator * (float);
	vec3 operator / (float);
	vec3 operator + (vec3);
	vec3 operator - (vec3);

	void operator += (vec3&);
	void operator -= (vec3&);

	bool operator == (vec3&);
	vec3 operator * (vec3&);
	vec3 operator / (vec3&);
	void operator *= (float);
	void operator /= (float);
	
	void Inv();
	vec2 XY();

	void RotateOij(float&sina,float&cosa,int i,int j);
	void RotateOij(float ang,int i,int j);

	void MakeOrtDop(vec3& a);
	void MakeOrtDop(vec3& a,vec3& b);
	void MakeOrtNormDop(vec3& a,vec3& b);
	void normalize();
	vec3 normalized();
	vec3 proected_on(vec3 norm);
	vec3 proected_on(vec3 a,vec3 b);

	static float dot(vec3& v1,vec3& v2);
	static vec3 vect_mult(vec3& v1,vec3& v2);
	static vec3 rnd(vec3 c,vec3 d);
	static vec3 rnd01();

	static vec3 Clamp(float min,float max,vec3 v);
	static vec3 Clamp(vec3 min,vec3 max,vec3 v);
	static vec3 Min(vec3 a,vec3 b);
	static vec3 Max(vec3 a,vec3 b);
	static bool IntersectBox ( vec3 pos,vec3 nav, vec3 minimum, vec3 maximum, float& start, float& final );
	

	static float line_line(vec3& a1,vec3& a2,vec3& b1,vec3& b2);

	static float line_vec(vec3 c,vec3 b);
	static vec3 vec3::flat_cross_line(flat f, vec3 l);

	
	
};
struct flat
{
	flat(){}
	flat(vec3 nd,vec3 nn);
	vec3 n,d;
};



#line 87 "d:\\projects\\vr\\dvr up1\\ct_tutorial_hand\\ct_tutorial\\mygraph\\vec3.h"
#line 5 "d:\\projects\\vr\\dvr up1\\ct_tutorial_hand\\ct_tutorial\\mygraph\\CS3.h"


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


#line 26 "d:\\projects\\vr\\dvr up1\\ct_tutorial_hand\\ct_tutorial\\mygraph\\CS3.h"
#line 3 "MyGraph\\CS3.cpp"



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
