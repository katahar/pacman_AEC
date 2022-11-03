#pragma once
#include <iostream>
#include "fssimplewindow.h"
#include "simplebitmap.h"
#include <vector>
#include <string>
#include <unordered_set>

class Animation{
	friend class map;
private:
	std::vector<std::string> ghostColorNames;
	std::vector<std::string> positionNames;
	std::vector<std::string> pacmanOrientationNames;
	std::vector<std::string> ghostModeNamesBlue;
	std::vector<std::string> ghostModeNamesWhite;
	std::vector<std::string> wordNames;
	std::vector<std::string> pacmanDeathNames;
	std::vector<std::string> ghostEyesNames;
	std::vector<std::string> scoreNames;
	std::string baseFileName;

	SimpleBitmap spriteBitmaps[4][4][2];
	SimpleBitmap spritePacman[4][5];
	SimpleBitmap spriteFood;
	SimpleBitmap spriteSuperPellet;
	SimpleBitmap spriteMap;
	SimpleBitmap spriteGhostModeBlue[2];
	SimpleBitmap spriteGhostModeWhite[2];
	SimpleBitmap spriteWords[6];
	SimpleBitmap spritePacmanDeath[10];
	SimpleBitmap spriteReady;
	SimpleBitmap spriteGhostEyes[4];
	SimpleBitmap spriteScores[4];
	SimpleBitmap spriteBigPacman[5];
	SimpleBitmap spriteGameOver;

	int screenWidth;
	int screenHeight;
	int pixelSize;
	int pixelSize2 = 30;
	
	int livesHeight = 192;
	bool mode = false;

public:
	int blink_counter = 0;
	int currState[4][2]; 
	int pacmanState[2];
	int pacmanOrientation[2] = {2, 0};
	std::vector<std::vector<int>> occupiedPixels;
	int wordX[6] = {160, 220, 260, 300, 350, 740};
	int wordY[3] = {50, 40, 80};
	int livesRemaining = 3;
	bool isFirstStep = true;

	Animation(int width, int height, int pixel_size);
	bool loadGhosts();
	bool loadPacman();
	bool loadFood();
	void loadMap();
	bool loadWords();
	bool loadScores();

	void removeGhostMode();
	bool isValid(int x, int y);
	void initialAnimation();
	void pacmanDeathAnimation();
	void updateGhosts(std::vector<int> nextDirection);
	void updateOneGhost(int ghostNo, int nextDirection);
	void levelUpAnimation();
	
	void renderGhosts(std::vector<int>&& nx, std::vector<int>&& ny);
	bool renderPacman();
	void renderFood(int, int);
	bool renderOneFood(int, int);
	void renderMap();
	void renderWords(int sleep);
	void renderSuperPellet(int x, int y);
	void renderPacManLives();
	void assignTextPos();
	void renderOneGhost(int ghostNo, int x, int y, int mode, int direction);
	void renderReady();
	void renderScores(int scoreNo);
	void renderBigPacman();
	void renderGameOver();
	void resetAnimation();

	std::vector<int> blockToPixelCoords(int blockX, int blockY);
	void setPacManState(int x, int y, int orien1);
};	