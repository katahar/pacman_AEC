#include "PC_PacMan.h"

bool collision_test(PC_PacMan& pman) //returns true if passed. 
{
    double start_center[] = {0,0};
    pman.init(start_center,15,0,24,0.01);

    double collide_ghost[] = {0,0};
    double no_collide_ghost1[] = {1,0};
    double no_collide_ghost2[] = {0,1};
    double no_collide_ghost3[] = {1,1};

    if( false == pman.check_collision_block(collide_ghost) )
    {
        return false;
    }
    if( true == pman.check_collision_block(no_collide_ghost1) )
    {
        return false;
    }
    if( true == pman.check_collision_block(no_collide_ghost2) )
    {
        return false;
    }
    if( true == pman.check_collision_block(no_collide_ghost3) )
    {
        return false;
    }
    if(false== pman.check_collision_block(collide_ghost,no_collide_ghost1,no_collide_ghost2,no_collide_ghost3 ))
    {
        return false;
    }

    return true;
}


bool life_test(PC_PacMan& pman) //returns true if passed. 
{
    double start_center[] = {0,0};
    pman.init(start_center,15,0,24,0.01);

    if(3!=pman.get_lives())
    {
        return false;
    }

    pman.add_life();
    if(4!=pman.get_lives())
    {
        return false;
    }

    pman.remove_life();
    if(3!=pman.get_lives())
    {
        return false;
    }
    
    pman.remove_life();
    if(2!=pman.get_lives())
    {
        return false;
    }
    return true;

}

int main()
{
    PC_PacMan pman; 

    if(false == collision_test(pman) ) //failed test
    {
        return 1; 
    }
    if(false == life_test(pman) ) //failed test
    {
        return 1; 
    }
    return 0;

}