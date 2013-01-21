#include "Event.h"
#include <Windows.h>



vector<SDLKey>	Event::keys;
pair<int,int>	Event::mousePos;


bool Event::keyDown(int key)
{
	SDLKey keyObj = (SDLKey)key;
	return (Utils::findObject(keyObj,keys) >= 0);
}
int Event::mouseX()
{
	return mousePos.first;
}
int Event::mouseY()
{
	return mousePos.second;
}



void Event::all()
{
	cout << mousePos.first << "  " << mousePos.second << endl;
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
					if(Utils::findObject(e.key.keysym.sym,keys) < 0)
						keys.push_back(e.key.keysym.sym);
					break;
				}
				case(SDL_KEYUP):
				{
					Utils::removeObject(e.key.keysym.sym,keys);
					break;
				}

			// mouse
				case(SDL_MOUSEMOTION):
				{
					mousePos.first = e.motion.x;
					mousePos.second = e.motion.y;
					break;
				}
		}
}