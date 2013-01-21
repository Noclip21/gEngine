#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include <SDL.h>

#include "Utils.h"
#include "Object.h"
#include "Screen.h"
#include "Event.h"

using namespace std;


#include "prologue.h"
class G_DECLSPEC Main
{
public:

	static bool	RUNNING;

	static int		framerate();
	static int		fps();
	static double	time();
	static double	speedFactor();


	static Screen* root();
	
	static int width();
	static int height();


	Main(int	w,
		 int	h,
		 int	framerate,
		 bool	frame,
		 char	*appName);
	~Main();
	
	
	int display();

private:

	static int		_FRAMERATE;
	static int		_FPS;

	static double	_TIME;
	static double	_SPEEDFACTOR;


	char			*_appName;
	bool			_frame;
	static Screen	*_root;

	static int _w;
	static int _h;

	bool init();
	void quit();
};
#include "epilogue.h"

#endif