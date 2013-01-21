#include <gCore.h>
#include "World.h"


int main(int argc,char *argv[])
{
	Main video(800,600,60,true,"VIDYA!");
		new World(Main::root());
		video.display();
	return 0;
}