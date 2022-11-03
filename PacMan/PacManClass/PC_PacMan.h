#ifndef PC_PACMAN_CLASS_INCLUDED
#define PC_PACMAN_CLASS_INCLUDED

#include "PC_Character.h"

class PC_PacMan : public PC_Character
{
public:

    // figure out this inheritance stuff
    // PC_PacMan():PC_Character([0.0,0.0], 5, 1, 5, 0.01);

    PC_PacMan();

    int get_lives();
    void add_life();
    bool remove_life(); //reduces lives by 1, returns whether pacman is still alive ( get_alive )

    //score stuff
    int getScore();
    int increaseScore(int score_add);
    void resetScore();
    void levelReset();
    void eatPellet();
    int getPelletCount(); 
     

    //move to character class!!
    // bool check_collision(double ghost_positions[2]); 
    // bool check_collision(double ghost_position1[2], double ghost_position2[2], double ghost_position3[2], double ghost_position4[2]);
    bool check_collision_block(double ghost_positions[2]); //provided in block coordinates
    bool check_collision_block(double ghost_position1[2], double ghost_position2[2], double ghost_position3[2], double ghost_position4[2]);

private:
    int remaining_lives = 3;
    int score; //score?

    double radius = 5; //retired 
        
    double def_home_pos[2] = {0.0,0.0};
    double def_velocity = 1;
    int def_level = 0;
    int def_pixels_per_block = 5;
    double def_dt = 0.01;
    int def_num_blocks_x_map = 28;
    int pelletCount = 0; 
}; 

#endif