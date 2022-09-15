#include "AllInc.h"

#include "Camera.h"
#include "AllDef.h"

#include <Math.h>



Camera::Camera(): bt(0), dist(3),center(0),hand_move(0),eye_distance(0.05f)
{
	UpdateNavs();
}

void Camera::MouseMove ( int x, int y )
{
	int dx = x-mx;
	int dy = y-my;
	if(bt&(1<<2))
	{
		//if(hand_move)
		{
			center += (left *(float)(-dx) + top * (float)dy)*(0.003f*dist);
		}
	}
	if(bt&(1<<1))
	{
		yRot -= dx*0.01f;
		xRot -= dy*0.01f;
	}

	if(bt&(1))
	{
		if(dy>0) dist *= 0.99f; else dist *= 1.01f;
	}
	if(bt)UpdateNavs();
	mx=x;
	my=y;
}
		
void Camera::MouseButton ( int button, int state )
{
	if(state) 
	{
		bt |= (1<<button);
	}
	else
		bt &= ~(1<<button);

	hand_move = (button==2 && state==1);
	
}

void Camera::KeyButton ( int key, int state )
{

}
/*
void ApplyKeyboard ( Keyboard& kbd )
{
	if(kbd.key['W'])
		center.x++;
}
*/
void Camera::MouseWheel( int val )
{
	if(val>0) dist *= 0.8f; else dist *= 1.2f;
	UpdateNavs();
}
void Camera::SetCenter(vec3 c)
{
	center=c;
	UpdateNavs();
}
float Camera::GetDistance()
{
	return dist;
}
void Camera::SetDistance(float d)
{
	dist=d;
	UpdateNavs();

}

void Camera::SetupPosition()
{
	glLoadIdentity();
	if(stereo_mode)
	{
		glTranslated(eye_distance*(left_eye?1:-1),0,-dist);
	}
	else
		glTranslated(0.0, 0.0, -dist);
	glRotated(-xRot * PI180 , 1.0, 0.0, 0.0);
	glRotated(-yRot * PI180 +180, 0.0, 1.0, 0.0);
	glTranslated(-center.x, -center.y, -center.z);

}

void Camera::SetupProjection(float angle,float mynear,float myfar,int x,int y,int width,int height)
{
	glViewport(x,y,width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(angle, width/(double)height, mynear, myfar);
    glMatrixMode(GL_MODELVIEW);
}

void Camera::UpdateNavs()
{
	float sin_a_y=sin(yRot),cos_a_y=cos(yRot),sin_a_x=sin(xRot),cos_a_x=cos(xRot);
	
	nav.set(sin_a_y*cos_a_x,sin_a_x,cos_a_y*cos_a_x);
	top.set(-sin_a_y*sin_a_x,cos_a_x,-cos_a_y*sin_a_x);
	left.set(-cos_a_y,0,sin_a_y);

	

	pos=nav*(-dist);
	pos += center;
}

void Camera::Rotate(float rx,float ry)
{
	vec3 old_pos = pos;
	yRot += ry;
	xRot += rx;
	UpdateNavs();
	center += old_pos-pos;
	pos = old_pos;
}
vec3 Camera::GetStereoPosition()
{
	if(!stereo_mode)return pos;
	return pos+left*(left_eye?-1:1)*eye_distance;
}