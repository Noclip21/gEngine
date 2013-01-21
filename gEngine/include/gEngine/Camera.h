#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include "Utils.h"
#include "Object.h"
#include "Surface.h"


#include "prologue.h"
class G_DECLSPEC Camera : public Object
{
public:

	static vector<Camera*> objects;


	double delay;
	
	
	void target(Surface *target);
	void target(double posx,double posy);

	
	Camera(	int		 screenWidth,
			int		 screenHeight,
			Surface *wrapper);
	~Camera();

private:

	int		 _width;
	int		 _height;
	Surface	*_wrapper;
	Surface *_target;
	double	 _x;
	double	 _y;

	void Camera_display();
};
#include "epilogue.h"

#endif