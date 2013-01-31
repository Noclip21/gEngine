#include "World.h"
#include <iostream>
using namespace std;

World::World(Surface *parent) : Screen(parent,0,0,Main::width(),Main::height())
{
	Resource::cache("../res/res.wad");

	srand(time(NULL));
	for(size_t i=0; i<60; ++i)
	{
		Sprite *obj = new Sprite("dummy32.bmp",Main::root());
				obj->origin2d(16,16);
				obj->pos.x = rand()%Main::width();
				obj->pos.y = rand()%Main::height();
				obj->avel.x = (rand()%60)/10.0f - 3; 
				obj->addListener([obj]()
				{
					if(obj->pos.x + obj->avel.x > Main::width())	// Right
					{
						obj->avel.x *=	-1;
						obj->pos.x =	Main::width();
						obj->avelrot =	obj->avel.y;
					}
					if(obj->pos.x + obj->avel.x < 0)				// Left
					{
						obj->avel.x *=	-1;
						obj->pos.x =	0;
						obj->avelrot =	-obj->avel.y;
					}
					if(obj->pos.y + obj->avel.y > Main::height())	// Botton
					{
						obj->avel.y *=	-1;
						obj->pos.y =	Main::height();
						obj->avelrot =	obj->avel.x;
					}else
						obj->avel.y += 1;
					if(obj->pos.y + obj->avel.y < 0)				// Top
					{
						obj->avel.y *=	-1;
						obj->pos.y =		0;
						obj->avelrot =	-obj->avel.x;
					}
				});
	}
}
World::~World()
{
	Resource::dump("../res/res.wad");
}



void World::World_display()
{
	if(Event::keyDown(SDLK_ESCAPE))
		Main::RUNNING = false;
}