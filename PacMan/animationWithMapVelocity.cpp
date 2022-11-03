#include <iostream>
#include <vector>
#include <string>

#include "fssimplewindow.h"
#include "consumable.h"
#include "map.h"
#include "scoreboard.h"
#include "animation.h"
#include "PC_PacMan.h"
#include "GhostManager.h"
#include "sound.h"

int main()
{

    std::cout<< "Final Version " << std::endl;
    std::string mapName = "maps/map1.txt";
    Map m(mapName);
    int windowWid = m.getMapWid();
    int windowHei = m.getMapHei();
    int pixelSize = m.getBlockWid();
    int char_size = 30;

    FsOpenWindow(0, 0, windowWid, windowHei, 1);

    ScoreBoard s(windowWid, windowHei);
    Animation animation(windowWid, windowHei, pixelSize);
    
    s.setPlayerName("player");
    s.readScores();
    s.displayHighScoresConsole();
    animation.assignTextPos();
    animation.loadGhosts();
	animation.loadPacman();
	animation.loadFood();
	animation.loadWords();
    animation.loadScores();

    SoundPlayer sound; 

    sound.startPlay(); 
    sound.playIntroMusic(); 

    //std::cout<<"\nRunning Initial Animation Press Space to start interactive pacman movement"<<std::endl;  
	animation.initialAnimation();
    
    sound.stopAll();
    
    int initialX = 13;
    int initialY = 26;
    m.updatePacmanLoc(initialX, initialY);
    int x = m.getPacmanX();
    int y = m.getPacmanY();
    
    // std::cout<<x<<" "<<y<<"\n";
    std::vector<int> iniState = animation.blockToPixelCoords(initialX, initialY);
    std::vector<int> orientation = {0, 0};
    animation.pacmanState[0] = iniState[0] + char_size/2;
    animation.pacmanState[1] = iniState[1];
    int movementRate = char_size ;
	int k = 0;

    //pacman initatiion
    double cur_block_center[2]; // in pixels
    double cur_block_TLCorner[2];
    int cur_block_ind[2];
    m.blockToPixelCoords(cur_block_TLCorner[0],cur_block_TLCorner[1], initialX, initialY); //gets pixel top left of given block
    m.getBlockCenter(cur_block_TLCorner[0],cur_block_TLCorner[1], cur_block_center[0],cur_block_center[1]); //gets center coordinate of block given other coordinate in block
    cur_block_center[0] += char_size/2;
    m.pixelToBlockCoords(cur_block_center[0], cur_block_center[1], cur_block_ind[0], cur_block_ind[1]);

    PC_PacMan pman; 
    pman.init(cur_block_center,4,0,pixelSize,m.getNumBlocksX(),0.05);
    animation.pacmanOrientation[0] = 2;
    animation.pacmanOrientation[1] = 0;
    animation.occupiedPixels[int(cur_block_ind[0])]
                            [int(cur_block_ind[1])] = 1;
    //std::cout<<"\npacman object created and initialiized\n";

    // ghost manager
    GhostManager gm;

    sound.startPlay();
    bool pause = true;
    bool sys_pause = false; 
    bool death_flag = false; 
    bool life_lost_flag = false; 
    bool level_up_flag = false; 
    int level_pellet_count = 244; 
    int level = 1; 

    int fps = 0;
    double t = 0;
    auto ms0 = FsPassedTime();
    double t0 = (double)ms0/1000.0;
    bool start_timestep = true;
    for(;;)
    {

		++fps;
		auto ms = FsPassedTime();
        t += (double)ms/1000.0;
        if (1 <= t - t0)
        {
            //std::cout << "fps: " << fps << std::endl; 
            fps = 0;
            t0 = t;
        }

        if(level_up_flag || life_lost_flag )
        {
            if (level_up_flag) 
            {
                pman.levelReset(); 
            }
            
            pman.go_Home();

            //updates current block center for later evaluation
            m.getBlockCenter(pman.get_x_pos(),pman.get_y_pos(), cur_block_center[0], cur_block_center[1]); 
            pman.update_block_center(cur_block_center);
            //updates the bock index based on current location
            m.pixelToBlockCoords(pman.get_x_pos(),pman.get_y_pos(), cur_block_ind[0], cur_block_ind[1]);
            pman.set_direction("RIGHT", m.checkCollisionWall(pman.get_x_pos(),pman.get_y_pos(), "RIGHT"));

            animation.pacmanState[0]= pman.get_x_pos() - (0.5*char_size ); //reset pacman location after animation
            animation.pacmanState[1]= pman.get_y_pos() + (0.5*char_size );
            gm.reset();
            level_up_flag = false; 
            life_lost_flag = false; 
            animation.pacmanOrientation[0] = 2;
            animation.pacmanOrientation[1] = 0;
            pause = true; 
        }


        //getting inputs
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto key = FsInkey();

       
        if (FSKEY_ESC == key){
            break;
        }

        if(FsGetKeyState(FSKEY_UP)!=0)
        {
            pause = false;
            if(pman.set_direction("UP", m.checkCollisionWall(pman.get_x_pos(),pman.get_y_pos(), "UP")))
            {
                animation.pacmanOrientation[0] = 3;
            }
            animation.isFirstStep = false;
        }
        else if(FsGetKeyState(FSKEY_LEFT)!=0)
        {
            pause = false;
            if (pman.set_direction("LEFT", m.checkCollisionWall(pman.get_x_pos(),pman.get_y_pos(), "LEFT")))
            {
                animation.pacmanOrientation[0] = 1;
            }
            animation.isFirstStep = false;
        }
        else if(FsGetKeyState(FSKEY_DOWN)!=0)
        {
            
            pause = false;
            if(pman.set_direction("DOWN", m.checkCollisionWall(pman.get_x_pos(),pman.get_y_pos(), "DOWN")))
            {
                animation.pacmanOrientation[0] = 0;
            }
            animation.isFirstStep = false;
        }
        else if(FsGetKeyState(FSKEY_RIGHT)!=0)
        {
            pause = false;
            if(pman.set_direction("RIGHT", m.checkCollisionWall(pman.get_x_pos(),pman.get_y_pos(), "RIGHT")))
            {
                animation.pacmanOrientation[0] = 2;
            }
            animation.isFirstStep = false;
        }

        else if (key == FSKEY_J){
            m.changeMapTo2();
        }
        else if (key == FSKEY_K){
            m.changeMapTo1();
        }

        else if (FSKEY_PLUS == key){
            sound.adjustVolume(0.1);
        }
        else if (FSKEY_MINUS == key){
            sound.adjustVolume(-0.1);
        }
        
        else if (FSKEY_I == key){
            level_up_flag = true;
        }

        else if (FSKEY_H == key){
            s.displayHighScoresConsole();
        }

        if(key == FSKEY_SPACE)
        {
            pause = !pause;
        }


        if (!pause && !sys_pause) // main game block. 
        {
            //moves pacman
            if (pman.is_feasible(m.checkCollisionWall(pman.get_x_pos(),pman.get_y_pos(), pman.get_str_direction()), cur_block_center))
            {
                pman.move(true);
                animation.pacmanOrientation[1] += 1; //advances animation
            }
            else 
            {
                animation.pacmanOrientation[1] = 3;
            }
            
            //updates current block center for later evaluation
            m.getBlockCenter(pman.get_x_pos(),pman.get_y_pos(), cur_block_center[0], cur_block_center[1]); 
            pman.update_block_center(cur_block_center);
            //updates the bock index based on current location
            m.pixelToBlockCoords(pman.get_x_pos(),pman.get_y_pos(), cur_block_ind[0], cur_block_ind[1]);


            //updates state for animation
            animation.pacmanState[0]= pman.get_x_pos() - (0.5*char_size); //moved to center sprite
            animation.pacmanState[1]= pman.get_y_pos() + (0.5*char_size);

            //check map for pellet and add score
            if(m.checkLocForPellet(cur_block_ind[0], cur_block_ind[1]))
            {
                pman.increaseScore(10);
                pman.eatPellet(); 
                s.setScore(s.getScore()+10);
                m.eatPellet(cur_block_ind[0], cur_block_ind[1], false);
                gm.increment_ghost_dot_counter();

                sound.playPacmanMunch();  //@TODO:Bring back
            }
            bool power_pellet_consumed_flag = false; //resetting flag
            if(m.checkLocForPowerPellet(cur_block_ind[0], cur_block_ind[1]))
            {
                pman.increaseScore(50);
                pman.eatPellet(); 
                s.setScore(s.getScore()+50);
                power_pellet_consumed_flag = true; 
                m.eatPellet(cur_block_ind[0], cur_block_ind[1], true);
                gm.increment_ghost_dot_counter();
            }
            // updating ghosts here
            int dx, dy;
            pman.get_direction_vec(dx, dy);
            bool pacman_killed = false;
            int ghosts_consumed_index = gm.check_collision((int)pman.get_x_pos(), (int)pman.get_y_pos(), pacman_killed);
            gm.update(m, (int)pman.get_x_pos()/PX_PER_BLOCK, (int)pman.get_y_pos()/PX_PER_BLOCK, dx, dy, power_pellet_consumed_flag);
            
            //std::cout << m.getNumPellets() << std::endl;
            if(pman.getPelletCount()>=m.getNumPellets())
            {
                level_up_flag = true;
            }

            //dealing with ghost collisions
            if(1 == ghosts_consumed_index )
            {
                pman.increaseScore(200*ghosts_consumed_index);
                s.setScore(s.getScore() + (200*ghosts_consumed_index) );
                //std::cout << "First ghost! 200 points earned!" <<std::endl; 
                //@Akshay show the +200 animation
                animation.renderScores(0);
                sound.playEatGhost(); 
            }
            else if(2 == ghosts_consumed_index )
            {
                pman.increaseScore(200*ghosts_consumed_index);
                s.setScore(s.getScore() + (200*ghosts_consumed_index) );
                //std::cout << "Second ghost! 400 points earned!" <<std::endl; 
                //@Akshay show the +400 animation
                animation.renderScores(1);
                sound.playEatGhost(); 
            }
            else if(3 == ghosts_consumed_index )
            {
                pman.increaseScore(200*ghosts_consumed_index);
                s.setScore(s.getScore() + (200*ghosts_consumed_index) );
                //std::cout << "Third ghost! 600 points earned!" <<std::endl; 
                //@Akshay show the +800 animation
                animation.renderScores(2);
                sound.playEatGhost(); 
            }
            else if(4 == ghosts_consumed_index )
            {
                pman.increaseScore(200*ghosts_consumed_index);
                s.setScore(s.getScore() + (200*ghosts_consumed_index) );
                //std::cout << "Fourth ghost! 800 points earned!" <<std::endl; 
                //@Akshay show the +1600 animation
                animation.renderScores(3);
                sound.playEatGhost(); 
            }
            else if(pacman_killed)
            {
                life_lost_flag = true; 

                pman.remove_life(); 
                animation.livesRemaining -= 1;
                sound.playPacmanDeath(); 
                if(pman.get_lives() <= 0 )
                {
                    death_flag = true; 

                }
            }

        }

        if(level_up_flag)
        {
            //@akshay add animation for level ups
            ++level;
            m.MapBlink(true);
            for(int i = 0; i < 9; ++i)
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                m.RenderMap(animation);
                s.drawScore();
                animation.renderPacman();
                animation.renderPacManLives();                 
                FsSwapBuffers();
                FsSleep(150);
            }
            m.MapBlink(false);

            if(level%2 == 0)
            {
                //@akshay show the between level animations (chasing across the screen)
                sound.playIntermission();
                animation.levelUpAnimation();
                //std::cout<<"levelup animation done"<< std::endl;    
                animation.pacmanState[0]= pman.get_x_pos() - (0.5*char_size ); //reset pacman location after animation
                animation.pacmanState[1]= pman.get_y_pos() + (0.5*char_size );
                animation.resetAnimation();
                m.changeMapTo2();
                animation.isFirstStep = true;
                sound.stopIntermission();
                
            }   
            else
            {
                animation.resetAnimation();
                m.changeMapTo1();
                animation.resetAnimation();
                animation.isFirstStep = true;         

                m.blockToPixelCoords(cur_block_TLCorner[0],cur_block_TLCorner[1], initialX, initialY); //gets pixel top left of given block
                //reseting to home position
                m.getBlockCenter(cur_block_TLCorner[0],cur_block_TLCorner[1], cur_block_center[0],cur_block_center[1]); //gets center coordinate of block given other coordinate in block
                cur_block_center[0] += char_size/2;
                m.pixelToBlockCoords(cur_block_center[0], cur_block_center[1], cur_block_ind[0], cur_block_ind[1]);       
            }
            
        }
        //if (true == m.getMapBlink() && m.getBlinkCount() >= 50){
        //    m.MapBlink(false);
        //}

        //all rendering
        m.RenderMap(animation);
        s.drawScore();
        if(death_flag)
        {
            animation.pacmanDeathAnimation(); 
            death_flag = false; 
            for(int i=0;i<100;++i){
                animation.renderGameOver();
            }
            break;
        }
        if(life_lost_flag ) //lose live animation and reset. 
        {
            animation.pacmanDeathAnimation(); 
            animation.isFirstStep = true;
            animation.resetAnimation();
            continue;
        }
        animation.occupiedPixels[int(cur_block_ind[0])]
                                [int(cur_block_ind[1])+1] = 1; //fixed offset between animation and map get block index
        
        
        animation.renderPacman();
        animation.renderPacManLives();
        gm.render(animation);
        
        FsSwapBuffers();
        FsSleep(10);
    }

    sound.endPlay(); 
    s.saveScore();
    return 0;
}