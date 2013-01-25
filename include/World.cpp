#include "World.h"


World::World(Surface *parent) : Screen(parent,0,0,Main::width(),Main::height())
{
	Resource::cache("../res/res.wad");

	srand(time(NULL));
	for(size_t i=0; i<20; ++i)
	{
		Sprite *obj = new Sprite("dummy64.bmp",Main::root());
				obj->x = rand()%Main::width();
				obj->y = rand()%Main::height();
				obj->avelx = (rand()%60)/10.0f - 3; 
				obj->addListener([obj]()
				{
					obj->avely += 1;
					if(obj->x + obj->avelx > Main::width())
					{
						obj->avelx *= -1;
						obj->x = Main::width();
					}
					if(obj->x + obj->avelx < 0)
					{
						obj->avelx *= -1;
						obj->x = 0;
					}
					if(obj->y + obj->avely > Main::height())
					{
						obj->avely *= -1;
						obj->y = Main::height();
					}
					if(obj->y + obj->avely < 0)
					{
						obj->avely *= -0.999;
						obj->y = 0;
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