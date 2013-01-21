#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Object.h"
#include "Utils.h"

using namespace std;


#include "prologue.h"
class G_DECLSPEC Event : public Object
{
public:

	static bool keyDown(int key);

	static int mouseX();
	static int mouseY();

	/*bool MouseButtonDown();
	bool MouseButtonUp();

	bool MouseMotion();*/

	Event();
	~Event();

	static void all();

private:

	static vector<SDLKey>	keys;
	static pair<int,int>	mousePos;

	void Event_display();
};
#include "epilogue.h"

#endif