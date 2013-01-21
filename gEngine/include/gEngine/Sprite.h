#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

#include <SDL.h>

#include "Utils.h"
#include "Resource.h"
#include "Surface.h"


#include "prologue.h"
#define SPRITE_DECAL	0
#define SPRITE_OPAQUE	1
#define SPRITE_TRANSC	2
class G_DECLSPEC Sprite : public Surface
{
public:
	
	static vector<Sprite*> objects;


	Sprite( char	*src =		NULL,
			Surface *parent =	NULL,
			double	 posx =		0,
			double	 posy =		0);
	virtual ~Sprite();

	
	SDL_Surface* loadBmp(char *src);

private:

	void Sprite_display();
};
#include "epilogue.h"

#endif