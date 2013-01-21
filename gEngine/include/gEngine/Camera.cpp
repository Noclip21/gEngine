#include"Camera.h"



vector<Camera*> Camera::objects;


Surface* Camera::target()				{ return _target;	}
void	 Camera::target(Surface *target){ _target = target; }
void	Camera::target(double posx,double posy)
{
	_target = NULL;
	_x = posx;
	_y = posy;
}



Camera::Camera(int screenWidth,
			   int screenHeight,
			   Surface *wrapper)
{
	objects.push_back(this);

	delay = 0.1f;

	_width =	screenWidth;
	_height =	screenHeight;
	_wrapper =	wrapper;
	_x = _y =	0;

	addListener([this](){Camera_display();});
}

Camera::~Camera()
{
	_wrapper =	NULL;
	_target =	NULL;
	Utils::removeObject(*this,objects);
}



void Camera::Camera_display()
{
	if(alive(_wrapper))
	{
		double x,y;
		if(alive(_target))
		{
			_x = x = _target->x;
			_y = y = _target->y;
		}else{
			x = _x;
			y = _y;
		}

		_wrapper->avelx = (_width/2 - x - _wrapper->x)*delay;
		_wrapper->avely = (_height/2 - y - _wrapper->y)*delay;
	}
}