
#ifndef DRAW_H
#define DRAW_H

#include "vec3.h"
#include "CS3.h"

#define glMYLine(x1,y1,z1,x2,y2,z2) {glBegin(GL_LINES);glVertex3f(x1,y1,z1);glVertex3f(x2,y2,z2);glEnd();}

void ChangeCoordSystem(vec3 center, vec3 x, vec3 y, vec3 z);
void ChangeCoordSystem(CS3 cs);

void DrawCylinder();
void DrawSphere();

void DrawCubeFrame(vec3 a,vec3 b);
void DrawCube(vec3 a,vec3 b);
void DrawDot(vec3 dot);
void DrawPrizma(vec3 v1,vec3 v2,vec3 v3,vec3 v4);
void DrawOs(vec3 n);
void DrawLine(vec3 a,vec3 b);
void DrawCylinder(vec3 a,vec3 b,float radius);
void DrawSphere(vec3 pos,float radius);

#endif