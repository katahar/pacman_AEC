#include "PC_Character.h"


int test  = 2; 

PC_Character::PC_Character(double def_home_pos[2], double velocity, int level, int pixels_per_block, int map_width_blocks, double dt)
{
    init(def_home_pos, velocity, level, pixels_per_block, map_width_blocks, dt);
}

PC_Character::PC_Character()
{
    //will have to call init later. 
    int a = 0;
}


void PC_Character::init(double def_home_pos[2], double velocity, int level, int pixels_per_block, int map_width_blocks, double dt)
{
    // std::cout<<"\n--------INIT--------\n";
    this->home_position[0] = def_home_pos[0];
    // std::cout<<"home pos 0 " << this->home_position[0] <<"\n";
    this->home_position[1] = def_home_pos[1];
    // std::cout<<"home pos 1 " << this->home_position[1] <<"\n";
    this->base_velocity = velocity; 
    // std::cout<<"vel " << this->base_velocity <<"\n";
    this->dt = dt;
    // std::cout<<"dt" <<this->dt <<"\n";
    this->level = level;
    // std::cout<<"level" << this->level <<"\n";
    this->pixels_per_block = pixels_per_block;
    // std::cout<<"ppb" << this->pixels_per_block <<"\n";
    this->map_width_blocks = map_width_blocks ;

    this->current_position[0] = this->home_position[0];
    this->current_position[1] = this->home_position[1];
    // std::cout<<"Set current position to home position \n";

    //@TODO: add switch using current level
    current_velocity = base_velocity;
    // std::cout<<"velcoity\n";
    current_direction = RIGHT;
    // std::cout<<"right \n";

    // std::cout<<"\n--------INIT END--------\n";
}

double PC_Character::get_x_pos()
{
    return current_position[0];
}

double PC_Character::get_y_pos()
{
    return current_position[1];
}

void PC_Character::update_block_center(double cur_block_center[2])
{
    this->cur_block_center[0] = cur_block_center[0];
    this->cur_block_center[1] = cur_block_center[1];
}

void PC_Character::get_block_center(double cur_block_center[2])
{
    cur_block_center[0] = this->cur_block_center[0];
    cur_block_center[1] = this->cur_block_center[1];
}

bool PC_Character::is_feasible(bool wall_present, double cur_block_center[2]) //blockcenter in pixel coordinates
{
    if(!wall_present) //true if there something to collide with
    {
        return true;
    }
    else //no wall present
    {
        switch(current_direction)
        {
            case UP:
                if(cur_block_center[1] <= current_position[1] ) //character is below block center, can still move up
                {
                    // current_position[1] = cur_block_center[1];
                    // current_position[0] = cur_block_center[0];//realigns center for direction change
                    return true;
                }
                else
                {
                    return false;
                }
                break;
            case DOWN:
                if(cur_block_center[1] >= current_position[1] ) //character is above block center, can still move down
                {
                    // current_position[1] = cur_block_center[1];
                    // current_position[0] = cur_block_center[0];
                    return true;
                }
                else
                {
                    return false;
                }
                break;
            case RIGHT:
                if(cur_block_center[0] >= current_position[0]  ) //character is left of block center, can still move right
                {
                    // current_position[0] = cur_block_center[0];
                    // current_position[1] = cur_block_center[1];
                    return true;
                }
                else
                {
                    return false;
                }
                break;
            case LEFT:
                 if(cur_block_center[0] <= current_position[0] ) //character is left of block center, can still move right
                {
                    // current_position[0] = cur_block_center[0];
                    // current_position[1] = cur_block_center[1];
                    return true;
                }
                else
                {
                    return false;
                }
                break;
        
        }
    }
}

void PC_Character::set_direction(std::string input_direction)
{
    if (input_direction == "UP" || input_direction == "up")
    {
       current_direction = UP;
    }
    else if (input_direction == "DOWN" || input_direction == "Down" || input_direction == "down")
    {    
        current_direction = DOWN;
    }
    else if (input_direction == "LEFT" || input_direction == "Left" || input_direction == "left")
    {
        current_direction = LEFT;
    }
    else if (input_direction == "RIGHT" || input_direction == "Right" || input_direction == "right")
    {
        current_direction = RIGHT;
    }
    else
    {
        current_direction = RIGHT;
    }
}

bool PC_Character::set_direction(std::string input_direction, bool wall_present)
{
    if(!wall_present)
        {
        if (input_direction == "UP" || input_direction == "up")
        {
            if(current_direction == LEFT || current_direction == RIGHT )
            {
                current_position[0] = cur_block_center[0];
                current_position[1] = cur_block_center[1];
            }
            current_direction = UP;
        }
        else if (input_direction == "DOWN" || input_direction == "Down" || input_direction == "down")
        {    
            if(current_direction == LEFT || current_direction == RIGHT )
            {
                current_position[0] = cur_block_center[0];
                current_position[1] = cur_block_center[1];
            }
            current_direction = DOWN;
        }
        else if (input_direction == "LEFT" || input_direction == "Left" || input_direction == "left")
        {
            if(current_direction == UP || current_direction == DOWN )
            {
                current_position[0] = cur_block_center[0];
                current_position[1] = cur_block_center[1];
            }
            current_direction = LEFT;
        }
        else if (input_direction == "RIGHT" || input_direction == "Right" || input_direction == "right")
        {
            if(current_direction == UP || current_direction == DOWN )
            {
                current_position[0] = cur_block_center[0];
                current_position[1] = cur_block_center[1];
            }
            current_direction = RIGHT;
        }
        else
        {
            current_direction = RIGHT;
        }
    }
    return !wall_present;
}

void PC_Character::move(bool is_feasible)
{
    if(is_feasible)
    {
        switch(current_direction)
        {
            case UP:
                current_position[1] = current_position[1] - (current_velocity*pixels_per_block*dt); //might need to be subtracted
                break;
            case DOWN:
                current_position[1] = current_position[1] + (current_velocity*pixels_per_block*dt); //might need to be added
                break;
            case RIGHT:
                current_position[0] = current_position[0] + (current_velocity*pixels_per_block*dt); 
                // std::cout << "checking teleport" << " at x pos :" << current_position[0] << std::endl;
                if(current_position[0] >= (map_width_blocks*pixels_per_block)- (pixels_per_block*0.5))
                {
                    // std::cout << "original x: " << current_position[0] << std::endl;
                    current_position[0] = 0; 
                    // std::cout << "Teleporting from right" << std::endl;
                    // std::cout << "new x: " << current_position[0] << std::endl;
                }
                break;
            case LEFT:
                current_position[0] = current_position[0] - (current_velocity*pixels_per_block*dt); 
                // std::cout << "checking teleport" << " at x pos :" << current_position[0] << std::endl;
                if(current_position[0] <= pixels_per_block*0.5 )
                {
                    // std::cout << "original x: " << current_position[0] << std::endl;
                    current_position[0] = (map_width_blocks*pixels_per_block)-5; 
                    // std::cout << "Teleporting from left" << std::endl;
                    // std::cout << "new x: " << current_position[0] << std::endl;
                }
                break;
        }

        
    }
}

bool PC_Character::get_mode()
{
    return scatter_mode; 
}


void PC_Character::set_mode(bool mode)
{
    scatter_mode = mode;
}


// need function on map tha tconverts pixel to location. 

void PC_Character::iterate_animation()
{
    animation_index++;
}

bool PC_Character::get_alive()
{
    return is_alive;
}

void PC_Character::kill_character()
{
    is_alive = false; 
}

double PC_Character::get_base_velocity()
{
    return base_velocity;
}

PC_Character::direction PC_Character::get_direction()
{
    return current_direction;
}

void PC_Character::get_direction_vec(int &dx, int &dy)
{
    switch(current_direction)
        {
            case UP:
                dx = 0, dy = -1;
                break;
            case DOWN:
                dx = 0, dy = 1;
                break;
            case RIGHT:
                dx = 1, dy = 0;
                break;
            case LEFT:
                dx = -1, dy = 0;
                break;
        }
}

std::string PC_Character::get_str_direction()
{
    switch(current_direction)
        {
            case UP:
                return "UP";
                break;
            case DOWN:
                return "DOWN";
                break;
            case RIGHT:
                return "RIGHT";
                break;
            case LEFT:
                return "LEFT";
                break;
            default:
                return "RIGHT"; //in case something gets modified in the init
                break;
        }
}

void PC_Character::set_direction(direction input_direction)
{
    current_direction = input_direction;
}

void PC_Character::get_position(double position[2]) //populates position with current location 
{
    position[0] = current_position[0];
    position[1] = current_position[1];
}

void PC_Character::set_position(double position[2]) //sets character location to specified position
{
    current_position[0] = position[0];
    current_position[1] = position[1];
}


void PC_Character::go_Home() //returns character to their home position
{
    current_position[0] = home_position[0];
    current_position[1] = home_position[1];
}


// private:
// direction current_direction;
// double velocity; //character's speed in blocks per second. (scaling is done using pixels_per_block)
// double current_position [2]; // current character x,y position in map coordinates
// double home_position[2]; // beginning character x,y position in map coordinates
// int animation_index; 
// bool is_alive;
// int level; //will be used to determine character properties such as velocity modifiers, etc. 
// double dt; //used for velocity calculations. Will have to be a global variable within the game class
// int pixels_per_block; //used for determining speed. Original game block is is 8x8 pixels, or 8 pixels per block 
