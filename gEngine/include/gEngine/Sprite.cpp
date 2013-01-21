#include "Sprite.h"



vector<Sprite*> Sprite::objects;


Sprite::Sprite( string	 src =		NULL,
				Surface	*parent =	NULL,
				double	 posx =		0,
				double	 posy =		0) : Surface(parent,posx,posy)
{
	objects.push_back(this);

	setSurface(loadBmp(src));
	
	addListener([this](){Sprite_display();});
}

Sprite::~Sprite()
{
	Utils::removeObject(*this,objects);
}



SDL_Surface* Sprite::loadBmp(string src)
{
	if(src.size() > 0)
	{
		SDL_RWops *data = Resource::fetch(src);
		if(data)
		{
			SDL_Surface *temp = SDL_LoadBMP_RW(data,0);
			if(temp)
			{
				SDL_LockSurface(temp);

				Uint8 keyRed8	= temp->format->palette->colors[255].r;
				Uint8 keyGreen8	= temp->format->palette->colors[255].g;
				Uint8 keyBlue8	= temp->format->palette->colors[255].b;

				SDL_UnlockSurface(temp);

				
				int mode = 0;
				if(src[0] == '{')
					mode = SPRITE_DECAL;
				else
					if((keyRed8 + keyGreen8 + keyBlue8) == 255)
							mode = SPRITE_TRANSC;
					else
							mode = SPRITE_OPAQUE;
				
				switch(mode)
				{
					case SPRITE_OPAQUE:
					{
						SDL_Surface *formated = SDL_DisplayFormat(temp);
						SDL_FreeSurface(temp);
						return formated;
					}

					case SPRITE_TRANSC:
					{
						SDL_SetColorKey(temp,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(temp->format,keyRed8,keyGreen8,keyBlue8));
						SDL_Surface *formated = SDL_DisplayFormat(temp);
						SDL_FreeSurface(temp);
						return formated;
					}
					case SPRITE_DECAL:
					{
						SDL_Surface *formated = SDL_DisplayFormatAlpha(temp);
						SDL_FreeSurface(temp);

						SDL_LockSurface(formated);
			
						int w = formated->w;
						int h = formated->h;
						Uint32 *pixels = (Uint32*)formated->pixels;

						Uint32 keyColor32 = SDL_MapRGB(formated->format,keyRed8,keyGreen8,keyBlue8);
							Uint8 keyRed32 =	(keyColor32 & 0x00ff0000) >> 16;
							Uint8 keyGreen32 =	(keyColor32 & 0x0000ff00) >> 8;
							Uint8 keyBlue32 =	 keyColor32 & 0x000000ff;

						for(int x=0; x<w; ++x)
							for(int y=0; y<h; ++y)
							{
								Uint32 *pixel = &pixels[(y*w)+x];

								Uint8 alpha =	(*pixel & 0xff000000) >> 24;
								Uint8 red =		(*pixel & 0x00ff0000) >> 16;
								Uint8 green =	(*pixel & 0x0000ff00) >> 8;
								Uint8 blue =	 *pixel & 0x000000ff;
					
								Uint8 grayscale = (Uint8)((red+green+blue)/3);

								*pixel = SDL_MapRGBA(formated->format,
									min(grayscale,keyRed32),
									min(grayscale,keyGreen32),
									min(grayscale,keyBlue32),
									255-grayscale);
							}

						SDL_UnlockSurface(formated);
						return formated;
					}
				}
			}
		}
	}
	return NULL;
}



void Sprite::Sprite_display()
{
	// code
}