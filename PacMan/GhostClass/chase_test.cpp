#include "GhostManager.h"


/*
Testing the scatter behavior- ghosts should stay within respective regions of the map.
Visualization shown along with pass/fail.
*/
int main(){

    Map map;
    GhostManager gm;

    FsOpenWindow(0, 0, map.getMapWid(), map.getMapHei(), 1);

    int pacmanX = 15;
    int pacmanY = 23;
    double blinkyBB[2][2]   = { 9.0  , 18.0,
                                20.0 , 26.0};
    double pinkyBB[2][2]    = { 15.0 , 21.0,
                                23.0 , 26.0};
    double clydeBB[2][2]    = { 6.0  , 9.0,
                                17.0 , 23.0};

    auto ghosts = gm.get_ghosts();
    gm.reset();
    bool chase = true;
    double t = 0;
    double tol = 1e-8;
    FsPassedTime();
    while (t < 10)
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

        if (t > 2)
        {
            double ghostPos[4][2];
            for (int i = 0; i < 4; ++i)
            {
                auto pos = ghosts[i].get_position();
                ghostPos[i][0] = pos[0];
                ghostPos[i][1] = pos[1];
            }

            // check blinky bounding box
            if (ghostPos[0][0] + tol < blinkyBB[0][0] || ghostPos[0][0] > blinkyBB[0][1] + tol ||
                ghostPos[0][1] + tol < blinkyBB[1][0] || ghostPos[0][1] > blinkyBB[1][1] + tol)
            {
                std::cout << "blinky failed" << std::endl;
                std::cout << ghostPos[0][0] << ", " << ghostPos[0][1] << std::endl;
                std::cout << blinkyBB[0][0] << ", " << blinkyBB[1][0] << std::endl;
                return 1;
            }

            // check pinky bounding box
            if (ghostPos[1][0] + tol < pinkyBB[0][0] || ghostPos[1][0] > pinkyBB[0][1] + tol ||
                ghostPos[1][1] + tol < pinkyBB[1][0] || ghostPos[1][1] > pinkyBB[1][1] + tol)
            {
                std::cout << "pinky failed" << std::endl;
                std::cout << ghostPos[1][0] << ", " << ghostPos[1][1] << std::endl;
                return 1;
            }

            // check clyde bounding box
            if (ghostPos[3][0] + tol < clydeBB[0][0] || ghostPos[3][0] > clydeBB[0][1] + tol ||
                ghostPos[3][1] + tol < clydeBB[1][0] || ghostPos[3][1] > clydeBB[1][1] + tol)
            {
                std::cout << "clyde failed" << std::endl;
                std::cout << ghostPos[3][0] << ", " << ghostPos[3][1] << std::endl;
                return 1;
            }
        }

        gm.update(map, pacmanX, pacmanY, 1, 0, chase);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        map.RenderMap();
        gm.draw(map.getBlockWid());
        map.FillCell(pacmanX, pacmanY, 255, 255, 0);
        
        FsSwapBuffers();
        FsSleep(10);
    }

    return 0;
}