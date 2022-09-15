#include "AllInc.h"

#include "Draw2D.h"
#include <Math.h>
#include "AllDef.h"


void DrawRectangle(vec2 a,vec2 b)
{
	glBegin(GL_LINE_LOOP);
	glVertex2fv(&a.x);
	glVertex2f(a.x,b.y);
	glVertex2fv(&b.x);
	glVertex2f(b.x,a.y);
	glEnd();
}
void DrawLine(vec2 a,vec2 b)
{
	glBegin(GL_LINES);
	glVertex2fv(&a.x);
	glVertex2fv(&b.x);
	glEnd();
}

void DrawFilledRectangle(vec2 a,vec2 b)
{
	glBegin(GL_QUADS);
	glVertex2fv(&a.x);
	glVertex2f(a.x,b.y);
	glVertex2fv(&b.x);
	glVertex2f(b.x,a.y);
	glEnd();
}
void DrawGrid(vec2 b1,vec2 b2,float cell_size,vec4 color1,vec4 color10)
{
	glBegin(GL_LINES);

	float i;
	for(i = cell_size*int(b1.x/cell_size);i<=cell_size*int(b2.x/cell_size);i+=cell_size)
	{
		if(int(i/cell_size)%10==0)glColor4fv(&color10.x);else glColor4fv(&color1.x);
		glVertex2f(i,b1.y);
		glVertex2f(i,b2.y);
	}
	for(i = cell_size*int(b1.y/cell_size);i<=cell_size*int(b2.y/cell_size);i+=cell_size)
	{
		if(int(i/cell_size)%10==0)glColor4fv(&color10.x);else glColor4fv(&color1.x);
		glVertex2f(b1.x,i);
		glVertex2f(b2.x,i);
	}
	glEnd();
}

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