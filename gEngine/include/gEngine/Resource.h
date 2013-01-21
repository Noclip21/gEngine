#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>
#include <iostream>

#include <SDL.h>

#include <HLLib.h>
#include <Wrapper.h>

#include "Object.h"

using namespace std;


#include "prologue.h"
class G_DECLSPEC Resource 
{
public:

	static bool			cache(string package);
	static void			dump(string package);
	static SDL_RWops*	fetch(string file);

private:

	static bool hlInitialized;
	
	struct sFile
	{
		string	name;
		int		size;
		char	*data;
	};
	struct sPackage
	{
		string			name;
		vector<sFile*>	files;
	};

	static vector<sPackage*> packages;
};
#include "epilogue.h"

#endif