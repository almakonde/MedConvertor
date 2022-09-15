#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
/*
struct Keyboard
{
	Keyboard();
	int key[255];
};
*/
class Camera
{
public:
	Camera();

	void MouseMove ( int x, int y );
	void MouseButton ( int button, int state );
	//void ApplyKeyboard ( Keyboard& kbd );
	
	void KeyButton ( int key, int state );

	void MouseWheel( int val );

	void SetupPosition();
	void SetupProjection(float angle,float mynear,float myfar,int x,int y,int width,int height);

	void SetCenter(vec3 c);
	void SetDistance(float d);
	float GetDistance();

	vec3 GetCenter(){return center;}
	vec3 GetPosition(){return pos;}
	vec3 GetStereoPosition();
	vec3 GetNav(){return nav;}
	vec3 GetLeft(){return left;}
	vec3 GetTop(){return top;}

	void SetXRot(float _xRot){xRot = _xRot;UpdateNavs();}
	void SetYRot(float _yRot){yRot = _yRot;UpdateNavs();}
	float GetXRot(){return xRot;}
	float GetYRot(){return yRot;}

	void Rotate(float rx,float ry);

	bool stereo_mode,left_eye;
	float eye_distance;

private:
	void UpdateNavs();

	vec3 pos,nav,top,left,center;
	float xRot,yRot,dist;

	int mx,my;
	char bt;
	bool hand_move;
};
#endif