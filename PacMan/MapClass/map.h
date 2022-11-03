#ifndef MAP_H_IS_INCLUDED
#define  MAP_H_IS_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "consumable.h"
#include "fssimplewindow.h"
#include "animation.h"

class Map{
/*
    This class is responsible for generating the map and also for working with the pellets and the locations of the pellets and ghosts.
    Reads the mapData from a file. The one shown below is a sample only.

    Unit tests:
    1) transformCoordsTest - transform coords from pixel to block and back to pixel
	2) checkPelletTest - Check pellet and power pellet
    3) checkWallTest - Test the getMapBlock function to check if it is returning the correct value at wall location
*/
private:
    const int blockWid = 24;
    const int numBlocksX = 28;
    const int numBlocksY = 36;

    const int windowWid = blockWid * numBlocksX;
    const int windowHei = blockWid * numBlocksY;   

    std::string fileName = "maps/map1.txt";
    std::string mapInit;
    std::string curMap;

    Consumable* pellets = nullptr;
    Consumable* powerPellets = nullptr;
    int* map = nullptr;
    char* mapData = nullptr;    
    int numPellets = 0;

    long long int stateCount = 0;
    bool blinkMap = false;

    int blue[3] = {20, 70, 230}; int lineWidth1 = 10;
    int black[3] = {0, 0, 0}; int lineWidth2 = 5;
    int white[3] = {255, 255, 255};
    int* color = blue;

    int PacManX, PacManY; // Block Coords

public:
    
    // Transformation functions
    int get1DIndex(int x, int y) const{
        /*! Convert a 2D index to a 1D index to get values from a 1D vector or array !*/
            return y*numBlocksX + x; 
    }
    void blockToPixelCoords(double& wx, double& wy,const int blockX, const int blockY) { // ! - potentionally change block coords to double
        /*! Convert block to pixel coords.
            Returns the top-left pixel values of the block !*/

        wx = blockWid * blockX;
        wy = blockWid * blockY;
    }
    void pixelToBlockCoords(double px, double py, int& blockX, int& blockY){
        /*! Convert pixel to block coords.
            Origin is top left of screen (0, 0) !*/
        
        blockY = py / blockWid;
        blockX = px / blockWid;
    }
    void getBlockCenter(double px, double py, double& cx, double& cy){
        /*! get block center in pixels.
            Steps = Pixel coords -> Block coords -> get top left of block in pixels -> return center in pixels !*/

        // std::cout<< "\n\nGET BLOCK CENTER FUNCTION " ;
        // std::cout<< "Originally provided pixel X  \n" << px;
        // std::cout<< "Originally provided pixel Y  \n" << py;

        int bx, by;
        pixelToBlockCoords(px, py, bx, by);
        // std::cout<< "Converted x to block  \n" << px;
        // std::cout<< "Originally provided pixel Y  \n" << py;

        double topLPX, topLPY; // top left of block in pixels
        blockToPixelCoords(topLPX, topLPY, bx, by);

        cx = topLPX + blockWid/2;
        cy = topLPY + blockWid/2;
        // std::cout<< "----------------------\n\n " ;
    }

    // Const Pointers
    Consumable* getPelletsPointer(void) const {
        return pellets;
    }
    Consumable* getPowerPelletsPointer(void) const {
        return powerPellets;
    }
    int* getMapPointer(void) const {
        return map;
    }

    // Editable Map pointer
    int* getEditableMapPointer(void){
        return map;
    }

    // Access methods -> All args in Block coords
    unsigned int getMapBlock(int x, int y){ // Gets the corresponding block at location (x,y) from the char array and returns as an int
        auto i = get1DIndex(x, y);
        return mapData[i];
    }
    int getMapValue(int x, int y) const{
        x = (x<0) ? 0 : x;
        x = (x>=numBlocksX) ? numBlocksX-1 : x;
        auto i = get1DIndex(x, y);
        return map[i];
    }
    Consumable getPellet(int x, int y, bool power) const{ // Helper function to access the pellet at a particular location   
        // power = true when checking for powerpellet
        auto i = get1DIndex(x, y);
        if (power){
            return powerPellets[i];
        }  
        return pellets[i];
    }
    Consumable* getEditablePellet(int x, int y, bool power){ // Helper function to give modifiable access the pellet at a particular location    
        // power = true when checking for powerpellet
        auto i = get1DIndex(x, y);
        if (power){
            return &powerPellets[i];
        }  
        return &pellets[i];
    }
    
    int getMapHei() const {
        return windowHei;
    }
    int getMapWid() const {
        return windowWid;
    }
    int getNumBlocksX() const{
        return numBlocksX;
    }
    int getNumBlocksY() const{
        return numBlocksY;
    }
    double getBlockWid() const{
        return blockWid;
    }
    int getNumPellets() const{
        return numPellets;
    }

    // For demo ---------
    int getPacmanX() const{
        return PacManX;
    }
    int getPacmanY() const{
        return PacManY;
    }
    void updatePacmanLoc(const int x, const int y) {
        PacManX = x;
        PacManY = y;
    }
    // ------------------

    void FillCell(int x, int y, int r, int g, int b) const
    {
        glColor3ub(r, g, b);
        glBegin(GL_QUADS);
        glVertex2i( x   *blockWid,  y   *blockWid);
        glVertex2i((x+1)*blockWid,  y   *blockWid);
        glVertex2i((x+1)*blockWid, (y+1)*blockWid);
        glVertex2i( x   *blockWid, (y+1)*blockWid);
        glEnd();
    }

    void readMapFile(){   
        if (pellets!=nullptr || powerPellets!=nullptr || map!=nullptr || mapData != nullptr){
            CleanUp();
        }
        FsChangeToProgramDir();
        std::ifstream in(fileName.c_str(), std::ios::in);
        
        std::string str;
        if (in.is_open())
        {
            while (in.good())
            {
                std::getline(in, str);
                for (auto x : str){
                    if (x != '\n'){
                        mapInit.push_back(x);
                    }
                }
            }
            in.close();
        }
        else
        {
            std::cout << "Error opening file here" << std::endl;
        } 

        mapData = const_cast<char*> (mapInit.c_str());
    }
    
    void readMapFile(std::string fName){
        if (pellets!=nullptr || powerPellets!=nullptr || map!=nullptr || mapData != nullptr){
            CleanUp();
        }
        
        FsChangeToProgramDir();
        std::ifstream in(fName.c_str(), std::ios::in);
        
        std::string str;
        if (in.is_open())
        {
            while (in.good())
            {
                std::getline(in, str);
                for (auto x : str){
                    if (x != '\n'){
                        mapInit.push_back(x);
                    }
                }
            }
            in.close();
        }
        else
        {
            std::cout << "Error opening file" << std::endl;
        }

        mapData = const_cast<char*> (mapInit.c_str());
    }

    Map(){
        curMap = fileName;
        readMapFile();

        InitializeMap();
    }

    void changeMapTo2(){
        curMap = "maps/map2.txt";
        readMapFile(curMap);
        InitializeMap();
    }
    void changeMapTo1(){
        curMap = "maps/map1.txt";
        readMapFile(curMap);
        InitializeMap();
    }

    Map(int w, int h){
        // curMap = fName;
        // readMapFile(fName);

        // InitializeMap();
        
        // windowWid = w;
        // windowHei = h;
        // mapHei = windowHei - 156;
        // mapWid = windowWid;
        // numBlocksX = (int)(mapWid / blockWid);
        // numBlocksY = (int)(mapHei / blockWid);

        // curMap = fileName;
        // readMapFile();

        // pellets = new Consumable[numBlocksX * numBlocksY];
        // powerPellets = new Consumable[numBlocksX * numBlocksY];
        // map = new int[numBlocksX * numBlocksY];
        // for(int i=0;i<numBlocksX*numBlocksY;++i){
        //     pellets[i].setIsEaten(false);
        //     pellets[i].setLocation(-1,-1);
        //     powerPellets[i].setIsEaten(false);
        //     powerPellets[i].setPower(true);
        //     powerPellets[i].setLocation(-1,-1);
        //     map[i] = 0;
        // }

        // InitializeMap();
    }
    Map(std::string fName){
        
        curMap = fName;
        readMapFile(fName);

        InitializeMap();
    }
    void InitializeMap(){   
        numPellets = 0; 
        pellets = new Consumable[numBlocksX * numBlocksY];
        powerPellets = new Consumable[numBlocksX * numBlocksY];
        map = new int[numBlocksX * numBlocksY];
        for(int i=0;i<numBlocksX*numBlocksY;++i){
            pellets[i].setIsEaten(false);
            pellets[i].setLocation(-1,-1);
            powerPellets[i].setIsEaten(false);
            powerPellets[i].setPower(true);
            powerPellets[i].setLocation(-1,-1);
            map[i] = 0;
        }

        for(int blockY=0;blockY<numBlocksY;++blockY){
            for(int blockX=0;blockX<numBlocksX;++blockX){

                auto ind = get1DIndex(blockX, blockY);
                auto block = getMapBlock(blockX, blockY);

                if (block == 'H' || block == 'V' || block == 'C' || block == 'N' || block == 'G'){
                    map[ind] = 1;
                }
                else if (block == 'F'){
                    auto pInd = get1DIndex(blockX, blockY);
                    pellets[pInd].setLocation(blockX, blockY);
                    numPellets += 1;
                }
                else if (block == 'O'){
                    auto powerInd = get1DIndex(blockX, blockY);
                    powerPellets[powerInd].setLocation(blockX, blockY);
                    numPellets += 1;
                }
            }
        }
        // std::cout << numPellets << std::endl;
    }

    void CleanUp(){
        if (pellets!=nullptr){
            delete[] pellets;
            pellets = nullptr;
        }
        if (powerPellets!=nullptr){
            delete[] powerPellets;
            powerPellets = nullptr;
        }
        if(map!=nullptr){
            delete[] map;
            map = nullptr;
        }
        mapData = nullptr;
        mapInit.clear();
    }

    bool checkCollisionWall(int px, int py, std::string direction){

        int bx, by;
        pixelToBlockCoords(px, py, bx, by);

        if (direction == "UP" || direction == "up"){
            if (getMapValue(bx, by-1)){
                return true;
            }
            return false;
        }
        else if (direction == "DOWN" || direction == "Down" || direction == "down"){
            
            if (getMapValue(bx, by+1)){
                    return true;
                }
            return false;
        }
        else if (direction == "LEFT" || direction == "Left" || direction == "left"){
            
            if (getMapValue(bx-1, by)){
                return true;
            }
            return false;
        }
        else if (direction == "RIGHT" || direction == "Right" || direction == "right"){
            
            if (getMapValue(bx+1, by)){
                return true;
            }
            return false;        
        }
        else{
            exit(0);
            return false;
        }
        return false;
    }
    bool checkLocForWall(int x, int y){
        if (getMapValue(x, y)){
            return true;
        }
        return false;
    }

    void MapBlink(bool val){
        blinkMap = val;
    }
    long long int getBlinkCount(){
        return stateCount;
    }
    bool getMapBlink(){
        return blinkMap;
    }

    void RenderMap(Animation& animation){
        
        
        double wx, wy; // window coords

        if(blinkMap){
            if (stateCount % 2 == 0) {
                color = white;
            }
            else{
                color = blue;
            }
        }
        else{
            color = blue;
            stateCount = 0;
        }
        stateCount += 1;

        for(int blockY=0;blockY<numBlocksY;++blockY){
            for(int blockX=0;blockX<numBlocksX;++blockX){
                
                blockToPixelCoords(wx, wy, blockX, blockY);
                auto block = getMapBlock(blockX, blockY);

                std::string c_orientation = ""; std::string t_orientation="";

                auto blockBottom = getMapBlock(blockX, blockY + 1);
                auto blockTop = getMapBlock(blockX, blockY - 1);
                auto blockRight = getMapBlock(blockX + 1, blockY);
                auto blockLeft = getMapBlock(blockX - 1, blockY);
                
                if(animation.isFirstStep == true){
                    animation.renderReady();
                    //animation.isFirstStep = false;
                }

                switch(block){
                    case 'H':                        
                        DrawHorizontal(wx, wy, color, lineWidth1);
                        DrawHorizontal(wx, wy, black, lineWidth2);
                        break;
                    case 'V':
                        DrawVertical(wx, wy, color, lineWidth1);
                        DrawVertical(wx, wy, black, lineWidth2);
                        break;
                    case 'C':
                        if (blockBottom && blockRight && blockBottom=='V' && blockRight=='H') { 
                            c_orientation = "br";
                        }
                        else if (blockBottom && blockLeft && blockBottom == 'V' && blockLeft == 'H'){ 
                            c_orientation = "bl";
                        }
                        else if (blockTop && blockLeft && blockTop=='V' && blockLeft=='H') { 
                            c_orientation = "tl";                    
                        }
                        else if (blockTop && blockRight && blockTop == 'V' && blockRight=='H'){ 
                            c_orientation = "tr";
                        }
                        else if (blockTop && blockRight && blockTop=='V' && blockRight=='C') {
                            c_orientation = "tr";
                        }
                        else if (blockTop && blockLeft && blockTop == 'V' && blockLeft =='C') {
                            c_orientation = "tl";
                        }
                        else if (blockTop && blockRight && blockTop == 'C' && blockRight == 'H'){
                            c_orientation = "tr";
                        }
                        else if (blockBottom && blockRight && blockBottom == 'C' && blockRight == 'H'){
                            c_orientation = "br";
                        }
                        else if (blockTop && blockLeft && blockTop == 'C' && blockLeft == 'H'){
                            c_orientation = "tl";
                        }
                        else if (blockBottom && blockLeft && blockBottom == 'C' && blockLeft == 'H'){
                            c_orientation = "bl";
                        }
                        else if (blockBottom && blockRight && blockBottom=='V' && blockRight=='C'){
                            c_orientation = "br";
                        }
                        else if (blockBottom && blockLeft && blockBottom=='V' && blockLeft=='C'){
                            c_orientation = "bl";
                        }
                        
                        DrawCorner(wx, wy, c_orientation, color, lineWidth1);
                        DrawCorner(wx, wy, c_orientation, black, lineWidth2);
                        break;
                    case 'F':
                        if (checkLocForPellet(blockX, blockY)){
                            // DrawPellet(wx, wy);
                            //if(!checkLocForWall(blockX, blockY))
                            animation.renderOneFood(wx, wy + getBlockWid());
                        }
                        break;
                    case 'O':
                        if (checkLocForPowerPellet(blockX, blockY)){
                            if(animation.blink_counter > 5 && animation.occupiedPixels[int(wx / getBlockWid())][int((wy+getBlockWid())/getBlockWid())] == 0)
                                DrawPowerPellet(wx, wy);
                                if (animation.blink_counter > 10)
                                {
                                    animation.blink_counter = 0;
                                }
                            //animation.renderSuperPellet(wx, wy + getBlockWid());
                        }
                        break;
                    case 'G':
                        int pink[3] = {255, 105, 180};
                        DrawHorizontal(wx, wy, pink, lineWidth1);
                        DrawHorizontal(wx, wy, black, lineWidth2);
                        break;
                }
                // if(animation.isFirstStep == true){
                //     animation.renderGameOver();
                //     animation.isFirstStep = false;
                // }
                // animation.renderGameOver();
                //animation.renderOneFood(wx, wy + getBlockWid());
            }
        }
        animation.blink_counter += 1;
        // FsSwapBuffers();
    }

    void DrawVertical(double X, double Y, const int color[], const int linewidth){

        glLineWidth(linewidth);
        glColor3ub(color[0], color[1], color[2]);

        glBegin(GL_LINES);
        glVertex2d(X + blockWid/2, Y);
        glVertex2d(X + blockWid/2, Y + blockWid);
        glEnd();
    }
    void DrawHorizontal(double X, double Y, const int color[], const int linewidth){
        
        glLineWidth(linewidth);
        glColor3ub(color[0], color[1], color[2]);
        glBegin(GL_LINES);
        glVertex2d(X, Y + blockWid/2);
        glVertex2d(X + blockWid, Y + blockWid/2);
        glEnd();
    }
    void DrawHorizontalHalf(double X, double Y, std::string side){
        
        glBegin(GL_LINES);
        if (side == "r"){
            glVertex2d(X + blockWid/2, Y + blockWid/2);
            glVertex2d(X + blockWid, Y + blockWid/2);
        }
        else if(side=="l"){
            glVertex2d(X + blockWid/2, Y + blockWid/2);
            glVertex2d(X, Y + blockWid/2);
        }
        glEnd();
    }
    void DrawVerticalHalf(double X, double Y, std::string side){

        glBegin(GL_LINES);
        if (side == "t"){
            glVertex2d(X + blockWid/2, Y + blockWid/2);
            glVertex2d(X + blockWid/2, Y);
        }
        
        else if (side == "b"){
            glVertex2d(X + blockWid/2, Y + blockWid/2);
            glVertex2d(X + blockWid/2, Y + blockWid);
        }
        glEnd();
    }
    void DrawCorner(double X, double Y, std::string orientation, const int color[], const int linewidth){
        
        // glBegin(GL_LINES);
        glColor3ub(color[0], color[1], color[2]);
        glLineWidth(linewidth);
        
        if (orientation == "br") { // bottom right
            DrawHorizontalHalf(X, Y, "r");
            DrawVerticalHalf(X, Y, "b");
        }
        else if (orientation == "bl"){ // bottom left
            DrawHorizontalHalf(X, Y, "l");
            DrawVerticalHalf(X, Y, "b");
        }
        else if (orientation == "tr"){ // top right
            DrawHorizontalHalf(X, Y, "r");
            DrawVerticalHalf(X, Y, "t");
        }
        else if (orientation == "tl"){ // top left
            DrawHorizontalHalf(X, Y, "l");
            DrawVerticalHalf(X, Y, "t");
        }
        // glEnd();
    }

    // Pellet-Map Functions

    void DrawPowerPellet(double X, double Y){
        
        double r = 7.5;
        glColor3ub(255, 255, 0);
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 64; ++i)
        {
            double a = (double)i * PI / 32.0;
            double c = std::cos(a);
            double s = std::sin(a);
            glVertex2d(X + blockWid/2 + c * r, Y + blockWid/2 + s * r); 
        }
        glEnd();
    }
    bool checkLocForPellet(int x, int y){
        auto p = getPellet(x, y, false);
        std::vector<int> pelletLoc = p.getLocation();

        if (pelletLoc[0] != -1 && pelletLoc[1] != -1){
            // pellet present at loc
            
            if (p.getIsEaten()){
                // eaten
                return false; // no pellet
            }
            return true;
        }
        return false;
    }
    

    bool checkLocForPowerPellet(int x, int y){
        auto p = getPellet(x, y, true);
        auto pelletLoc = p.getLocation();
        if (pelletLoc[0] != -1 && pelletLoc[1] != -1){
            if (p.getIsEaten()){
                // eaten
                return false; // no pellet
            }
            return true;
        }
        return false;
    }
    void eatPellet(int x, int y)
    {
        if (checkLocForPellet(x, y)){
            pellets[get1DIndex(x,y)].setIsEaten(true);
        }
        else if (checkLocForPowerPellet(x, y)) {
            powerPellets[get1DIndex(x,y)].setIsEaten(true);
        }
    }
    void eatPellet(int x, int y, bool power) // Fill in later. Args in blocks
    {
        if(!power)
        {
            pellets[get1DIndex(x,y)].setIsEaten(true);        
        }
        else
        {
            powerPellets[get1DIndex(x,y)].setIsEaten(true);        
        }

    }



    ~Map(){
        CleanUp();
    }

    // For demo ----------------------------------
    bool checkCollisionPacManWallUp(){
        if (getMapValue(PacManX, PacManY-1)){
            return false;
        }
        PacManY -= 1; //  just for initial testing. 
        return true;
    }
    bool checkCollisionPacManWallDown(){
        // check Collision here
        if (getMapValue(PacManX, PacManY+1)){
            return false;
        }
        PacManY += 1; //  just for initial testing. 
        return true;
    }
    bool checkCollisionPacManWallRight(){

        if (getMapValue(PacManX+1, PacManY)){
            return false;
        }
        PacManX += 1; //  just for initial testing. 
        return true;
    }
    bool checkCollisionPacManWallLeft(){
        if (getMapValue(PacManX-1, PacManY)){
            return false;
        }
        PacManX -= 1; //  just for initial testing. 
        return true;
    }
// For demo -----------------------------------

};
#endif