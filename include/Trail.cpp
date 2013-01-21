#include "Trail.h"

Trail::Trail(Surface *target) : Animation(target->parent(),target->x,target->y)
{
	origin(64,64);

	target->parent()->swapDepths(depth(),target->depth());

	char *anim[] =
	{
		"dummy128.bmp",
		"dummy64.bmp",
		"dummy32.bmp",
		"dummy16.bmp"
	};
				
	addAnimation("blink",250,anim,4);

	callback([this]()
	{
		kill();
	});
}
Trail::~Trail()
{
}