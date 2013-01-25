#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

#include "Utils.h"
#include "Surface.h"
#include "Sprite.h"
#include "Camera.h"


#include "prologue.h"
class G_DECLSPEC Screen : public Surface
{
public:

	static vector<Screen*> objects;

	
	Camera* cam();

	void cam(Surface *wrapper,Surface *target);
	void cam(Surface *wrapper,double posx,double posy);
	void camDelay(double delay);


	Screen( Surface *parent,
			double	 posx,
			double	 posy,
			int		 width,
			int		 height);

	~Screen();
	
	void blint(Sprite *sprite);
	void render(Surface *surface);

private:
	
	Camera *_cam;

	void Screen_display();
};
#include "epilogue.h"

#endif
