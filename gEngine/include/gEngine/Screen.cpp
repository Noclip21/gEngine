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
	
	_width =	width;
	_height =	height;

	_cam = NULL;

	addListener([this](){Screen_display();});
}

Screen::~Screen()
{
	Utils::kill(*_cam);
	Utils::removeObject(*this,objects);
}



void Screen::blint(Sprite *sprite)
{
	if(alive(sprite))
	{
		glBindTexture(GL_TEXTURE_2D,sprite->id());
		{
			double Gx =			sprite->globalX();
			double Gy =			sprite->globalY();
			double Gox =		sprite->globalOriginX()*sprite->scaleX;
			double Goy =		sprite->globalOriginY()*sprite->scaleY;
			double Grotation =	sprite->globalRotation();
			double Swidth =		sprite->width()*sprite->scaleX;
			double Sheight =	sprite->height()*sprite->scaleY;
			
			double sn = sin(Grotation*PI/180);
			double cn = cos(Grotation*PI/180);

			double	qx = -cn*Gox+sn*Goy,				qxw = cn*(Swidth-Gox)+sn*Goy,
					qy = -sn*Gox-cn*Goy,				qyw = sn*(Swidth-Gox)-cn*Goy,

					qxh = -cn*Gox-sn*(Sheight-Goy),		qxwh = cn*(Swidth-Gox)-sn*(Sheight-Goy),
					qyh = -sn*Gox+cn*(Sheight-Goy),		qywh = sn*(Swidth-Gox)+cn*(Sheight-Goy);
			
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);	glVertex3f(Gx+qx,	Gy+qy,0);
				glTexCoord2f(1,0);	glVertex3f(Gx+qxw,	Gy+qyw,0);
				glTexCoord2f(1,1);	glVertex3f(Gx+qxwh,	Gy+qywh,0);
				glTexCoord2f(0,1);	glVertex3f(Gx+qxh,	Gy+qyh,0);
			glEnd();
		}
	}
}

void Screen::render(Surface* surface)
{
	if(alive(surface))
		for(size_t i=0; i<surface->children.size(); ++i)
		{
			render(surface->children[i]);
			if(dynamic_cast<Sprite*>(surface->children[i]))
				blint((Sprite*)surface->children[i]);
		}
}



void Screen::Screen_display()
{
	render(this);
}