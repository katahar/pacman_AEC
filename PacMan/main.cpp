// this runs the overall PacMan gameW
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fssimplewindow.h>
#include "PC_PacMan.h"

class ApplicationMain
{
protected:
	bool end_term = false;

public:
	// ApplicationMain();
	bool MustTerminate(void) const;
	void RunOneStep(void);
	void Draw(void) const;

	PC_PacMan pman; 
};

// ApplicationMain::ApplicationMain()
// {
// 	pman();
// }
bool ApplicationMain::MustTerminate(void) const
{
	// fill in
	return end_term;
}
void ApplicationMain::RunOneStep(void)
{
	FsPollDevice();
	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		end_term = true ;
	}
	else if(FSKEY_T==key)
	{
		// fill in
	}
    else if(FSKEY_V==key)
	{
		// fill in
	}
	else if(FSKEY_SPACE==key)
	{
		
	}

	// std::cout << pman.getScore();

	// fill in
}
void ApplicationMain::Draw(void) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// fill in
	FsSwapBuffers();
}


int main(void)
{
	FsOpenWindow(0,0,224,228,1);

	// windowWid = 672, windowHei = 900; Map starts from Y = 78 (78 pixels down from top).
	// BlockWid = 24 x 24 

	ApplicationMain app;
	while(true!=app.MustTerminate())
	{
		app.RunOneStep();
		app.Draw();
	}
	return 0;
}
