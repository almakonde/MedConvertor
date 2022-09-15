#ifndef MOUSE_H
#define MOUSE_H

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

#endif