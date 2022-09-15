#ifndef DRAW2D_H
#define DRAW2D_H

#include "vec2.h"
#include "ivec2.h"
#include "vec4.h"


void DrawRectangle(vec2 a,vec2 b);
void DrawLine(vec2 a,vec2 b);
void DrawFilledRectangle(vec2 a,vec2 b);

void DrawGrid(vec2 b1,vec2 b2,float cell_size,vec4 color1=vec4(1,1,1,0.2f),vec4 color10=vec4(1,1,1,0.4f));

void Begin2D ( int width, int height );
void End2D ( void );

#endif