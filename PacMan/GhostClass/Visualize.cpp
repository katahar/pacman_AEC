#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Ghost.h"

// void drawMapTarg(int x, int y, int pxPerBlock)
// {
// 	glColor3f(1, 0, 0);
// 	glBegin(GL_QUADS);
// 	glVertex2i( x   *pxPerBlock,  y   *pxPerBlock);
// 	glVertex2i((x+1)*pxPerBlock,  y   *pxPerBlock);
// 	glVertex2i((x+1)*pxPerBlock, (y+1)*pxPerBlock);
// 	glVertex2i( x   *pxPerBlock, (y+1)*pxPerBlock);
// 	glEnd();
// }

// void updateTarg(const Ghost &g, int &x, int &y)
// {
// 	const int* targ = g.get_target();
// 	x = targ[0];
// 	y = targ[1];
// }

int main(void)
{
// 	srand((int)time(NULL));

// 	//initialize
	Map map;
// 	Ghost ghost;
// 	int targX;
// 	int targY;
// 	updateTarg(ghost, targX, targY);

	FsOpenWindow(0,0,map.getMapWid(),map.getMapHei(),1);

// 	bool term=false;
// 	bool pause=false;
// 	while(true!=term)
// 	{
// 		FsPollDevice();
        
// 		//input
// 		int key=FsInkey();
// 		if(FSKEY_ESC==key)
// 		{
// 			term=true;
// 		}
// 		if(FSKEY_SPACE==key)
// 		{
// 			pause=!pause;
// 		}
// 		// if(FSKEY_UP==key)
// 		// {
// 		// 	ghost.set_speed(ghost.get_speed() + 0.01);
// 		// }
// 		// if(FSKEY_DOWN==key)
// 		// {
// 		// 	ghost.set_speed(ghost.get_speed() - 0.01);
// 		// }

// 		int lb,mb,rb,mx,my;
// 		auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);
// 		if(FSMOUSEEVENT_LBUTTONDOWN==evt)
// 		{
// 			ghost.update_target(map.px_to_block(mx), map.py_to_block(my));
// 			updateTarg(ghost, targX, targY);
// 			// const int* newTarg = ghost.get_target();
			
// 			// std::cout << "new target: " << newTarg[0] << ", " << newTarg[1] << std::endl; 

// 		}

// 		// calculations
// 		if (!pause) 
// 		{
//         	ghost.update(map);
// 		}

// 		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

// 		// draw
//         map.draw();
// 		ghost.draw(map);
// 		drawMapTarg(targX, targY, map.pxPerBlock);
// 		// const int *posi = ghost.get_position();
// 		// const int *dir = ghost.get_direction();
// 		// std::cout << posi[0] << std::endl;
// 		// std::cout << posi[1] << std::endl;
// 		// std::cout << dir[0] << std::endl;
// 		// std::cout << dir[1] << std::endl;

// 		FsSwapBuffers();

// 		FsSleep(25);
// 	}
	return 0;
}