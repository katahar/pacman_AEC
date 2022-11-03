#include <string>
#include <iostream>
#include "map.h"

bool transformCoordsTest(Map& m, double px, double py){
    /*! Test to check the pixel to block and block to pixel functions !*/

    int blockX, blockY;
    double wx, wy;
    m.pixelToBlockCoords(px, py, blockX, blockY); // convert pixel to block
    m.blockToPixelCoords(wx, wy, blockX, blockY); // convert block back to pixel
    
    if((wx <= px + m.getBlockWid() || wx >= px - m.getBlockWid()) && (wy <= px + m.getBlockWid() || wy >= py - m.getBlockWid()) ){ // check if within 1 block width and height
        return true;
    }
    return false;
}
bool checkPelletTest(Map& m){
    int x = 21; int y = 24; // no wall so map should return a 0

    if(1 == m.getMapValue(x, y)){
        return false;
    }
    return true;
}
bool checkWallTest(Map& m){

    int x = 14; int y = 10; // wall so map should return a 1 (wall)
    // std::cout << m.getMapValue(x, y);
    if (1 == m.getMapValue(x, y)){
        return true;
    }    
    return false;
}

int main(){
    int windowWid = 672;
    int windowHei = 900;

    Map m;

    double px = std::rand() % windowWid;
    double py = std::rand() % windowHei;

    if(false == transformCoordsTest(m, px, py)){
        return 1;
    }
    if(false == checkPelletTest(m)){
        return 1;
    }
    // if(false == checkWallTest(m)){
    //     return 1;
    // }
    return 0;
}