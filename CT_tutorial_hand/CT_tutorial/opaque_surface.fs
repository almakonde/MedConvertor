#version 120

varying vec3 vertex, normal;	
uniform float level1, step_length;
uniform vec3 box1,box2;				

uniform vec3 pos;					
uniform vec3 nav;					
uniform vec3 size;					
uniform vec3 scale;

uniform sampler3D f_text;			



uniform vec3 RFrom;
uniform vec3 GFrom;
uniform vec3 BFrom;

const vec3 level_color1 = vec3(0.7,0.8,1.0);
const vec3 level_color2 = vec3(1.0,0.8,0.5);
const vec3 levelLineColor = vec3(1.0,0.0,0.0);
const float surface_opacity = 0.6;


const float z_near=0.3;
const float z_far=60.0;


float Equ(in vec3 arg)
{
	return texture3D(f_text, arg/scale).x;
}


vec3 GradEqu(in vec3 arg)
{
	vec3 delta=vec3(1.0)/size;
	vec3 res;
	res.x = Equ(vec3(arg.x+delta.x,arg.y,arg.z))-Equ(vec3(arg.x-delta.x,arg.y,arg.z));
	res.y = Equ(vec3(arg.x,arg.y+delta.y,arg.z))-Equ(vec3(arg.x,arg.y-delta.y,arg.z));
	res.z = Equ(vec3(arg.x,arg.y,arg.z+delta.z))-Equ(vec3(arg.x,arg.y,arg.z-delta.z));
	return normalize(res);
}

#define K_A 0.1
#define K_D 0.9
#define K_S 0.9
#define P 64.0

vec3 Phong ( vec3 point, vec3 normal, vec3 color)
{
   	vec3 light = normalize( pos - point );
	float diffuse = dot ( light, normal );
	vec3 reflect = reflect ( -light, normal );
	float specular = pow ( max (0.0, dot ( reflect, light ) ), P );
	return K_A * vec3(1.0) + diffuse * ( K_D * color + K_S * specular * vec3(1.0) );
}

float IntersectBox ( vec3 b1, vec3 b2, vec3 pos, vec3 nav)
{
	vec3 OMAX = ( b1 - pos ) / nav;
	vec3 OMIN = ( b2 - pos ) / nav;
	vec3 MAX = max ( OMAX, OMIN );
	float res = min ( MAX.x, min ( MAX.y, MAX.z ) );
	return res;
}

float GetDepth(vec3 ps)
{
	return z_far/(z_far-z_near) - (z_far*z_near/(z_far-z_near))/(dot(ps-pos,nav));
}


bool IntersectBox ( vec3 Origin,vec3 Direction, vec3 minimum, vec3 maximum, out float start, out float final )
{
	vec3 OMAX = ( minimum - Origin ) / Direction;
	vec3 OMIN = ( maximum - Origin ) / Direction;
	vec3 MAX = max ( OMAX, OMIN );
	vec3 MIN = min ( OMAX, OMIN );
	final = min ( MAX.x, min ( MAX.y, MAX.z ) );
	start = max ( max ( MIN.x, 0.0), max ( MIN.y, MIN.z ) );	
	return final > start;
}

bool isLevelLine(vec3 pt)
{
	return mod(pt.y, scale.y / 6.0) < 0.004;
}

void main()
{
	float start,final;
	vec3 color = vec3(0.0);						
	vec3 norm = normal, ray = normalize(vertex-pos);
	vec4 step  = vec4(ray*step_length,step_length);	
	vec4 ps = vec4(vertex,0.0);						

	IntersectBox (ps.xyz,ray,box1,box2,start,final );
	ps = ps + step*(start/step_length);


	float e = Equ(ps.xyz),e0;						
	ps+=step;

			gl_FragDepth = 1.0;				
			for(float ii=0.0;ii<2000.0 && (ps.w<final) ;ii+=0.1)
			{
				e0 = e;
				e = Equ(ps.xyz);			
				
				vec3 tmp = vec3(level1,e0,e);
				if(clamp(tmp.x,tmp.y,tmp.z) == tmp.x)
				{
					vec3 ps11 = ps.xyz + step.xyz*((tmp.x-tmp.z)/(tmp.z-tmp.y));
					norm = -GradEqu(ps11);
												
					color = Phong(ps11,norm, isLevelLine(ps11) ? levelLineColor : level_color2); 
					
					if(gl_FragDepth==1.0)gl_FragDepth = max(GetDepth(ps.xyz-step.xyz),0.1);
					break;
				}else
				if(clamp(tmp.x,tmp.z,tmp.y) == tmp.x)
				{
					vec3 ps11 = ps.xyz + step.xyz*((tmp.x-tmp.z)/(tmp.z-tmp.y));
					norm = GradEqu(ps11);
					color = Phong(ps11,norm, isLevelLine(ps11) ? levelLineColor : level_color1);
					if(gl_FragDepth==1.0)gl_FragDepth = max(GetDepth(ps.xyz-step.xyz),0.1);
					break;
				}
				ps+=step;

			

			}
			
				
	
	mat3 m_anag = mat3(RFrom,GFrom,BFrom);	

	
	gl_FragColor = vec4( color * m_anag ,1.0);	
}
