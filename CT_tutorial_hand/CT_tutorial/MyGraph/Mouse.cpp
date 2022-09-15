

#include "Mouse.h"

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
