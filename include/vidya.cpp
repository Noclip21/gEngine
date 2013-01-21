// #include <Windows.h>
#include <SDL.h>
#include <gCore.h>

int main(int argc,char *argv[])
{
	Main video(800,600,60,true,"VIDYA!");
		video.display();
	return 0;
}