#ifndef VEC3_INCLUDED
#define VEC3_INCLUDED



#define VEC_BY_ID(t,i) *(&(t).x+i)
#define BY_ID(i) *(&x+i)

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

	void RotateOij(float&sina,float&cosa,int i,int j);//поворот в плоскости координатных осей i,j
	void RotateOij(float ang,int i,int j);

	void MakeOrtDop(vec3& a);
	void MakeOrtDop(vec3& a,vec3& b);
	void MakeOrtNormDop(vec3& a,vec3& b);
	void normalize();
	vec3 normalized();
	vec3 proected_on(vec3 norm);
	vec3 proected_on(vec3 a,vec3 b);

	static float dot(vec3& v1,vec3& v2);
	static vec3 vect_mult(vec3& v1,vec3& v2);//векторное умножение
	static vec3 rnd(vec3 c,vec3 d);
	static vec3 rnd01();

	static vec3 Clamp(float min,float max,vec3 v);
	static vec3 Clamp(vec3 min,vec3 max,vec3 v);
	static vec3 Min(vec3 a,vec3 b);
	static vec3 Max(vec3 a,vec3 b);
	static bool IntersectBox ( vec3 pos,vec3 nav, vec3 minimum, vec3 maximum, float& start, float& final );
	

	static float line_line(vec3& a1,vec3& a2,vec3& b1,vec3& b2);//расстояние(квадрат) между прямыми a и b

	static float line_vec(vec3 c,vec3 b);//расстояние(квадрат) от точки c до прямой Ob
	static vec3 vec3::flat_cross_line(flat f, vec3 l);//пересечение плоскости с линией

};
struct flat
{
	flat(){}
	flat(vec3 nd,vec3 nn);
	vec3 n,d;
};



#endif