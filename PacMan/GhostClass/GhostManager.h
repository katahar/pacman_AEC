#ifndef GHOSTMANAGER_IS_INCLUDED
#define GHOSTMANAGER_IS_INCLUDED

#include "Ghost.h"
#include "GhostParams.h"
/*
Ghost 0-Blinky  (red)   : target PacMan (scatter top right)
Ghost 1-Pinky   (pink)  : target 2 tiles ahead of direction of PacMan (scatter top left)
Ghost 2-Inky    (cyan)  : target the tile at 2 times the directional distance from Blinky to PacMan (scatter bottom right)
Ghost 3-Clyde   (orange): target PacMan when at least 8 tiles away from PacMan, otherwise target scatter location (scatter bottom left)
*/
class GhostManager
{
private:
    Ghost ghosts[N];
    int move_counter;               // acts as delay to make ghosts slower (via lower fps)
    const int* mode_timer;          // when to switch mode
    int mode_counter;               // track frames since switched mode
    Mode global_mode;         
    int ghosts_eaten;
    
public:
    // GhostManager(void);
    // void set_scatter_targets(void);
    // void set_home_positions(void);
    // void set_colors(void);

    // void update(const Map &map, double pacX, double pacY, int dirX, int dirY, bool chase);
    // void draw(int blockWid);
    // void draw_targets(const Map &map);
    // void reset(void);

    // Ghost* get_ghosts(void);
    // void get_positions(int** arr) const;

    GhostManager(void)
    {
        for (int i = 0; i < N; ++i)
        {
            ghosts[i] = Ghost(i);
        }
        reset();
    }

    void reset(void)
    {
        for (int i = 0; i < 4; ++i)
        {
            ghosts[i].reset();
        }
        ghosts_eaten = 0;
        move_counter = 0;
        mode_counter = 0;
        mode_timer = MODE_TIMERS;
        global_mode = SCATTER;
    }

    // pacX and pacY in blocks (pacman's x and y center position as block location)
    void update(const Map &map, int pacX, int pacY, int dirX, int dirY, bool frightened)
    {
        if (*mode_timer == -1)
        {
            goto skip_mode_change;
        }
        ++mode_counter;
        if (mode_counter >= *mode_timer)
        {
            mode_counter = 0;
            ++mode_timer;
            if (global_mode == SCATTER)
            {
                global_mode = CHASE;
            }
            else 
            {
                global_mode = SCATTER;
            }
            for (int i = 0; i < 4; ++i)
            {
                ghosts[i].update_mode(global_mode);
                // ghosts[i].switch_mode();
            }
            // std::cout << "ghosts changed mode" << std::endl;
        }

        skip_mode_change:
        if (frightened)
        {
            for (int i = 0; i < 4; ++i)
            {
                ghosts[i].update_mode(FRIGHTENED);
            }
            ghosts_eaten = 0;
            // std::cout << "ghosts frightened" << std::endl;
        }


        // move once every MOVE_DELAY frames
        ++move_counter;
        if (move_counter < MOVE_DELAY)
        {
            return;
        }
        move_counter = 0;

        // update ghost chase targets
        ghosts[0].update_chase_target(pacX, pacY);
        ghosts[1].update_chase_target(pacX + 2*dirX, pacY + 2*dirY);

        const int *blinkyPos = ghosts[0].get_position();
        ghosts[2].update_chase_target(2*pacX - (blinkyPos[0]/PX_PER_BLOCK), 2*pacY - (blinkyPos[1]/PX_PER_BLOCK));

        if (ghosts[3].dist_from_position_to(pacX*PX_PER_BLOCK, pacY*PX_PER_BLOCK) < 8)
        {
            const int *scat_targ = ghosts[3].get_scatter_target();
            ghosts[3].update_chase_target(scat_targ[0], scat_targ[1]);
        }
        else
        {
            ghosts[3].update_chase_target(pacX, pacY);
        }


        // call ghost update function
        for (int i = 0; i < 4; ++i)
        {
            ghosts[i].update(map);
        }
    }

    // pacX and pacY in pixels
    int check_collision(int pacX, int pacY, bool &pacman_killed)
    {
        // update collision even when ghost is in between moves
        for (int i = 0; i < 4; ++i)
        {
            int collisionCheck = ghosts[i].collide_with_pacman(pacX, pacY);
            if (collisionCheck == 0)
            {
                return ++ghosts_eaten;
            }
            else if (collisionCheck == 1)
            {
                pacman_killed = true;
            }
        }
        return 0;
    }

    void render(Animation a) const 
    {
        for (int i = 0; i < 4; ++i)
        {
            ghosts[i].render(a);
        }
    }

    void draw()
    {
        for (int i = 0; i < 4; ++i)
        {
            ghosts[i].draw();
        }
    }

    void draw_targets(const Map &map)
    {
        int col[3];
        for (int i = 0; i < 4; ++i)
        {
            ghosts[i].get_color(col);
            const int* targ = ghosts[i].get_target();
            // std::cout << targ[0] << ", " << targ[1] << std::endl;
            map.FillCell(targ[0], targ[1], col[0], col[1], col[2]);
        }
    }

    Ghost* get_ghosts(void)
    {
        return ghosts;
    }

    void increment_ghost_dot_counter()
    {
        for (int i = 0; i < N; ++i)
        {
            if (ghosts[i].is_in_ghost_house() && !ghosts[i].is_leaving_ghost_house())
            {
                ghosts[i].increment_dot_counter();
                return;
            }
        }
    }

    // void get_positions(int** arr) const
    // {
    //     for (int i = 0; i < 4; ++i)
    //     {
    //         const int* pos = ghosts[i].get_position();
    //         arr[i][0] = pos[0];
    //         arr[i][1] = pos[1];
    //     }
    // }
};

#endif