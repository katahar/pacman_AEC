#ifndef PARAMS_H_INCLUDED
#define PARAMS_H_INCLUDED

enum Mode
{
    CHASE,
    SCATTER,
    FRIGHTENED
};

const int NORMAL_SPEED = 4;
const int FRIGHTENED_SPEED = 3;
const int RETURN_SPEED = 24;
const int MOVE_DELAY = 1;

const int NX = 28;
const int NY = 36;
const int PX_PER_BLOCK = 24;

const int FPS = 30;
const int MODE_TIMERS[8] = {7*FPS, 20*FPS, 7*FPS, 20*FPS, 5*FPS, 20*FPS, 5*FPS, -1};
const int FRIGHTENED_TIMER = 6*FPS/MOVE_DELAY;
const int FRIGHTENED_WARNING_TIMER = 4*FPS/MOVE_DELAY;

const int N = 4;
const int SCATTER_TARGETS[N][2] = 
{
    26  , 0,
    1   , 0,
    27  , 35,
    0   , 35
};

const double HOME_POSITIONS[N][2] = 
{
    13.5, 14.0,
    13.5, 18.0,
    11.0, 16.0,
    16.0, 16.0
};

const int INIT_DIRECTIONS[N][2] = 
{
    1   , 0,
    1   , 0,
    0   , 1,
    0   , 1
};

const int DEFAULT_COLORS[N][3] = 
{
    255 , 0     , 0,
    255 , 184   , 255,
    0   , 255   , 255,
    255 , 184   , 82 
};

const int GHOST_HOUSE_DOOR[2][2] =
{
    13  , 15,
    14  , 15
};

const int GHOST_HOUSE_EXIT[2] = {13, 14};
const int GHOST_HOUSE_ENTRANCE[2] = {14, 16};

const bool INIT_GHOST_HOUSE[N] = {0, 1, 1, 1};
const int GHOST_HOUSE_INIT_DOT_LIMIT[N] = {0, 0, 20, 40};
const int GHOST_HOUSE_RESET_DOT_LIMIT[N] = {0, 10, 20, 30};


#endif