#ifndef WORLD_H
#define WORLD_H

#include <gCore.h>


class World : public Screen
{
public:

	World(Surface *parent);
	~World();

private:
	void World_display();
};

#endif;