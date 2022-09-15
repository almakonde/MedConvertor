#include "AllInc.h"

#include <GL/glfw.h>
#include "AllDef.h"
#include "Mouse.h"
#include "Camera.h"
#include "Draw.h"
#include "Iso.h"
#include "output.h"
#include <Math.h>
#include <ivec3.h>
#include "Draw2D.h"


extern Mouse mouse;
extern Camera cam;
extern int keyboard[255];
extern int width, height;

extern IsoViewer*iso;
extern int stereo_on, anag;

void DrawScene()
{
	cam.stereo_mode = stereo_on;
	cam.SetupPosition();				//домножение текущей матрицы преобразований в соответствии с положением и ориентацией камеры
	iso->ApplyCamera(&cam);				//обновление камеры в шейдерах
	iso->Draw(&cam);					//вывод объёмных данных
	

	if(stereo_on!=1)
	{
		glColor3d(1,1,1);
		if(keyboard['3'])
			DrawDot(iso->GetMinBox());
		if(keyboard['4'])
			DrawDot(iso->GetMaxBox());
	}
}

// рисуем сцену в соответствии со стерео-режимом
void FullDraw()
{

		switch(stereo_on)		// stereo_on:	0-без стерео  1-анаглиф  2-для проектора  3-для монитора Zalman  4-для технологии 3DVision (только для карт Quadro)
		{
		case 0:	
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				DrawScene();
			}
			break;
		case 1:
			{
				glDrawBuffer(GL_BACK);
    
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glReadBuffer(GL_BACK);
				glClear(GL_ACCUM_BUFFER_BIT);

				iso->SetAnag(anag,0);
				cam.left_eye = 0;
				DrawScene();

				glFlush();
				//glClear(GL_DEPTH_BUFFER_BIT);
    
				glAccum(GL_LOAD, 1.0f);                
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				iso->SetAnag(anag,1);
				cam.left_eye = 1;
				
				DrawScene();

				glFlush();
				glAccum(GL_ACCUM, 1.0f);
				glAccum(GL_RETURN, 1.0f);

				

			}
			break;
		case 2:
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				cam.left_eye = 0;
				cam.SetupProjection(45,0.3f,60.0f,0,0,width/2,height);

				DrawScene();

				cam.left_eye = 1;
				cam.SetupProjection(45,0.3f,60.0f,width/2,0,width/2,height);
				DrawScene();
				
			}
			break;
		case 3:
			{
				
				glEnable(GL_STENCIL_TEST);
				
//				glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
				cam.left_eye = 0;
				glStencilFunc(GL_EQUAL, 0, 1);
				DrawScene();

				cam.left_eye = 1;
				glStencilFunc(GL_EQUAL, 1, 1);
				DrawScene();

				

				glDisable(GL_STENCIL_TEST);
			}
			break;
		case 4:
			{

				glDrawBuffer(GL_BACK_LEFT);  
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      //clear color and depth buffers
				cam.left_eye = 0;
				DrawScene();

				glDrawBuffer(GL_BACK_RIGHT);  
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      //clear color and depth buffers
				cam.left_eye = 1;
				DrawScene();

				
  
  			}
			break;
		}
}

// инициализация маски в виде горизонтальных полос на экране (для вывода в соотв. режиме стерео)
void InitInterlace()
{
	Begin2D(width,height);
	glEnable(GL_STENCIL_TEST);
	glClearStencil(0);
	//glStencilMask(1);
	glClear (GL_STENCIL_BUFFER_BIT);
	

	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	
	glBegin(GL_LINES);
	for(int i=0;i<height;i+=2)
	{
		glVertex2f(0,i);
		glVertex2f(width,i);
	}
	glEnd();

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDisable(GL_STENCIL_TEST);
	End2D();
}

// установить стерео-режим
// stereo_mode:	0-без стерео  1-анаглиф  2-для проектора  3-для монитора Zalman  4-для технологии 3DVision (только для карт Quadro)
void SetStereoMode(int stereo_mode)
{
	cam.stereo_mode = !!stereo_mode;
	switch(stereo_on)
			{
			case 0:	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glfwSwapBuffers();
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;
			case 1: iso->SetAnag(0,0);
				
				break;
			case 2: cam.SetupProjection(45,0.3f,60.0f,0,0,width,height);
				break;
			case 4:glDrawBuffer(GL_BACK);
				break;
			}
	
	stereo_on = stereo_mode;
	if(stereo_on==3)InitInterlace();
}
