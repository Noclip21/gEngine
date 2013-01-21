#ifndef WORLD_H
#define WORLD_H

#include <gCore.h>
#include "Player.h"


class World : public Screen
{
public:

	Screen	*screen;
	Player	*player;


	World(Surface *parent);
	~World();

private:
	void World_display();
};

#endif;