#include "GhostManager.h"

/*
Testing the chase behavior- ghosts should stay within respective regions of the map based on target position.
Not testing inky's behavior here since his target position depends on both pacman and blinky's positions and is less predictable.
Visualization shown along with pass/fail.
*/
int main(){

    Map map;
    GhostManager gm;

    FsOpenWindow(0, 0, map.getMapWid(), map.getMapHei(), 1);

    double blinkyBB[2][2]   = { 20.0, 26.0,
                                4.0 , 8.0};
    double pinkyBB[2][2]    = { 1.0 , 6.0,
                                4.0 , 8.0};
    double inkyBB[2][2]     = { 15.0, 26.0,
                                26.0, 32.0};
    double clydeBB[2][2]    = { 1.0 , 12.0,
                                26.0, 32.0};

    auto ghosts = gm.get_ghosts();
    ghosts[0].set_position(26, 4);
    ghosts[1].set_position(1, 4);
    ghosts[2].set_position(26, 32);
    ghosts[3].set_position(1, 32);
    bool chase = false;
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

        // check inky bounding box
        if (ghostPos[2][0] + tol < inkyBB[0][0] || ghostPos[2][0] > inkyBB[0][1] + tol ||
            ghostPos[2][1] + tol < inkyBB[1][0] || ghostPos[2][1] > inkyBB[1][1] + tol)
        {
            std::cout << "inky failed" << std::endl;
            std::cout << ghostPos[2][0] << ", " << ghostPos[2][1] << std::endl;
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

        gm.update(map, 0, 0, 0, 0, chase);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        map.RenderMap();
        gm.draw(map.getBlockWid());
        
        FsSwapBuffers();
        FsSleep(10);
    }

    return 0;
}