#include "animation.h"
#include <iostream>

// to check of all the sprites as loaded from the given path
bool loadFileCheck(Animation& animation)
{
    if(animation.loadFood())
        return false;
    if(animation.loadGhosts())
        return false;
    if(animation.loadPacman())
        return false;
    if(animation.loadWords())
        return false;
    return true;
}

// to check if a food render is possible at a location which was
// visited by the pacman previously. The pacman would have eaten 
// the food previously so render food should return false the second
// time
bool checkFoodRender(Animation& animation, int pixelSize)
{
    // set the position as visited by pacman(so food eaten)
    animation.occupiedPixels[10][10] = 1;

    // try to render food there again should fail 
    if(animation.renderOneFood(int(10*pixelSize), 10*pixelSize) == false)
        return true;
    return false;
}

// to check if rendering pacman outside the map fails,
// will input a point outside the map and should fail
bool checkPacmanRender(Animation& animation, int height, int width)
{   
    // setting pacman state outside the map
    animation.pacmanState[0] = width + 1;
    animation.pacmanState[1] = height + 1;
    if(animation.renderPacman() == true)
        return false;

    // trying another position
    animation.pacmanState[0] = -1;
    if(animation.renderPacman() == true)
        return false;
    
    return true;
}

int main()
{
    int windowWid = 672;
    int windowHei = 900;
    int pixelSize = 24;
    Animation animation(windowWid, windowHei, pixelSize);
    if(loadFileCheck(animation) == false)
        return 1;

    if(checkFoodRender(animation, pixelSize) == false)
        return 1;

    if(checkPacmanRender(animation, windowHei, windowWid) == false)
        return 1;
        
    return 0;
}   