#include "AllInc.h"

#include <GL/glfw.h>
#include <stdio.h>
#include <stdlib.h>
#include "AllDef.h"
#include "Mouse.h"
#include "Camera.h"
#include "Draw.h"
#include "Iso.h"
#include "output.h"
#include <Math.h>
#include <ivec3.h>
#include "Draw2D.h"



Mouse mouse;
Camera cam;

IsoViewer*iso;

int keyboard[255];
int width = 450, height = 450;

int stereo_on=0, anag=1;


void SetStereoMode(int);
void InitInterlace();
void FullDraw();

std::string GetInt(int val,int digits)
{
	std::string res;
	res.resize(digits);
	for(int i=0;i<digits;i++)
	{
		res[digits-i-1] = '0'+val%10;
		val/=10;
	}
	return res;
}


void LoadDataset()
{
	ivec3 size(244, 124, 257);
	int type = GL_SHORT;
	short *arr=new short[size.x*size.y*size.z];
	
	std::string fn = "Hand16.raw";
	std::ifstream fs(fn.c_str(),std::ios::in | std::ios::binary);
	if(!fs)return;
	vec3 scale = vec3(1,size.y/float(size.x),size.z/float(size.x));
	fs.read( (char*)arr, size.x*size.y*size.z*sizeof(short));
	fs.close();
	iso->size=size;
	iso->UploadFieldData(arr,size,type,scale);				//загрузка скал€рных данных в GPU
	iso->SetBoundingBox(vec3(0),scale);
	delete[]arr;
}

// направление в точку на экране с координатами x,y
vec3 GetNav(int x,int y)
{
	vec3 ll=cam.GetLeft()*((x-width/2)/float(height));
	vec3 uu=cam.GetTop()*((y-height/2)/float(height));
	
	
	return cam.GetNav()-(uu-ll)*(2*TAN_22_5);

}

// результат перемещени€ точки dot в точку с экранными координатами x,y

vec3 MoveDot(int x,int y,vec3 dot)
{
	vec3 n = cam.GetNav();
	float mx = max(abs(n.x),max(abs(n.y),abs(n.z)));
	flat f(dot-cam.GetPosition(),vec3(mx==abs(n.x),mx==abs(n.y),mx==abs(n.z)));
	return vec3::flat_cross_line(f,GetNav(x,y))+cam.GetPosition();
}

//обработчик движени€ мыши
void MouseMove ( int x, int y )
{
	mouse.Move(x,y);
	cam.MouseMove(x,y);

	if(keyboard['1']) 
	{
		iso->SetLevel(iso->GetMinLevel()+mouse.dy*0.0003f);
		printf("%f\n",iso->GetMinLevel());
	}

	if(keyboard['3']) iso->SetBoundingBox(MoveDot(x,y,iso->GetMinBox()),iso->GetMaxBox());
	if(keyboard['4']) iso->SetBoundingBox(iso->GetMinBox(),MoveDot(x,y,iso->GetMaxBox()));

	if(keyboard['5']) cam.eye_distance+=mouse.dy*0.001f;
	

}

//обработчик событи€, св€занного с кнопками мыши
void MouseButton ( int button, int state )
{
	mouse.Button(button,state);
	cam.MouseButton(button,state);
}

//обработчик клавиатуры
void KeyButton ( int key, int state )
{
	keyboard[key]=state;
	cam.KeyButton(key,state);

	
	if(state)
	{
		if(key=='S')
			SetStereoMode((stereo_on+1)%4);

	}
	
}

//обработчик вращени€ колЄсика мыши
void MouseWheel( int val )
{
	static int oval = val;
	mouse.Wheel(val-oval);
	cam.MouseWheel(val-oval);
	oval = val;
}

void SetupGL()
{
	#ifdef USE_GLEW
		glewInit();
	#endif
	glClearColor(0,0,0,0);
	//glShadeModel(GL_FLAT);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	
	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void initIVP()
{
	cam.SetupProjection(45, 0.3f, 60.0f, 0, 0, width, height);


	SetupGL();
	
	iso = new IsoViewer();						//в конструкторе загружаетс€ и компиллируетс€ шейдер дл€ трассировки луча
	LoadDataset();	

	iso->SetLevel(0.008f);
	cam.SetCenter(vec3(0.5f));
	cam.SetDistance(1.5f);

	printf("-----\n%s\n-----\n",output::out_string.c_str());	//вывод результата компилл€ции шейдера на консоль
	output::out_string.clear();

}

int main ( void )
{
	glfwInit ( );
	printf("'S' - change stereo mode\nUse mouse to translate/rotate/scale scene \nWhen moving mouse:\n");
	printf("	'1' - change iso-value\n");
	printf("	'3' - change BoundingBox point1\n");
	printf("	'4' - change BoundingBox point2\n");
	printf("	'5' - change distance between eyes\n");

	int choice = 0;
	int _width, _height, mode = GLFW_WINDOW;

	//---------------------------------------------------------------------------------------------
	if ( choice == 'Y' || choice == 'y' )
	{
		GLFWvidmode vidmode;
		glfwGetDesktopMode ( &vidmode );
		width = vidmode.Width;
		height = vidmode.Height;
		mode = GLFW_FULLSCREEN;
	}
    if( !glfwOpenWindow ( width, height, 8, 8, 8, 8, 8, 8, mode ) )
    {
        glfwTerminate ( ); exit ( 0 );
	}
    glfwSwapInterval ( 0 );

	glfwSetMousePosCallback ( MouseMove );
	glfwSetMouseButtonCallback ( MouseButton );
	glfwSetKeyCallback ( KeyButton );
	glfwSetMouseWheelCallback ( MouseWheel );

	//---------------------------------------------------------------------------------------------

	

	bool running = GL_TRUE;

	int frames = 0;

	char caption [100];
	initIVP();
	double start = glfwGetTime ( );
    while ( running )
    {

        double time = glfwGetTime ( );
        if ( ( time - start ) > 1.0 || frames == 0 )
        {
            double fps = frames / ( time - start );
            sprintf_s ( caption, "%.1f FPS", fps );
            glfwSetWindowTitle ( caption );
            start = time;
            frames = 0;
        }
        frames++;

		//-----------------------------------------------------------------------------------------

        glfwGetWindowSize ( &_width, &_height );
        _height = max ( _height, 1 );
		if(_height!=height || _width!=width)
		{
			width=_width;
			height=_height;
			cam.SetupProjection(45,0.3f,60.0f,0,0,width,height);
			if(stereo_on==3)InitInterlace();

		}

		FullDraw();

        glfwSwapBuffers ( );

		//-----------------------------------------------------------------------------------------
		
		running = !glfwGetKey ( GLFW_KEY_ESC ) && glfwGetWindowParam ( GLFW_OPENED );
	}

    glfwTerminate ( ); 
	
	delete iso;

	exit ( 0 );
}