#include <gCore.h>
#include <Windows.h>
#include <iostream>
using namespace std;


int main(int argc,char *argv[])
{
	Main video(800,600,60,true,"VIDYA!");

	Resource::cache("../res/pack.pak");
	//Audio *audio = new Audio("hit.wav");
	Screen *scr = new Screen(NULL,0,0,500,500);
			scr->addListener([scr]()
			{
				if(Event::keyDown(SDLK_LCTRL))
				{
					double factor = 1;
					if(Event::keyDown(SDLK_UP)) scr->pos.y -= factor;
					if(Event::keyDown(SDLK_DOWN)) scr->pos.y += factor;
					if(Event::keyDown(SDLK_LEFT)) scr->pos.x -= factor;
					if(Event::keyDown(SDLK_RIGHT)) scr->pos.x += factor;

					cout << "Screen x= " << scr->pos.x << " y= " << scr->pos.y << endl;
				}
			});
	Sprite *rainbow = new Sprite("rainbow.bmp",scr);
	Screen *scr2 = new Screen(scr,20,20,100,100);
	Sprite *dummy = new Sprite("dummy128.bmp",scr2);
			dummy->addListener([dummy]()
			{
				if(Event::keyDown(SDLK_LSHIFT))
				{
					double factor = 1;
					if(Event::keyDown(SDLK_UP)) dummy->pos.y -= factor;
					if(Event::keyDown(SDLK_DOWN)) dummy->pos.y += factor;
					if(Event::keyDown(SDLK_LEFT)) dummy->pos.x -= factor;
					if(Event::keyDown(SDLK_RIGHT)) dummy->pos.x += factor;

					cout << "Sprite x= " << dummy->pos.x << " y= " << dummy->pos.y << endl;
				}

				/*float factor = 0.01;
				if(Event::keyDown(SDLK_UP))
				{
					if(Event::keyDown(SDLK_r)) obj->red		+= factor;
					if(Event::keyDown(SDLK_g)) obj->green	+= factor;
					if(Event::keyDown(SDLK_b)) obj->blue	+= factor;
					if(Event::keyDown(SDLK_a)) obj->alpha	+= factor;

					cout << "R: " << obj->red << " G: " << obj->green << " B: " << obj->blue << endl;
				}
				if(Event::keyDown(SDLK_DOWN))
				{
					if(Event::keyDown(SDLK_r)) obj->red		-= factor;
					if(Event::keyDown(SDLK_g)) obj->green	-= factor;
					if(Event::keyDown(SDLK_b)) obj->blue	-= factor;
					if(Event::keyDown(SDLK_a)) obj->alpha	-= factor;

					cout << "R: " << obj->red << " G: " << obj->green << " B: " << obj->blue << endl;
				}*/
			});

	/*		obj->origin2d(16,16);
			obj->avel.x = 5;
			obj->addListener([obj,audio]()
			{
				if(obj->pos.x + obj->avel.x > Main::width())	// Right
				{
					obj->avel.x *=	-1;
					obj->pos.x =	Main::width();
					obj->avelrot =	obj->avel.y;

					audio->play();
				}
				if(obj->pos.x + obj->avel.x < 0)				// Left
				{
					obj->avel.x *=	-1;
					obj->pos.x =	0;
					obj->avelrot =	-obj->avel.y;

					audio->play();
				}
				if(obj->pos.y + obj->avel.y > Main::height())	// Botton
				{
					obj->avel.y *=	-1;
					obj->pos.y =	Main::height();
					obj->avelrot =	obj->avel.x;

					audio->play();
				}else
					obj->avel.y += 1;
				if(obj->pos.y + obj->avel.y < 0)				// Top
				{
					obj->avel.y *=	-1;
					obj->pos.y =	0;
					obj->avelrot =	-obj->avel.x;

					audio->play();
				}

				if(Event::keyDown(SDLK_ESCAPE))
					Main::RUNNING = false;
			});*/

	video.display();
	return 0;
}