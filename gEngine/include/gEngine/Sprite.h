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


	Sprite( string	 src,
			Surface *parent,
			double	 posx,
			double	 posy);
	virtual ~Sprite();

	
	SDL_Surface* loadBmp(string src);

private:

	void Sprite_display();
};
#include "epilogue.h"

#endif