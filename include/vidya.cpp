#include <gCore.h>
#include <Windows.h>
#include <iostream>
using namespace std;


int main(int argc,char *argv[])
{
	Main video(800,600,60,true,"VIDYA!");

	Resource::cache("../res/pack.pak");

	Object *obj = new Object();
			obj->addListener([obj]()
			{
				if(Event::keyDown(SDLK_ESCAPE))
					Main::RUNNING = false;
			});
	Screen *scr = new Screen(NULL,0,0,800,600);
		Text *text = new Text("Hello World!",scr,100,100);
		Text *fps = new Text("---",scr);

	text->addListener([text]()
	{
		if(Event::keyDown(SDLK_1)) text->text("Text 1");
		if(Event::keyDown(SDLK_2)) text->text("Text 2");
		if(Event::keyDown(SDLK_3)) text->text("Text 3");

		if(Event::keyDown(SDLK_r)) text->textColor(255,0,0);
		if(Event::keyDown(SDLK_g)) text->textColor(0,255,0);
		if(Event::keyDown(SDLK_b)) text->textColor(0,0,255);

		if(Event::keyDown(SDLK_UP))		text->pos.y -= 1;
		if(Event::keyDown(SDLK_DOWN))	text->pos.y += 1;
		if(Event::keyDown(SDLK_LEFT))	text->pos.x -= 1;
		if(Event::keyDown(SDLK_RIGHT))	text->pos.x += 1;

		if(Event::keyDown(SDLK_LSHIFT))	text->textSize(text->textSize()+1);
		if(Event::keyDown(SDLK_LCTRL))	text->textSize(text->textSize()-1);


	});
	fps->addListener([fps,text]()
	{
		fps->text(toStringi(Main::fps()) +" FPS   " +
							" posx: " + toStringi(text->pos.x) +
							" posy: " + toStringi(text->pos.y) +
							" size: " + toStringi(text->textSize()));
	});

	video.display();
	return 0;
}