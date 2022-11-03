#include <iostream>
#include <vector>
#include <string>

#include "consumable.h"
#include "map.h"
#include "scoreboard.h"
#include "fssimplewindow.h"
#include "animation.h"

//// NOT WORKING ANYMORE DUE TO NEW CHANGES

int main(){

    // int windowWid = 672;
    // int windowHei = 900;
    // int pixelSize = 24;

    // FsOpenWindow(0, 0, windowWid, windowHei, 1);

    // Map m(windowWid,windowHei);
    // ScoreBoard s(windowWid, windowHei);
    // Animation animation(windowWid, windowHei, pixelSize);

    // s.setPlayerName("shreyas");

    // s.readScores();
    // s.displayHighScores();

    // for(;;){
    //     FsPollDevice();
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //     auto key = FsInkey();
    //     if (FSKEY_ESC == key){
    //         break;
    //     }
    //     else if (FSKEY_UP == key){
    //         m.checkCollisionPacManWallUp();
    //     }
    //     else if (FSKEY_DOWN == key){
    //         m.checkCollisionPacManWallDown();
    //     }
    //     else if (FSKEY_LEFT == key){
    //         m.checkCollisionPacManWallLeft();
    //     }
    //     else if (FSKEY_RIGHT == key){
    //         m.checkCollisionPacManWallRight();
    //     }
        

    //     glColor3ub(0, 0, 0);
    //     glBegin(GL_QUADS);
    //     glVertex2i(0,0);
    //     glVertex2i(0,windowHei);
    //     glVertex2i(windowWid,windowHei);
    //     glVertex2i(windowWid,0);
    //     glEnd();

    //     m.RenderMap(animation);
    //     s.drawScore();

    //     FsSwapBuffers();
    //     FsSleep(10);
    // }

    // s.saveScore();

    return 0;
}
