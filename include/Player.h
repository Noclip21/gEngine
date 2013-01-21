#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <gCore.h>
#include "Trail.h"

using namespace std;


class Player : public Animation
{
public:

	Player(Surface *parent,double posx, double posy);
	~Player();

private:

	pair<double,double> qdist;

	int vel;
	int maxVel;

	void Player_display();
};

#endif