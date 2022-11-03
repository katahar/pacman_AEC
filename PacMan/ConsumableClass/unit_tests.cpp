#include "consumable.h"
#include <vector>
#include <cstdlib>

bool locationTest(Consumable& c){
    int locx = std::rand() % 29;
    int locy = std::rand() % 31;

    c.setLocation(locx, locy);

    auto pos = c.getLocation();

    if (pos[0] == locx && pos[1] == locy){
        return true;
    }
    return false;
}

bool powerTest(Consumable& c){
    int p = std::rand() % 1;

    if (p){
        c.setPower(true);
        if(true == c.getPower()){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        c.setPower(false);
        if (true == c.getPower()){
            return false;
        }
        else{
            return true;
        }
    }
}

bool eatenTest(Consumable& c){
    int e = std::rand() % 1;

    if (e){
        c.setIsEaten(true);
        if(true == c.getIsEaten()){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        c.setIsEaten(false);
        if (true == c.getIsEaten()){
            return false;
        }
        else{
            return true;
        }
    }
}

int main(){

    Consumable c;

    if (false == locationTest(c)){
        return 1;
    }
    if (false == powerTest(c)){
        return 1;
    }
    if (false == eatenTest(c)){
        return 1;
    }

    return 0;
}