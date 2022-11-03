#include "PC_PacMan.h"
#include "PC_Character.h"


PC_PacMan::PC_PacMan()
{
    init(def_home_pos, def_velocity, def_level, def_pixels_per_block,def_num_blocks_x_map, def_dt);
}

    
int PC_PacMan::get_lives()
{
    return remaining_lives;
}

void PC_PacMan::add_life()
{
    remaining_lives++;
}

//reduces lives by 1, returns whether pacman is still alive ( get_alive )
bool PC_PacMan::remove_life() 
{
    remaining_lives--;
    return get_alive();
}

//score stuff
int PC_PacMan::getScore()
{
    return score;
}

int PC_PacMan::increaseScore(int score_add)
{
    score = score + score_add;
    return score;
}

void PC_PacMan::resetScore()
{
    score = 0;
}

int PC_PacMan::getPelletCount()
{
    return pelletCount; 
}

void PC_PacMan::eatPellet()
{
    pelletCount++;
}

void PC_PacMan::levelReset()
{
    // go_Home(); 
    pelletCount = 0; 
    current_direction = RIGHT;

}

// bool PC_PacMan::check_collision(double ghost_positions[2])
// {
//     if( ghost_positions[0] + radius < current_position[0] && ghost_positions[0] - radius > current_position[0] &&
//         ghost_positions[1] + radius < current_position[1] && ghost_positions[1] - radius > current_position[1]      )
//     {
//         return true;
//     }
//     return false;    
// }

bool PC_PacMan::check_collision_block(double ghost_positions[2])
{
    if( ghost_positions[0] == current_position[0] && ghost_positions[1] == current_position[1])
    {
        return true;
    }
    return false;
    
}



// bool PC_PacMan::check_collision(double ghost_position1[2], double ghost_position2[2], double ghost_position3[2], double ghost_position4[2])
// {
//     if( check_collision(ghost_position1) || check_collision(ghost_position2) || check_collision(ghost_position3) || check_collision(ghost_position4) )
//     {
//         return true;
//     }
//     return false;
// }

bool PC_PacMan::check_collision_block(double ghost_position1[2], double ghost_position2[2], double ghost_position3[2], double ghost_position4[2])
{
    if( check_collision_block(ghost_position1) || check_collision_block(ghost_position2) || check_collision_block(ghost_position3) || check_collision_block(ghost_position4) )
    {
        return true;
    }
    return false;

}
