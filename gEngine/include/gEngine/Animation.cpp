#include "Animation.h"



vector<Animation*> Animation::objects;


void Animation::play()
{
	_pause = false;
}
void Animation::pause()
{
	_pause = true;
} 
void Animation::play(int frame)
{
	_pause = false;
	_frame = frame;
}
void Animation::pause(int frame)
{
	_pause = true;
	_frame = frame;
}
void Animation::stop()
{
	_pause = true;
	_frame = 0;
}
int Animation::numFrames()
{
	if(_currentAnim)
		return _currentAnim->surfaces.size();
	else
		return 0;
}



Animation::Animation(	Surface *parent,
						double posx,
						double posy) : Sprite(NULL,parent,posx,posy)
{
	objects.push_back(this);

	_currentAnim = NULL;
	_timer = 0;
	_frame = 0;
	_pause = false;
	_callback = [](){};

	addListener([this](){Animation_display();});
}

Animation::~Animation()
{
	Utils::removeObject(*this,objects);
}



void Animation::setAnimation(string name)
{
	for(size_t i=0; i<_animations.size(); ++i)
		if(name.compare(_animations[i]->name) == 0)
		{
			_frame = 0;
			_currentAnim = _animations[i];
		}
}

void Animation::addAnimation(string	name,
							 int	time,
							 string	sprites,
							 int	len)
{
	if(	name.size() > 0 &&
		time > 0		&&
		len > 0)
	{
		animPack *anim = new animPack;
		anim->name = name;
		anim->time = time;
		for(int i=0; i<len; ++i)
		{
			SDL_Surface *temp = loadBmp(sprites);
			if(temp) anim->surfaces.push_back(temp);
		}
		_animations.push_back(anim);

		_frame = 0;
		_currentAnim = anim;
	}
}

void Animation::callback(function<void ()> f)
{
	_callback = f;
}

void Animation::Animation_display()
{
	if(_currentAnim)
	{
		if(SDL_GetTicks() - _timer >= _currentAnim->time)
		{
			_timer = SDL_GetTicks();

			if(!_pause) _frame++;

			if(_frame >= 0 && _frame <= _currentAnim->surfaces.size())
			{
				setSurface(_currentAnim->surfaces[_frame-1]);
				if(_frame == _currentAnim->surfaces.size())
					_callback();
			}else
				_frame = 0;
		}
	}
}