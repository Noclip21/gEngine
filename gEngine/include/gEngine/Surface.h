#ifndef Surface_H
#define Surface_H

#include <vector>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <SDL.h>

#include "Utils.h"
#include "Object.h"


#include "prologue.h"
class G_DECLSPEC Surface : public Object
{
public:

	static vector<Surface*> objects;

	vector<Surface*> children;
	
	double x;
	double y;
	double avelx;
	double avely;
	double ox;
	double oy;
	double scaleX;
	double scaleY;
	double rotation;
	
	
	pair<double,double>	pos();
	pair<double,double>	oldPos();
	double				oldx();
	double				oldy();
	pair<double,double>	avel();
	pair<double,double> origin();
	double				globalX();
	double				globalY();
	double				globalOriginX();
	double				globalOriginY();
	double				globalRotation();
	int					depth();
	Surface*			parent();
	int					width();
	int					height();
	pair<double,double> scale();

	int					mouseX();
	int					mouseY();
	pair<double,double> mouse();
	
	void pos		(double posx,double posy);
	void avel		(double ax,double ay);
	void origin		(double posx,double posy);
	void parent		(Surface *parent);
	void scale		(double sx,double sy);


	Surface(Surface *parent =	NULL,
			double	posx =		0,
			double	posy =		0);
	virtual ~Surface();


	void swapDepths		(int surfaceId1,int surfaceId2);
	void addChild		(Surface *child);
	void removeChild	(Surface *child);


protected:

	int _width;
	int _height;


private:

	int _depth;
	
	Surface	*_parent;

	double _oldx;
	double _oldy;

	void Surface_display();
};
#include "epilogue.h"

#endif