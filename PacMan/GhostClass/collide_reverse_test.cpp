#include "GhostManager.h"

/*
Testing the general behavior- the pacman location will change intermittently and the ghosts will most accordingly.
The ghosts should never be in prohibited spots of the map or reverse directions.
Visualization shown along with pass/fail.
*/
int main(){

    Map map;
    GhostManager gm;

    FsOpenWindow(0, 0, map.getMapWid(), map.getMapHei(), 1);

    int pacmanX=0, pacmanY=0;

    const int targChanges = 5;
    int times[targChanges] =      {5,  10, 15, 20, 25};
    int pacXLocs[targChanges] =   {27, 27,  0, 14, 20};
    int pacYLocs[targChanges] =   {35, 0 , 35, 18, 30};
    int idx = 0;

    int ghostPrevDir[4][2] = {0};

    auto ghosts = gm.get_ghosts();
    gm.reset();
    bool chase = true;
    double t = 0;
    double tol = 1e-8;
    FsPassedTime();
    while (t < 25)
    {

        FsPollDevice();

        // input
        auto key = FsInkey();
        if(FSKEY_ESC==key)
        {
            return 1;
        }
        // std::cout << t << std::endl;
        auto ms = FsPassedTime();
        t += (double)ms/1000.0;

        if (t > times[idx%targChanges])
        {
            pacmanX = pacXLocs[idx%targChanges];
            pacmanY = pacYLocs[idx%targChanges];
            ++idx;
        }

        gm.update(map, pacmanX, pacmanY, 1, 0, chase);

        for (int i = 0; i < 4; ++i)
        {
            auto dir = ghosts[i].get_direction();
            if (dir[0] + ghostPrevDir[i][0] == 0 &&
                dir[1] + ghostPrevDir[i][1] == 0)
                {
                    std::cout << "Error: ghost " << i << " reversed" << std::endl;
                    return 1;
                }
            
            auto pos = ghosts[i].get_position();
            int posX, posY;
            map.pixelToBlockCoords(pos[0], pos[1], posX, posY);
            if (1 == map.getMapValue(posX,posY))
            {
                std::cout << "Error: ghost " << i << " in prohibited location" << std::endl;
                return 1;
            }

        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        map.RenderMap();
        gm.draw(map.getBlockWid());
        map.FillCell(pacmanX, pacmanY, 255, 255, 0);
        
        FsSwapBuffers();
        FsSleep(10);
    }

    return 0;
}