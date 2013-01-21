#include "Surface.h"
#include "Main.h"


vector<Surface*> Surface::objects;


pair<double,double>	Surface::pos()		 { return make_pair(x,y);							}
pair<double,double>	Surface::oldPos()	 { return make_pair(_oldx,_oldy);					}
double				Surface::oldx()		 { return _oldx;									}
double				Surface::oldy()		 { return _oldy;									}
pair<double,double>	Surface::avel()		 { return make_pair(avelx,avely);					}
pair<double,double> Surface::origin()	 { return make_pair(ox,oy);							}
SDL_Surface*		Surface::getSurface(){ return _surface;									}
Surface*			Surface::parent()	 { return _parent;									}
int					Surface::width()	 { if(_surface) return _surface->w; else return 0;	}
int					Surface::height()	 { if(_surface) return _surface->h; else return 0;	}

void Surface::pos	(double posx,double posy)	{ x = posx; y = posy;		}
void Surface::avel	(double ax,double ay)		{ avelx = ax; avely = ay;	}
void Surface::origin(double posx,double posy)	{ ox = posx; oy = posy;		}
double Surface::globalX()
{
	if(_parent) return x + _parent->globalX();
	else		return x;
}
double Surface::globalY()
{
	if(_parent) return y + _parent->globalY();
	else		return y;
}
double Surface::globalOriginX()
{
	if(_parent) return ox + _parent->globalOriginX();
	else		return ox;
}
double Surface::globalOriginY()
{
	if(_parent) return oy + _parent->globalOriginY();
	else		return oy;
}
void Surface::setSurface(SDL_Surface *surface)
{
	_surface = surface;
}
void Surface::parent(Surface *parent)
{
	if(_parent) _parent->removeChild(this);
	if(parent)	_parent->addChild(this);
}



Surface::Surface(Surface *parent,
				 double	  posx,
				 double	  posy)
{
	objects.push_back(this);

	x =		posx;
	y =		posy;
	avelx =	0;
	avely =	0;
	ox =	0;
	oy =	0;
	
	_surface =	NULL;
	_parent =	NULL;

	if(parent) parent->addChild(this);

	addListener([this](){Surface_display();});
}
Surface::~Surface()
{
	while(children.size() > 0) delete children[0];
	SDL_FreeSurface(_surface);
	_surface = NULL;

	Utils::removeObject(*this,objects);
	if(alive(_parent)) Utils::removeObject(*this,_parent->children);
}



void Surface::addChild(Surface *child)
{
	if(alive(child))
	{
		children.push_back(child);
		child->_parent = this;
	}
}
void Surface::removeChild(Surface *child)
{
	if(alive(child))
	{
		Utils::removeObject(*child,children);
		child->_parent = NULL;
	}
} 
void Surface::blint(Surface *surface)
{
	if(alive(surface) && _surface)
		if(surface->getSurface())
		{
			SDL_Rect r;
			r.x = (Sint16)(surface->globalX() - surface->globalOriginX());
			r.y = (Sint16)(surface->globalY() - surface->globalOriginY());
			SDL_BlitSurface(surface->getSurface(),NULL,_surface,&r);
		}
}



void Surface::Surface_display()
{
	_oldx = x;
	_oldy = y;

	double coef = Main::speedFactor()*Main::time();

	x += avelx*coef;
	y += avely*coef;
}
