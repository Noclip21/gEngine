#include "Screen.h"



vector<Screen*> Screen::objects;


Camera* Screen::cam(){ return _cam; }

void Screen::cam(Surface *wrapper,Surface *target)
{
	if(alive(wrapper) && alive(target))
	{
		if(_cam) delete _cam;
		_cam = new Camera(width(),height(),wrapper);
		_cam->target(target);
	}
}
void Screen::cam(Surface *wrapper,double posx,double posy)
{
	if(alive(wrapper))
	{
		if(_cam) delete _cam;
		_cam = new Camera(width(),height(),wrapper);
		_cam->target(posx,posy);
	}
}
void Screen::camDelay(double delay)
{
	if(_cam) _cam->delay = delay;
}



Screen::Screen(	Surface *parent,
				double	 posx,
				double	 posy,
				int		 width,
				int		 height) : Surface(parent,posx,posy)
{
	objects.push_back(this);
	
	setSurface(SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA,width,height,32,NULL,NULL,NULL,NULL));

	_cam = NULL;

	addListener([this](){Screen_display();});
}

Screen::~Screen()
{
	Utils::kill(*_cam);
	Utils::removeObject(*this,objects);
}



void Screen::blint(Surface *surface)
{
	if(alive(surface) && getSurface())
		if(surface->getSurface())
		{
			SDL_Rect r;
				r.x = (Uint16)(surface->globalX() - surface->globalOriginX() - globalX());
				r.y = (Uint16)(surface->globalY() - surface->globalOriginY() - globalY());

			SDL_BlitSurface(surface->getSurface(),NULL,getSurface(),&r);
		}
}

void Screen::render(Surface* surface)
{
	if(alive(surface))
		for(size_t i=0; i<surface->children.size(); ++i)
		{
			blint(surface->children[i]);
			if(!dynamic_cast<Screen*>(surface->children[i]))
				render(surface->children[i]);
		}
}

void Screen::Screen_display()
{
	if(getSurface())
	{
		SDL_FillRect(getSurface(),NULL,SDL_MapRGBA(getSurface()->format,0,0,0,255));
		render(this);
		SDL_Flip(getSurface());
	}
}