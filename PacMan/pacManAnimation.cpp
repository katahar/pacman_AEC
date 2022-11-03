#include <iostream>
#include "animation.h"

int main(){
	int width = 672;
	int height = 900;
	int pixelSize = 24;
    Animation animation(width, height, pixelSize);
	animation.loadGhosts();
	animation.loadPacman();
	animation.loadFood();
	animation.loadWords();
	animation.loadScores();

	animation.pacmanState[0] = 240;
	animation.pacmanState[1] = 240;
	FsOpenWindow(0,0,width,height,1);
	std::cout<<"Running Initial Animation Press Space to start interactive pacman movement"<<std::endl;  
	animation.levelUpAnimation();
	animation.removeGhostMode();
	int k = 0;
	int movementRate = 24;
    for(;;)
	{
		glViewport(0, 0, width, height);
    	glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		for(int i=0;i<width;i+=movementRate){
			
			//animation.renderFood(width, height);
        	FsPollDevice();
        	auto key = FsInkey();
			if(key == FSKEY_ESC)
            	return 0;

			animation.renderPacman();
			animation.renderGameOver();
			animation.renderOneGhost(0, 24, 24, 3);
			animation.renderOneGhost(1, 48, 48, 3);
			animation.renderOneGhost(2, 72, 72, 3);
			animation.renderOneGhost(3, 96, 96, 3);
			std::vector<int> next = {0, 2, 3, 1};
			animation.updateGhosts(next);
			animation.renderPacManLives();
			animation.renderScores(animation.livesRemaining);
			animation.livesRemaining -= 1;
			

			// else if(key == FSKEY_UP){
			// 	animation.pacmanOrientation[0] = 3;
			// 	animation.pacmanState[1] -= movementRate; 
			// }
			// else if(key == FSKEY_LEFT){
			// 	animation.pacmanOrientation[0] = 1;
			// 	animation.pacmanState[0] -= movementRate;
			// }
			// else if(key == FSKEY_DOWN){
			// 	animation.pacmanOrientation[0] = 0;
			// 	animation.pacmanState[1] += movementRate;
			// }
			// else if(key == FSKEY_RIGHT){
			// 	animation.pacmanOrientation[0] = 2;
			// 	animation.pacmanState[0] += movementRate;
			// }
			// else if(key == FSKEY_D)
			// {
			// 	std::cout<<"hkf\n";
			// 	animation.pacmanDeathAnimation();
			// 	break;
			// }

			// animation.occupiedPixels[int(animation.pacmanState[0]/pixelSize)]
			// 						[int(animation.pacmanState[1]/pixelSize)] = 1;
			// animation.pacmanOrientation[1] += 1;		
			// //animation.renderPacman();
			// if(k%2 == 0 || k%2 == 1){
			// 	animation.updateGhosts({2, 2, 2, 2});
			// 	animation.renderGhosts({i, i, i, i}, {20, 60, 160, 120});
			// }
			// else{
			// 	i -= movementRate;
			// 	animation.updateGhosts({0, 0, 0, 0});
			// 	animation.renderGhosts({i, i, i, i}, 
			// 						   {20+movementRate, 60+movementRate, 160+movementRate, 120+movementRate});
			// }
			//animation.renderMap();
			k += 1;
			FsSwapBuffers();
			FsSleep(1000);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		}
		//break;
		glEnd();
		//FsSwapBuffers();
	}

}