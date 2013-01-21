#include "Player.h"


Player::Player(Surface *parent,double posx,double posy) : Animation(parent,posx,posy)
{
	origin(64,64);

	qdist.first =	x;
	qdist.second =	y;
	vel =			1;
	maxVel =		5;

	char *amin[] =
	{
		"logo128.bmp",
		"logoi128.bmp"
	};

	addAnimation("car",250,amin,2);

	addListener([this](){Player_display();});
}
Player::~Player()
{
}


void Player::Player_display()
{
	/*if(Utils::dist(pos(),qdist) > 100)
	{
		qdist.first =	x;
		qdist.second =	y;
		new Trail(this);
	}*/


	if(Event::keyDown(SDLK_a) || Event::keyDown(SDLK_d))
	{
		if(Event::keyDown(SDLK_a))
			avelx -= vel;
		if(Event::keyDown(SDLK_d))
			avelx += vel;
	}else
		avelx *= 0.9;

	if(Event::keyDown(SDLK_w) || Event::keyDown(SDLK_s))
	{
		if(Event::keyDown(SDLK_w))
			avely -= vel;
		if(Event::keyDown(SDLK_s))
			avely += vel;
	}else
		avely *= 0.9;

	if(abs(avelx) > maxVel)
		if(avelx > 0) avelx = maxVel;
		else		  avelx = -maxVel;

	if(abs(avely)> maxVel)
		if(avely > 0) avely = maxVel;
		else		  avely = -maxVel;
}