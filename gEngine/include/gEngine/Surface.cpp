#include "Surface.h"
#include "Main.h"


vector<Surface*> Surface::objects;


pair<double,double>	Surface::pos()		 { return make_pair(x,y);			}
pair<double,double>	Surface::oldPos()	 { return make_pair(_oldx,_oldy);	}
double				Surface::oldx()		 { return _oldx;					}
double				Surface::oldy()		 { return _oldy;					}
pair<double,double>	Surface::avel()		 { return make_pair(avelx,avely);	}
pair<double,double> Surface::origin()	 { return make_pair(ox,oy);			}
Surface*			Surface::parent()	 { return _parent;					}
int					Surface::depth()	 { return _depth;					}
int					Surface::width()	 { return _width;					}
int					Surface::height()	 { return _height;					}
pair<double,double> Surface::scale()	 { return make_pair(scaleX,scaleY); }

int	Surface::mouseX()
{
	return Event::mouseX() - globalX();
}
int	Surface::mouseY()
{
	return Event::mouseY() - globalY();
}
pair<double,double> Surface::mouse()
{
	return make_pair(mouseX(),mouseY());
}

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
double Surface::globalRotation()
{
	if(_parent) return rotation + _parent->globalRotation();
	else		return rotation;
}
void Surface::parent(Surface *parent)
{
	if(_parent) _parent->removeChild(this);
	if(parent)	_parent->addChild(this);
}
void Surface::scale(double sx, double sy)
{
	scaleX = sx;
	scaleY = sy;
}



Surface::Surface(Surface *parent,
				 double	  posx,
				 double	  posy)
{
	objects.push_back(this);
	
	x =			posx;
	y =			posy;
	avelx =		0;
	avely =		0;
	ox =		0;
	oy =		0;
	scaleX =	1;
	scaleY =	1;
	rotation =	0;
	
	_depth =	-1;
	_parent =	NULL;
	_width =	0;
	_height =	0;
	_oldx =		0;
	_oldy =		0;


	if(parent) parent->addChild(this);

	addListener([this](){Surface_display();});
}
Surface::~Surface()
{
	while(children.size() > 0) delete children[0];

	if(alive(_parent))
	{
		Utils::removeObject(*this,_parent->children);
		for(size_t i=_depth; i<_parent->children.size(); ++i)
			_parent->children[i]->_depth = _depth;
	}

	Utils::removeObject(*this,objects);
}



void Surface::swapDepths(int depth1,int depth2)
{
	if(children.size() > 1)
	{
		if( (depth1 >= 0 && depth2 < children.size()) &&
			(depth1 >= 0 && depth2 < children.size()) &&
			(depth1 != depth2))
		{
			children[depth1]->_depth = depth2;
			children[depth2]->_depth = depth2;

			Surface *temp = children[depth1];
			children[depth1] = children[depth2];
			children[depth2] = temp;
		}
	}
}
void Surface::addChild(Surface *child)
{
	if(alive(child))
	{
		child->_depth = children.size();
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
		child->_depth = -1;
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
