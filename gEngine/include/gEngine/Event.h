#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Object.h"
#include "Utils.h"

using namespace std;
using namespace utils;


#include "prologue.h"
class G_DECLSPEC Event : public Object
{
public:
	
	static vector2 mouse;

	static bool keyDown(int key);


	/*bool MouseButtonDown();
	bool MouseButtonUp();

	bool MouseMotion();*/

	Event();
	~Event();

private:

	static vector<SDLKey>	keys;

	void Event_display();
};
#include "epilogue.h"

#endif