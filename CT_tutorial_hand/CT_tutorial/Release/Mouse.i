#line 1 "MyGraph\\Mouse.cpp"


#line 1 "d:\\projects\\vr\\dvr up1\\ct_tutorial_hand\\ct_tutorial\\mygraph\\Mouse.h"



struct Mouse
{
	void Move ( int x, int y );
	void Button ( int button, int state );
	void Wheel( int val );

	int oldx,oldy;
	int dx,dy;
	int dw;
	char btn;

};

#line 18 "d:\\projects\\vr\\dvr up1\\ct_tutorial_hand\\ct_tutorial\\mygraph\\Mouse.h"
#line 4 "MyGraph\\Mouse.cpp"

void Mouse::Move ( int x, int y )
{
	dx = x-oldx;
	dy = y-oldy;
	oldx=x;
	oldy=y;
}
		
void Mouse::Button ( int button, int state )
{
	if(state) 
		btn |= (1<<button);
	else
		btn &= ~(1<<button);

}

void Mouse::Wheel( int val )
{
	dw=val;
	
}
