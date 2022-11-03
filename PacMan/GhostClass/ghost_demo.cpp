#include "GhostManager.h"

int main(){

    Map map;
    GhostManager gm;
    Animation anim(map.getMapWid(), map.getMapHei(), PX_PER_BLOCK);
    
    // auto ghosts = gm.get_ghosts();
    int targX = 13.5*PX_PER_BLOCK, targY = 26*PX_PER_BLOCK;

    FsOpenWindow(0, 0, map.getMapWid(), map.getMapHei(), 1);
    
    bool term = false;
    bool pause = true;

    anim.assignTextPos();
    anim.loadGhosts();
	anim.loadPacman();
	anim.loadFood();
	anim.loadWords();
    
    // int fps = 0;
    // double t = 0;
    // auto ms0 = FsPassedTime();
    // double t0 = (double)ms0/1000.0;
    while(term!=true)
    {
        FsPollDevice();

		// ++fps;
		// auto ms = FsPassedTime();
        // t += (double)ms/1000.0;
        // if (1 <= t - t0)
        // {
        //     std::cout << "fps: " << fps << std::endl; 
        //     fps = 0;
        //     t0 = t;
        // }

        int collisionId = -1;
        bool frightened = false;
        // input
        auto key = FsInkey();
        {
            if(FSKEY_ESC==key)
            {
                term = true;
            }
            if(FSKEY_SPACE==key)
            {
                pause = !pause;
            }
            // if(FSKEY_C==key)
            // {
            //     mode = CHASE;
            //     change_mode = true;
            // }
            // if(FSKEY_S==key)
            // {
            //     mode = SCATTER;
            //     change_mode = true;
            // }
            if(FSKEY_F==key)
            {
                frightened = true;
            }
            if(FSKEY_P==key)
            {
                gm.increment_ghost_dot_counter();
            }
            if (FSKEY_0==key)
            {
                collisionId=0;
            }
            if (FSKEY_1==key)
            {
                collisionId=1;
            }
            if (FSKEY_2==key)
            {
                collisionId=2;
            }
            if (FSKEY_3==key)
            {
                collisionId=3;
            }
        }
		int lb,mb,rb,mx,my;
		auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);
		if(FSMOUSEEVENT_LBUTTONDOWN==evt)
		{
            targX = mx;
            targY = my;
		}
        
        // update
        if (!pause)
        {
            gm.update(map, targX/PX_PER_BLOCK, targY/PX_PER_BLOCK, 1, 0, frightened);
        }
        
        // draw 
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        map.RenderMap(anim);
        map.FillCell(targX/PX_PER_BLOCK, targY/PX_PER_BLOCK, 255, 255, 255);
        gm.draw();
        // gm.draw_targets(map);

        FsSwapBuffers();
        FsSleep(20);
    }

    return 0;
}