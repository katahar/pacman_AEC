#ifndef GHOST_IS_INCLUDED
#define GHOST_IS_INCLUDED

#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "GhostParams.h"

/*  
    Ghost 0-Blinky
    Ghost 1-Pinky 
    Ghost 2-Inky  
    Ghost 3-Clyde
*/ 
class Ghost
{
private:
    unsigned char id;
    int position[2];            // in pixels
    int direction[2];           // in {dx, dy}
    int target[2];              // in blocks
    int chase_target[2];        // target based on pacman's current block position
    Mode mode;                  // CHASE, SCATTER, FRIGHTENED
    int dot_counter;            // track num pellets eaten by pacman when preferred ghost (ghost manager informs)
    int dot_threshold;          // threshold to be able to leave ghost house
    bool in_ghost_house;        // if in the ghost house    
    bool leaving_ghost_house;   // if has permission to leave ghost house
    bool dead;                  // dead and returning to ghost house
    int frightened_counter;     // keep track of how long ghost has been frightened, for switching back to other mode
    bool frightened_blink;      // track when to render white ghost instead of blue when frightened
    int speed;                  // in pixels per frame
    int color[3];               // r,g,b in bytes

public:
    // void update(const Map &map, bool chase);
    // void update_direction(const Map &map, bool chase);
    // void update_target(int x, int y);
    // double dist_to_target_from(double x, double y) const;
    // double dist_from_position_to(double x, double y) const;
    // bool collide_pacman() const;
    // void draw(int blockWid) const;
    // void reset();

    // void set_position(double x, double y);
    // void set_home_position(double x, double y);
    // void set_speed(double speed);
    // void set_scatter_target(int x, int y);
    // void set_color(int r, int g, int b);

    // const double* get_position() const;
    // const int* get_direction() const;
    // const int* get_target() const;
    // const int* get_scatter_target() const;
    // double get_speed() const;
    // void get_color(int* arr) const;

    Ghost(){;}

    Ghost(unsigned char id)
    {
        this->id = id;
    }

    void reset(void)
    {
        speed = NORMAL_SPEED;
        mode = SCATTER;
        scatter();
        dot_counter = 0;
        frightened_counter = 0;
        dot_threshold = GHOST_HOUSE_INIT_DOT_LIMIT[id];
        dead = false;
        frightened_blink = false;
        in_ghost_house = INIT_GHOST_HOUSE[id];
        leaving_ghost_house = !GHOST_HOUSE_INIT_DOT_LIMIT[id] && in_ghost_house;
        set_position_by_block(HOME_POSITIONS[id][0], HOME_POSITIONS[id][1]); // HOME_POSITIONS is w.r.t blocks
        set_direction(INIT_DIRECTIONS[id][0], INIT_DIRECTIONS[id][1]);
        reset_color();
    }

    void update(const Map &map)
    {
        // this chunk deals with ghosts leaving and returning to ghost house
        if (in_ghost_house && leaving_ghost_house)  // need to exit ghost house
        {       
            if (is_at_exit())                       // exited safely  
            {   
                in_ghost_house = false;
                leaving_ghost_house = false;
                dot_counter = 0;
                dot_threshold = GHOST_HOUSE_RESET_DOT_LIMIT[id];
                update_mode(mode);
            }
            else 
            {
                update_target(GHOST_HOUSE_EXIT[0], GHOST_HOUSE_EXIT[1]);
            }
        }
        else if (dead && is_at_entrace())           // returned to ghost house safely 
        {
            in_ghost_house = true;
            leaving_ghost_house = !dot_threshold;
            dead = false;
            set_speed(NORMAL_SPEED);
            reset_color();
            update_mode(mode);
        }

        // update direction only if in center of block (can't update when at fractional block location)
        if (position[0]%PX_PER_BLOCK == 0  && position[1]%PX_PER_BLOCK == 0)
        {
            update_direction(map);
        }

        // update position
        position[0] += direction[0]*speed;
        position[1] += direction[1]*speed;

        // teleport if necessary
        if (position[0] < 0)
        {
            position[0] = map.getNumBlocksX()*PX_PER_BLOCK;
        }
        else if (position[0] >= map.getNumBlocksX()*PX_PER_BLOCK)
        {
            position[0] = 0;
        }

        // update target if chasing
        if (mode == CHASE && !dead)
        {
            chase();
        }
        else if (mode == FRIGHTENED)
        {
            ++frightened_counter;
            if (frightened_counter > FRIGHTENED_TIMER)
            {
                mode = CHASE;
                update_mode(CHASE);
                frightened_counter = 0;
                frightened_blink = false;
            }
            else if (frightened_counter > FRIGHTENED_WARNING_TIMER && frightened_counter % 5 == 0)
            {
                blink();
                frightened_blink = !frightened_blink;
            }
        }
        // if (id == 0)
        // {
        //     std::cout << frightened_counter << std::endl;
        // }
    }

    void update_direction(const Map &map)
    {
        int best_direction[2];

        // possible next directions
        int next_direction[] = 
        {
            0   ,   -1  ,
            -1  ,   0   ,
            0   ,   1   ,
            1   ,   0
        };

        double min_dist = 100000;
        for (int i = 0; i < 4; ++i)
        {
            // ghost cannot reverse direction
            if ((direction[0] != 0 && direction[0] == -1*next_direction[2*i]) ||
                (direction[1] != 0 && direction[1] == -1*next_direction[2*i+1]))
            {
                // std::cout << "can't reverse " << i << std::endl;
                continue;
            }
            
            // get position at possible next direction
            int next_position[] = 
            {
                position[0] + next_direction[2*i]*PX_PER_BLOCK,
                position[1] + next_direction[2*i+1]*PX_PER_BLOCK
            };

            // check if cell is open in this direction
            if (!map.getMapValue(next_position[0]/PX_PER_BLOCK, next_position[1]/PX_PER_BLOCK) ||
                ((leaving_ghost_house || dead) && is_at_door(next_position[0], next_position[1])))  // need door to be open for folks returning or exiting
            {
                // if (dead && is_at_door(next_position[0], next_position[1]))
                // {
                //     std::cout << "hi" << std::endl;
                // }
                double dist = dist_to_target_from(next_position[0], next_position[1]);
                // std::cout << i << " " << dist << std::endl;
                if (dist < min_dist)
                {
                    min_dist = dist;
                    best_direction[0] = next_direction[2*i];
                    best_direction[1] = next_direction[2*i+1];
                }
            }
            else
            {
                // std::cout << "cell blocked " << i << std::endl;
            }
            // std::cout << min_dist << std::endl;
        }
        direction[0] = best_direction[0];
        direction[1] = best_direction[1];
        // std::cout << std::endl;
    }

    void update_mode(Mode newMode)
    {
        // update targetting
        if (!(dead || in_ghost_house) && mode != FRIGHTENED)
        {
            switch (newMode)
            {
                case CHASE:
                    chase();
                    break;
                
                case SCATTER:
                    scatter();
                    break;

                case FRIGHTENED:
                    frightened();
                    break;
            }
            if (mode != newMode && mode != FRIGHTENED)
            {
                reverse_direction();
            }
        }
        if (!((dead || in_ghost_house) && newMode == FRIGHTENED) && mode != FRIGHTENED)
        {
            mode = newMode;
        }
        if (mode == FRIGHTENED && newMode == FRIGHTENED)
        {
            frightened();
            frightened_counter = 0;
            frightened_blink = false;
        }
    }

    void switch_mode()
    {
        if (mode == SCATTER)
        {
            update_mode(CHASE);
        }
        else if (mode == CHASE)
        {
            update_mode(SCATTER);
        }
    }

    void update_target(int x, int y)    // target always in block coords
    {
        target[0] = x;
        target[1] = y;
    }

    void update_chase_target(int x, int y)    // target always in block coords
    {
        chase_target[0] = x;
        chase_target[1] = y;
    }

    // pacX and pacY in pixels
    int collide_with_pacman(int pacX, int pacY)
    {
        if (collision(pacX, pacY) )
        {
            if (mode == FRIGHTENED)                // eaten by pacman need to add someting aboure laredy being dead
            {
                if(dead)
                {
                    return -1; 
                }
                else
                {
                    // std::cout << "ghost " << (int)id << " killed" << std::endl;
                    // FsSleep(500);
                    dead = true;
                    frightened_counter = 0;
                    mode = CHASE;
                    set_speed(RETURN_SPEED);
                    set_color(255, 255, 255);
                    update_target(GHOST_HOUSE_ENTRANCE[0], GHOST_HOUSE_ENTRANCE[1]);
                    return 0;
                }
            }
            else if (!dead)                                    // killed pacman
            {
                // std::cout <<"pacman killed"<<std::endl;
                return 1;
            }
        }
        return -1;
    }

    // x and y in pixels
    bool collision(int x, int y)
    {
        int pxTol = 16;
        if (((position[0] + PX_PER_BLOCK/2)/PX_PER_BLOCK == x/PX_PER_BLOCK &&   // in same tile
            (position[1] + PX_PER_BLOCK/2)/PX_PER_BLOCK == y/PX_PER_BLOCK) ||
            (abs(position[0] - x) < pxTol && abs(position[1] - y) < pxTol))       // not in same tile but less than sqrt(2*pxTol^2) pixels away
        {
            return true;
        }
        return false;
    }

    void scatter(void)
    {
        set_speed(NORMAL_SPEED);
        reset_color();
        update_target(SCATTER_TARGETS[id][0], SCATTER_TARGETS[id][1]);
    }

    void chase(void)
    {
        set_speed(NORMAL_SPEED);
        reset_color();
        update_target(chase_target[0], chase_target[1]);
    }

    void frightened(void)
    {
        std::srand(time(NULL)*(id+1));
        int bx = std::rand() % NX;
        int by = std::rand() % NY;

        set_speed(FRIGHTENED_SPEED);
        set_color(0, 0, 255);

        update_target(bx, by);
    }

    double dist_to_target_from(int x, int y) const   // incoming x, y in pixel coords
    {
        double dx = x/PX_PER_BLOCK - target[0];
        double dy = y/PX_PER_BLOCK - target[1];
        return sqrt(dx*dx + dy*dy);                 // return distance in block scale
    }

    double dist_from_position_to(int x, int y) const   // incoming x, y in pixel coords
    {
        double dx = (x - position[0])/PX_PER_BLOCK;
        double dy = (y - position[1])/PX_PER_BLOCK;
        return sqrt(dx*dx + dy*dy);                 // return distance in block scale
    }

    void render(Animation a) const
    {
        int m;
        if (mode == FRIGHTENED)
        {
            m = 1;
            if (frightened_blink)
            {
                m = 2;
            }
        }
        else if (dead)
        {
            m = 3;
        }
        else 
        {
            m = 0;
        }

        int dir;
        if (direction[0] == 0)
        {
            dir = 0;
            if (direction[1] == -1)
            {
                dir = 3;
            }
        }
        else
        {
            dir = 2;
            if (direction[0] == -1)
            {
                dir = 1;
            }
        }

        a.renderOneGhost(id, position[0] , position[1] + PX_PER_BLOCK, m, dir);
    }

    void draw() const
    {
        glColor3ub(color[0], color[1], color[2]);

        double r = PX_PER_BLOCK/2;
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 64; ++i)
        {
            double a = (double)i * PI / 32.0;
            double c = std::cos(a);
            double s = std::sin(a);
            glVertex2d( position[0] + PX_PER_BLOCK/2 + c * r, 
                        position[1] + PX_PER_BLOCK/2 + s * r);
        }
        glEnd();
    }

    bool is_at_door(int x, int y) // incoming x, y in pixel coords
    {
        bool at_door = ((x/PX_PER_BLOCK == GHOST_HOUSE_DOOR[0][0] && y/PX_PER_BLOCK == GHOST_HOUSE_DOOR[0][1]) ||
                        (x/PX_PER_BLOCK == GHOST_HOUSE_DOOR[1][0] && y/PX_PER_BLOCK == GHOST_HOUSE_DOOR[1][1]));
        return at_door;
    }

    bool is_at_exit()
    {
        bool at_exit =  position[0]/PX_PER_BLOCK == GHOST_HOUSE_EXIT[0] && 
                        position[1]/PX_PER_BLOCK == GHOST_HOUSE_EXIT[1];
        return at_exit;
    }
    
    bool is_at_entrace()
    {
        bool at_entrance =  position[0]/PX_PER_BLOCK == GHOST_HOUSE_ENTRANCE[0] && 
                            position[1]/PX_PER_BLOCK == GHOST_HOUSE_ENTRANCE[1];
        return at_entrance;
    }

    void increment_dot_counter()
    {
        dot_counter++;
        // std::cout << "ghost " << (int)id << " counter: " << dot_counter << std::endl;
        if (dot_counter >= dot_threshold)
        {
            leaving_ghost_house = true;
            // std::cout << "ghost " << (int)id << " left home " << std::endl;
        }
    }

    void reverse_direction()    // only called when ghosts change modes
    {
        direction[0]*=-1;
        direction[1]*=-1;
    }

    void set_position_by_block(double x, double y)
    {
        position[0] = x*PX_PER_BLOCK;
        position[1] = y*PX_PER_BLOCK;
    }

    void set_direction(int dx, int dy)
    {
        direction[0] = dx;
        direction[1] = dy;
    }

    void set_speed(int speed)
    {
        if (speed > 0)
        {
            this->speed = speed;
            position[0] -= position[0]%speed;
            position[1] -= position[1]%speed;
        }
    }

    void set_color(int r, int g, int b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    void blink()
    {
        if (color[0] == color[1] && color[1] == color[2])
        {
            set_color(0, 0, 255);
        }
        else
        {
            set_color(255, 255, 255);
        }        
    }

    void reset_color()
    {
        set_color(DEFAULT_COLORS[id][0], DEFAULT_COLORS[id][1], DEFAULT_COLORS[id][2]);
    }

    const int* get_position() const
    {
        return position;
    }

    const int* get_direction() const
    {
        return direction;
    }

    const int* get_target() const
    {
        return target;
    }

    const int* get_scatter_target() const
    {
        return SCATTER_TARGETS[id];
    }

    int get_speed() const
    {
        return speed; 
    }

    bool is_in_ghost_house() const
    {
        return in_ghost_house;
    }

    bool is_leaving_ghost_house() const
    {
        return leaving_ghost_house;
    }

    void get_color(int* arr) const
    {
        arr[0] = color[0];
        arr[1] = color[1];
        arr[2] = color[2];
    }

};


#endif