#ifndef ISO_H
#define ISO_H
#include "vec3.h"
#include "vec2.h"
#include "Camera.h"

#include "SimText.h"
#include "SimText3D.h"
#include <ivec3.h>

class ShaderProgram;

class IsoViewer
{
public:
	IsoViewer();
	~IsoViewer();
	void ApplyCamera(Camera* c);

	void UploadFieldData(void*data,ivec3 size,int type,vec3 scale1);

	void Draw(Camera* c);

	void SetLevel(float nl1);
//	void UpdateUniforms();
	void SetBoundingBox(vec3 a,vec3 b);
	float GetMinLevel(){return l1;}
	vec3 GetMinBox(){return b1;}
	vec3 GetMaxBox(){return b2;}

	void SetAnag(int s,bool left);

	bool draw_frame_is;
	ivec3 size;
private:

	vec3 anag[3];

	

	ShaderProgram *ps;

	SimText3D* st;
	SimText3D* st_i;
	SimText3D* st_n;

	float l1;
	vec3 b1,b2,scale;

	
};

#endif