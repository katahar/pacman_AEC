#include "PC_Character.h"

bool direction_test(PC_Character& character) //returns true if passed
{
    double start_center[] = {0,0};
    character.init(start_center,15,0,24,0.01);

    bool wall_present = true; 
    bool wall_not_present = false;

    character.set_direction("RIGHT", wall_not_present); //correctly sets direction to RIGHT

    if(character.get_str_direction() != "RIGHT")
    {
        return false;
    }

    character.set_direction("UP", wall_present); //attempts to set to UP, which should not work
    
    if(character.get_str_direction()!= "RIGHT")
    {
        return false;
    }

    character.set_direction("UP", wall_not_present); //attempts to set to UP, which should not work
    
    if(character.get_str_direction()!= "UP")
    {
        return false;
    }

    character.set_direction("DOWN", wall_not_present); //attempts to set to UP, which should not work
    
    if(character.get_str_direction()!= "DOWN")
    {
        return false;
    }

    character.set_direction("LEFT", wall_not_present); //attempts to set to UP, which should not work
    
    if(character.get_str_direction()!= "LEFT")
    {
        return false;
    }
    
    return true;

}

bool block_center_test(PC_Character& character)//returns true if passed
{
    double set_center[] = {1.3, 2.5};
    double get_center[] = {0,0};

    character.update_block_center(set_center);
    character.get_block_center(get_center);
    
    if( set_center[0] != get_center[0] || set_center[1] != get_center[1] )
    {
        return false;
    }


    set_center[0] = 264.5;
    set_center[1] = 158.1;

    get_center[0] = 0; 
    get_center[1] = 0; 

    character.update_block_center(set_center);
    character.get_block_center(get_center);
    
    if( set_center[0] != get_center[0] || set_center[1] != get_center[1] )
    {
        return false;
    }

    set_center[0] = 18.5;
    set_center[1] = 65.1;


    get_center[0] = 0; 
    get_center[1] = 0; 

    character.update_block_center(set_center);
    character.get_block_center(get_center);
    
    if( set_center[0] != get_center[0] || set_center[1] != get_center[1] )
    {
        return false;
    }

    return true;
}


bool feasibility_test(PC_Character& character)//returns true if passed
{
    double start_center[] = {0,0};
    double cur_block_center[] = {10,10};
    character.init(start_center,15,0,24,0.01);
    bool wall_present = true; 
    bool wall_not_present = false; 


    if( false == character.is_feasible(wall_not_present,cur_block_center) )
    {
        return false;
    }

    character.set_direction("UP");
    cur_block_center[0] = 0; 
    cur_block_center[1] = 0; 
    if( false == character.is_feasible(wall_not_present,cur_block_center) )
    {
        return false;
    }

    character.set_direction("DOWN");
    cur_block_center[0] = 20; 
    cur_block_center[1] = 20; 
    
    if( false == character.is_feasible(wall_not_present,cur_block_center) )
    {
        return false;
    }

    character.set_direction("RIGHT");
    cur_block_center[0] = 20; 
    cur_block_center[1] = 20; 
    
    if( false == character.is_feasible(wall_not_present,cur_block_center) )
    {
        return false;
    }

    character.set_direction("LEFT");
    cur_block_center[0] = 0; 
    cur_block_center[1] = 0; 
    if( false == character.is_feasible(wall_not_present,cur_block_center) )
    {
        return false;
    }
    return true;

}



int main()
{
    
    PC_Character character;
    
    if(false == direction_test(character) ) //failed test
    {
        return 1; 
    }
    if(false == block_center_test(character) ) //failed test
    {
        return 1; 
    }
    if(false == feasibility_test(character) ) //failed test
    {
        return 1; 
    }
}