#ifndef PC_CHARACTER_CLASS_INCLUDED
#define PC_CHARACTER_CLASS_INCLUDED
#include <string>
#include <iostream>


class PC_Character
{
    public:
    PC_Character(double def_home_pos[2], double velocity, int level, int pixels_per_block, int map_width_blocks, double dt);
    PC_Character();
    void init(double def_home_pos[2], double velocity, int level, int pixels_per_block, int map_width_blocks, double dt);

    //may need to reenumerate these within the map class. 
    enum direction {UP, DOWN, LEFT, RIGHT};
    

    //motion-related functions
    void move(bool is_feasible); 
    bool is_feasible(bool wall_present, double cur_block_center[2]); //blockcenter in pixel coordinates
    void iterate_animation(); //retired
    
    //character state stuff
    bool get_alive();
    void kill_character();
    

    double get_base_velocity();
    double get_current_velocity(); // will be populated in subclasses
    direction get_direction();
    std::string get_str_direction();
    void set_direction(direction input_direction);
    void set_direction(std::string input_direction);
    bool set_direction(std::string input_direction, bool wall_present);
    void get_position(double positition[2]); //populates position with current location, in pixels. Map will have to convert it to block coordinates
    void set_position(double positition[2]); //sets character location to specified position
    void update_block_center(double cur_block_center[2]);
    void get_block_center(double cur_block_center[2]);
    double get_x_pos(); //returns x location in pixels
    double get_y_pos(); //returns y location in pixels
    void get_direction_vec(int &dx, int &dy);
    void go_Home(); //returns character to their home position
    bool get_mode(); //returns scatter mode
    void set_mode(bool mode);
    



    protected:
    direction current_direction;
    double base_velocity; //character's base speed in blocks per second. (scaling is done using pixels_per_block)
    double current_velocity; //recalculated based on level. 
    
    double current_position [2]; // current character x,y position in map coordinates EDIT: USING PIXEL COORDINATES
    double home_position[2]; // beginning character x,y position in map coordinates EDIT: USING PIXEL COORDINATES
    double cur_block_center[2];

    int animation_index; 
    bool is_alive;
    int level; //will be used to determine character properties such as velocity modifiers, etc. 
    double dt; //used for velocity calculations. Will have to be a global variable within the game class
    int pixels_per_block; //used for determining speed. Original game block is is 8x8 pixels, or 8 pixels per block 
    bool scatter_mode; //used to indicate if the character is in scatter mode. 
    int map_width_blocks; 
    
};

#endif