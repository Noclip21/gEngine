#include "World.h"


World::World(Surface *parent) : Screen(parent,0,0,Main::width(),Main::height())
{
	Resource::cache("../res/res.wad");

	Surface *Wscr = new Surface(this,0,0);
	//Surface *Wplr = new Surface(screen,0,0);

	new Sprite("write256.bmp",Wscr);
	player = new Player(Wscr,0,0);
	screen = new Screen(Wscr,0,0,Main::width()/2,Main::height()/2);
	screen->origin(Main::width()/4,Main::height()/4);

	cam(Wscr,screen);
	//screen->cam(Wplr,player);

	addListener([this](){World_display();});
}
World::~World()
{
	Resource::dump("../res/res.wad");
}



void World::World_display()
{
	if(Event::keyDown(SDLK_TAB))
	{
		if(cam()->target() == player)
			cam()->target(screen);
		else
			cam()->target(player);
	}

	if(Event::keyDown(SDLK_ESCAPE))
		Main::RUNNING = false;
}