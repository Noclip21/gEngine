gEngine
=======


##About
gEngine is a 2D game engine written in c++.

Developed by myself for practice and study purposes at Federal University of Ceara.


##Example

```C++
#include <gCore.h>

int main(int argc,char *argv[])
{
	int width =		800;
	int height =	600;
	bool border =	true;
	char *name =	"Hello world";

	// Create new window
	Main vidya(width,height,border,name);

	// Precache resource pack
	Resource::cache("foo.wad");

	char	*img =		"bar.bmp";		// Image in resource pack
	Surface	*parent =	Main::root();	// Root parent
	double	posx =		0;
	double	posy =		0;

	// Create sprite
	Sprite	spr(img,parent,posx,posy);
			spr.addListener([obj]()		// Runs for each new frame
			{
				obj.rotation += 1;
				if(Event::keyDown(SDLK_ESCAPE)) // Esc pressed. Exit demo.
					Main::RUNNING = false;
			});

	// Free memory
	Resource::dump("foo.wad");

	retun 0;
}
```


##Instalation

###Binaries
- Get the .dlls and .libs from *gEngine/lib/*
- get the .hs from *gEngine/include/*

###Source
- Get the .hs amd .cpps from *gEngine/include/gEngine/*


**Compiling needs additional libraries**


####HLLib
- Get the .dlls and .libs from *gEngine/lib/*
- Get the .hs from *gEngine/include/hllib/*

####SDL
- Get the .dlls and .libs from *gEngine/lib/*
- Get the .hs from *gEngine/include/sdl/*

Projects included (Visual studio 2012)
- Engine development: *gEngine/gEngine.sln*
- Example: Vidya.sln

--
This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar. See the COPYING file for more details.
