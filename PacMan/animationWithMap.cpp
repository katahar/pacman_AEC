#include <iostream>
#include <vector>
#include <string>

#include "consumable.h"
#include "map.h"
#include "scoreboard.h"
#include "fssimplewindow.h"
#include <iostream>
#include "animation.h"

int main()
{
    int windowWid = 672;
    int windowHei = 900;
    int pixelSize = 24;

    FsOpenWindow(0, 0, windowWid, windowHei, 1);

    std::string mapName = "maps/map2.txt";
    Map m(mapName);
    ScoreBoard s(windowWid, windowHei);
    Animation animation(windowWid, windowHei, pixelSize);
    
    s.setPlayerName("shreyas_new_test");
    s.readScores();
    s.displayHighScoresConsole();
    animation.assignTextPos();
    animation.loadGhosts();
	animation.loadPacman();
	animation.loadFood();
	animation.loadWords();

    std::cout<<"\nRunning Initial Animation Press Space to start interactive pacman movement"<<std::endl;  
	animation.initialAnimation();
	//animation.removeGhostMode();
    
    int initialX = 13;
    int initialY = 11;
    m.updatePacmanLoc(initialX, initialY);
    int x = m.getPacmanX();
    int y = m.getPacmanY();
    
    std::cout<<x<<" "<<y<<"\n";
    std::vector<int> iniState = animation.blockToPixelCoords(initialX, initialY);
    std::vector<int> orientation = {0, 0};
    animation.pacmanState[0] = iniState[0];
    animation.pacmanState[1] = iniState[1];
    int movementRate = pixelSize;
	int k = 0;

    for(;;)
    {
        //std::cout<<"faza";
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto key = FsInkey();
        if (FSKEY_ESC == key){
            break;
        }
        m.RenderMap(animation);
        s.drawScore();

        if(key == FSKEY_UP){
            if(m.checkCollisionPacManWallUp()){
                animation.pacmanOrientation[0] = 3;
                animation.pacmanState[1] -= movementRate;
                animation.pacmanOrientation[1] += 1;
            } 
        }
        else if(key == FSKEY_LEFT){
            if(m.checkCollisionPacManWallLeft()){
                animation.pacmanOrientation[0] = 1;
                animation.pacmanState[0] -= movementRate;
                animation.pacmanOrientation[1] += 1;
            }
        }
        else if(key == FSKEY_DOWN){
            if(m.checkCollisionPacManWallDown()){
                animation.pacmanOrientation[0] = 0;
                animation.pacmanState[1] += movementRate;
                animation.pacmanOrientation[1] += 1;
            }
        }
        else if(key == FSKEY_RIGHT){
            if(m.checkCollisionPacManWallRight()){
                animation.pacmanOrientation[0] = 2;
                animation.pacmanState[0] += movementRate;
                animation.pacmanOrientation[1] += 1;
            }
        }
        animation.occupiedPixels[int(animation.pacmanState[0]/pixelSize)]
                                [int(animation.pacmanState[1]/pixelSize)] = 1;
        		
        animation.renderPacman();

        FsSwapBuffers();
        FsSleep(100);
    }

    s.saveScore();
    return 0;
}