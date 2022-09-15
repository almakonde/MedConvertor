#include "Draw.h"
#include "AllInc.h"
#include <Math.h>
#include "AllDef.h"
#include "mat34.h"

void DrawLine(vec3 a,vec3 b)
{
	glBegin(GL_LINES);
	glVertex3fv(&a.x);
	glVertex3fv(&b.x);
	glEnd();
}
void DrawCubeFrame(vec3 a,vec3 b)
{

	glBegin(GL_LINE_LOOP);		glVertex3f(a.x, a.y,  b.z);		glVertex3f(b.x, a.y,  b.z);			glVertex3f(b.x,  b.y,  b.z);		glVertex3f( a.x,  b.y,  b.z);		glEnd();	
	glBegin(GL_LINE_LOOP);		glVertex3f(a.x, a.y, a.z);		glVertex3f(a.x,  b.y, a.z);			glVertex3f(b.x,  b.y, a.z);			glVertex3f( b.x, a.y, a.z);		glEnd();	
	glBegin(GL_LINE_LOOP);		glVertex3f(a.x,  b.y, a.z);		glVertex3f(a.x,  b.y,  b.z);		glVertex3f(b.x,  b.y,  b.z);		glVertex3f( b.x,  b.y, a.z);		glEnd();	
	glBegin(GL_LINE_LOOP);		glVertex3f(a.x,  a.y, a.z);		glVertex3f(b.x,  a.y,  a.z);		glVertex3f(b.x,  a.y,  b.z);		glVertex3f( a.x,  a.y, b.z);		glEnd();	
	glBegin(GL_LINE_LOOP);		glVertex3f(b.x, a.y, a.z);		glVertex3f(b.x,  b.y, a.z);			glVertex3f(b.x,  b.y,  b.z);		glVertex3f( b.x, a.y,  b.z);		glEnd();	
	glBegin(GL_LINE_LOOP);		glVertex3f(a.x, a.y,a.z);	    	glVertex3f(a.x, a.y,  b.z);			glVertex3f(a.x, b.y, b.z);			glVertex3f( a.x,  b.y, a.z);		glEnd();	
	
}
void DrawCube(vec3 a,vec3 b)
{

	glBegin(GL_QUADS);
		glNormal3d(0.0, 0.0, 1.0);		glVertex3f(a.x, a.y,  b.z);		glVertex3f(b.x, a.y,  b.z);			glVertex3f(b.x,  b.y,  b.z);		glVertex3f( a.x,  b.y,  b.z);	
		glNormal3d(0.0, 0.0, -1.0);		glVertex3f(a.x, a.y, a.z);		glVertex3f(a.x,  b.y, a.z);			glVertex3f(b.x,  b.y, a.z);			glVertex3f( b.x, a.y, a.z);	
		glNormal3d(0.0, 1.0, 0.0);		glVertex3f(a.x,  b.y, a.z);		glVertex3f(a.x,  b.y,  b.z);		glVertex3f(b.x,  b.y,  b.z);		glVertex3f( b.x,  b.y, a.z);	
		glNormal3d(0.0, -1.0, 0.0);		glVertex3f(a.x,  a.y, a.z);		glVertex3f(b.x,  a.y,  a.z);		glVertex3f(b.x,  a.y,  b.z);		glVertex3f( a.x,  a.y, b.z);	
		glNormal3d(1.0, 0.0, 0.0);		glVertex3f(b.x, a.y, a.z);		glVertex3f(b.x,  b.y, a.z);			glVertex3f(b.x,  b.y,  b.z);		glVertex3f( b.x, a.y,  b.z);	
		glNormal3d(-1.0, 0.0, 0.0);		glVertex3f(a.x, a.y,a.z);	    	glVertex3f(a.x, a.y,  b.z);			glVertex3f(a.x, b.y, b.z);			glVertex3f( a.x,  b.y, a.z);	
	glEnd();	
	
}

void DrawDot(vec3 dot)
{
	glPointSize(10.0f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex3fv(&dot.x);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1);

}
/*
void Begin2D ( int width, int height )
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, width, height,0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
}

void End2D ( void )
{
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  
}

*/


void DrawPrizma(vec3 v1,vec3 v2,vec3 v3,vec3 v4)
{
	glBegin(GL_TRIANGLES);

	vec3 nrm;
	nrm = vec3::vect_mult(v2-v1,v3-v1);
	glNormal3fv(&nrm.x);

	glVertex3fv(&v1.x);
	glVertex3fv(&v2.x);
	glVertex3fv(&v3.x);

	nrm = vec3::vect_mult(v2-v1,v4-v1);
	glNormal3fv(&nrm.x);

	glVertex3fv(&v1.x);
	glVertex3fv(&v2.x);
	glVertex3fv(&v4.x);

	nrm = vec3::vect_mult(v2-v3,v4-v3);
	glNormal3fv(&nrm.x);

	glVertex3fv(&v2.x);
	glVertex3fv(&v3.x);
	glVertex3fv(&v4.x);

	nrm = vec3::vect_mult(v3-v1,v4-v1);
	glNormal3fv(&nrm.x);

	glVertex3fv(&v3.x);
	glVertex3fv(&v1.x);
	glVertex3fv(&v4.x);
	glEnd();
}

void DrawOs(vec3 n)
{
	float k=0.8f,arr_h=0.2f,arr_d=0.04f;
	glLineWidth(2);
	if(!n.x)
	{
		glColor4d(1,0,0,0.5);
		glMYLine(0,0,0,k,0,0);
		DrawPrizma(vec3(k,0,0),vec3(k-arr_h,arr_d,0),vec3(k-arr_h,-arr_d,-arr_d),vec3(k-arr_h,0,arr_d));
	}
	
	if(!n.y)
	{
		glColor4d(0,1,0,0.5);
		glMYLine(0,0,0,0,k,0);
		DrawPrizma(vec3(0,k,0),vec3(arr_d,k-arr_h,0),vec3(-arr_d,k-arr_h,-arr_d),vec3(0,k-arr_h,arr_d));
	}
	
	if(!n.z)
	{
		glColor4d(0,0,1,0.5);
		glMYLine(0,0,0,0,0,k);
		DrawPrizma(vec3(0,0,k),vec3(arr_d,0,k-arr_h),vec3(-arr_d,-arr_d,k-arr_h),vec3(0,arr_d,k-arr_h));
	}
	glLineWidth(1);
	
}

void DrawSphere()
{
	static GLuint list_id=0;
	if(!list_id) 
	{
		int sides_a = 21;
		int sides_b = 21;

		list_id = glGenLists(1);
		glNewList(list_id, GL_COMPILE);
		
		float ang=(float)(PI/sides_a);
		float sina=sin(ang),cosa=cos(ang);

		float ang2=(float)(PI*2.0/sides_b);
		float sinb=sin(ang2),cosb=cos(ang2);
		int i,j;
		vec3 v0(0,1,0),u0,u1,w0,w1;
		vec3 v1(v0);
		glBegin(GL_QUADS);
		for(i=0;i<sides_a;i++)
		{
			v1.RotateOij(sina,cosa,0,1);
		
			u0 = v0;
			w0 = v1;
			u1 = v0;
			w1 = v1;
			for(j=0;j<sides_b;j++)
			{
				u1.RotateOij(sinb,cosb,0,2);
				w1.RotateOij(sinb,cosb,0,2);

				//AddQuad(&tmp,u0,u1,w1,w0);
				glNormal3fv(&u0.x);
				glVertex3fv(&u0.x);
				glNormal3fv(&u1.x);
				glVertex3fv(&u1.x);
				glNormal3fv(&w1.x);
				glVertex3fv(&w1.x);
				glNormal3fv(&w0.x);
				glVertex3fv(&w0.x);

				u0=u1;
				w0=w1;
			}
			
			
			
			v0=v1;
		}
		glEnd();
		
		glEndList();
	}
	glCallList(list_id);
}

void DrawCylinder()
{
	static GLuint list_id=0;
	if(!list_id) 
	{
		list_id = glGenLists(1);
		glNewList(list_id, GL_COMPILE);

		int sides = 30;
		float ang=(float)(PI*2.0/sides);
		float sina=sin(ang),cosa=cos(ang);
		int i;
		
		vec3 t1(1,0,0),t0(1,0,0),hh(0,1,0),hh0(0,0,0);
		glBegin(GL_QUADS);
		for(i=0;i<sides;i++)
		{
			t1.RotateOij(sina,cosa,0,2);
			glNormal3f(t1.x,0,t1.z);
			glVertex3fv(&t1.x);
			glNormal3f(t0.x,0,t0.z);
			glVertex3fv(&t0.x);
			vec3 t1hh=t1+hh;
			vec3 t0hh=t0+hh;
			glNormal3f(t0hh.x,0,t0hh.z);
			glVertex3fv(&t0hh.x);
			glNormal3f(t1hh.x,0,t1hh.z);
			glVertex3fv(&t1hh.x);
			//AddQuad(&tmp,t0,t1,t1+hh,t0+hh);
			//tmp.AddTriangle(t0,t1,hh0);
			//tmp.AddTriangle(t1+hh,t0+hh,hh);
			t0=t1;
		}
		glEnd();
		
		ang=(float)(PI*2.0/sides);
		t1.set(1,0,0);
		t0.set(1,0,0);
		glBegin(GL_TRIANGLES);
		for(i=0;i<sides;i++)
		{
			t1.RotateOij(sina,cosa,0,2);
			glNormal3f(0,-1,0);
			glVertex3fv(&t0.x);
			glNormal3f(0,-1,0);
			glVertex3fv(&t1.x);
			glNormal3f(0,-1,0);
			glVertex3fv(&hh0.x);

			vec3 t1hh=t1+hh;
			vec3 t0hh=t0+hh;
			glNormal3f(0,1,0);
			glVertex3fv(&t1hh.x);
			glNormal3f(0,1,0);
			glVertex3fv(&t0hh.x);
			glNormal3f(0,1,0);
			glVertex3fv(&hh.x);

			//tmp.AddTriangle(t0,t1,hh0);
			//tmp.AddTriangle(t1+hh,t0+hh,hh);
			t0=t1;
		}
		glEnd();
		glEndList();
	}
	glCallList(list_id);
}
void ChangeCoordSystem(CS3 cs)
{
	ChangeCoordSystem(cs.center,cs.x,cs.y,cs.z);

}
void ChangeCoordSystem(vec3 center, vec3 x, vec3 y, vec3 z)
{
	float m[4][4];

	m[0][0] = x.x;
	m[0][1] = x.y;
	m[0][2] = x.z;
	m[0][3] = 0;

	m[1][0] = y.x;
	m[1][1] = y.y;
	m[1][2] = y.z;
	m[1][3] = 0;

	m[2][0] = z.x;
	m[2][1] = z.y;
	m[2][2] = z.z;
	m[2][3] = 0;

	m[3][0] = center.x;
	m[3][1] = center.y;
	m[3][2] = center.z;
	m[3][3] = 1;

	glMultMatrixf((float*)m);
}

void DrawCylinder(vec3 a,vec3 b,float radius)
{
	glPushMatrix();
	vec3 ny = b-a, nx,nz;
	ny.MakeOrtDop(nx,nz);
	nx.normalize();
	nz.normalize();
//	DrawLine(a,a+nx);
//	DrawLine(a,a+ny);
//	DrawLine(a,a+nz);

	ChangeCoordSystem(a,nx*radius,ny,nz*radius);
	DrawCylinder();

	glPopMatrix();
	
}
void DrawSphere(vec3 pos,float radius)
{
	glPushMatrix();
	
	glTranslatef(pos.x,pos.y,pos.z);
	glScaled(radius,radius,radius);
	DrawSphere();

	glPopMatrix();
}