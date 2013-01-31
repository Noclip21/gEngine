#include "Event.h"
#include <Windows.h>
using namespace utils;



vector<SDLKey>	Event::keys;
vector2			Event::mouse;


bool Event::keyDown(int key)
{
	SDLKey keyObj = (SDLKey)key;
	return (findObject(keyObj,keys) >= 0);
}



Event::Event()
{
	addListener([this](){Event_display();});
}
Event::~Event()
{
	// code
}



void Event::Event_display()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
		switch(e.type)
		{
			/*case():
			{
				break;
			}*/
			// key
				case(SDL_KEYDOWN):
				{
					if(findObject(e.key.keysym.sym,keys) < 0)
						keys.push_back(e.key.keysym.sym);
					break;
				}
				case(SDL_KEYUP):
				{
					removeObject(e.key.keysym.sym,keys);
					break;
				}

			// mouse
				case(SDL_MOUSEMOTION):
				{
					mouse.x = e.motion.x;
					mouse.y = e.motion.y;
					break;
				}
		}
}