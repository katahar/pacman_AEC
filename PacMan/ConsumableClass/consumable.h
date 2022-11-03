#ifndef CONSUMABLE_H_IS_INCLUDED
#define  CONSUMABLE_H_IS_INCLUDED

#include <vector>
#include <cmath>

const double PI = 3.1415926;

class Consumable {
/*
    This is the class that controls the Consumables like the pellets.
    The pellets are distributed across the map and hence we need to store the location and also store the state.
    false -> not eaten, true -> eaten
*/
private:
    std::vector<int> loc; //Block coords. 
    bool isEaten;
    bool power;
public:
    Consumable();

    bool getIsEaten() const; //  returns whether the pellet is eaten or not
    bool getPower() const; // check whether the pellet has a power or not
    std::vector<int> getLocation() const; // return location of pellet
    
    void setIsEaten(const bool); // set the pellet to eaten (or not eaten)
    void setLocation(const int, const int); // set location of the pellet
    void setPower(const bool);
};

Consumable::Consumable(){
    loc.push_back(0);
    loc.push_back(0);
    isEaten = false;
    power = false;
}
bool Consumable::getIsEaten() const{
    return isEaten;
}
std::vector<int> Consumable::getLocation() const{
    return loc;
}
bool Consumable::getPower() const{
    return power; // true or false
}
void Consumable::setIsEaten(const bool val){
    isEaten = val;
}
void Consumable::setLocation(const int x, const int y){
    loc[0] = x;
    loc[1] = y;
}
void Consumable::setPower(const bool val){
    power = val;
}

#endif