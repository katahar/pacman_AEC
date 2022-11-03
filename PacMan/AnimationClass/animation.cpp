// Class definition for all the animation functionalities
#include "animation.h"

Animation:: Animation(int width, int height, int pixel_size): screenHeight(height), screenWidth(width),
															  pixelSize(pixel_size)
{
	FsChangeToProgramDir();
	ghostColorNames = {"red", "pink", "blue", "orange"};
	// each color has 8 positions, 2 each for up, down, left, right motion. For each motion
	// one sprite with legs near and other with legs far away
	positionNames = {"down_back", "down_for", "left_back", "left_for",
					 "right_back", "right_for", "up_back", "up_for"};
	pacmanOrientationNames = {"down_full", "down", "down_big", "down_again2", "down_again", 
							  "left_full", "left", "left_big", "left_again2", "left_again",
							  "right_full", "right", "right_big", "right_again2", "right_again",
							  "up_full", "up", "up_big", "up_again2", "up_again"};
	ghostModeNamesBlue = {"fow_blue", "back_blue"};
	ghostModeNamesWhite =  {"fow_white", "back_white"};
	ghostEyesNames = {"down", "left", "right", "up"};
	wordNames = {"character", "cyan", "orange", "pink", "red", "start"};
	pacmanDeathNames = {"first", "second", "third",
						"fourth", "fifth", "sixth",
						"seventh", "eight", "ninth",
						"tenth", "eleventh"};
	scoreNames = {"200", "400", "800", "1600"};
	// base filename where all the sprites are present
	baseFileName = "sprites";//"/home/akshay/Downloads/Strange_Team_Name_Here/PacMan/sprites";
	for(int i=0;i<4;++i)
	{
		currState[i][0] = 0;
		currState[i][1] = 0;
	}
	pacmanState[0] = 0;
	pacmanState[1] = 0;
	occupiedPixels = std::vector<std::vector<int>>(int(screenWidth/pixelSize), 
								 std::vector<int>(int(screenHeight/pixelSize), 0));
}

bool Animation::isValid(int x, int y)
{
	if(x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
		return false;
	return true;
}

bool Animation::loadGhosts()
{
	int i = 0;
	for(auto color: ghostColorNames){
		for(auto position: positionNames){
			std::string temp  = baseFileName + "/" + color + "/" 
								+ position + "_" + std::to_string(pixelSize2) + ".png";
			char* temp_filename = const_cast<char*>(temp.data());
			bool isFileLoaded = spriteBitmaps[int(i/8)][int((i%8)/2)][int(i%2)].LoadPng(temp_filename);
			if(!isFileLoaded){
				std::cout<<" Ghost Sprite not loaded from the following filename,"
				"Please check the basefilename"
				"of line 17. For help refer Readme.txt\n Filename:"
				<<temp_filename<<"\n";
				return false;
			}
			spriteBitmaps[int(i/8)][int((i%8)/2)][int(i%2)].Invert();
			i += 1;
		}
	}
	i = 0;
	for(auto name: ghostModeNamesBlue){
		std::string temp = baseFileName + "/mode/ghost_" + name + "_" + 
						   std::to_string(pixelSize2) + ".png";
		char* temp_filename = const_cast<char*>(temp.data());
		bool isFileLoaded = spriteGhostModeBlue[i].LoadPng(temp_filename);
		if(!isFileLoaded)
			if(!isFileLoaded){
				std::cout<<"Mode Ghost Sprite not loaded from the following filename,"
				"Please check the basefilename"
				"of line 17. For help refer Readme.txt \n Filename:"
				<<temp_filename<<"\n";
				return false;
			}
		spriteGhostModeBlue[i].Invert();
		i += 1; 
	}
	i = 0;
	for(auto name: ghostModeNamesWhite){
		std::string temp = baseFileName + "/mode/ghost_" + name + "_" + 
						   std::to_string(pixelSize2) + ".png";
		char* temp_filename = const_cast<char*>(temp.data());
		bool isFileLoaded = spriteGhostModeWhite[i].LoadPng(temp_filename);
		if(!isFileLoaded)
			if(!isFileLoaded){
				std::cout<<"Mode Ghost Sprite not loaded from the following filename,"
				"Please check the basefilename"
				"of line 17. For help refer Readme.txt \n Filename:"
				<<temp_filename<<"\n";
				return false;
			}
		spriteGhostModeWhite[i].Invert();
		i += 1; 
	}
	i = 0;
	for(auto name: ghostEyesNames){
		std::string temp = baseFileName + "/eyes/" + name + "_" + 
						   std::to_string(pixelSize) + ".png";
		char* temp_filename = const_cast<char*>(temp.data());
		bool isFileLoaded = spriteGhostEyes[i].LoadPng(temp_filename);
		if(!isFileLoaded){
			std::cout<<"Mode Ghost Sprite not loaded from the following filename,"
			"Please check the basefilename"
			"of line 17. For help refer Readme.txt \n Filename:"
			<<temp_filename<<"\n";
			return false;
		}
		spriteGhostEyes[i].Invert();
		i += 1;
	}

	std::cout<<"Ghost sprites Loaded successfully\n";
	return true;
}

bool Animation::loadPacman()
{
	//down = 0, left = 1, right = 2, up = 3
	int i = 0;
	for(auto pacmanOrientation:pacmanOrientationNames){
		std::string temp  = baseFileName + "/" + "pacman" + "/" + 
							pacmanOrientation + "_" + std::to_string(pixelSize2) + ".png";
		char* temp_filename = const_cast<char*>(temp.data());
		bool y = spritePacman[int(i/5)][i%5].LoadPng(temp_filename);
		if(!y){
			std::cout<<"Pacman Sprite not loaded from the following filename,"
				"Please check the basefilename "
				"of line 17. For help refer Readme.txt\n Filename:"
				<<temp_filename<<"\n";
			return false;
		}
		spritePacman[int(i/5)][i%5].Invert();
		++i;
	}
	i = 0;
	for(auto deathName: pacmanDeathNames){
		std::string temp  = baseFileName + "/" + "pacman" + "/" + 
							deathName + "_" + std::to_string(pixelSize2) + ".png";
		char* temp_filename = const_cast<char*>(temp.data());
		bool y = spritePacmanDeath[i].LoadPng(temp_filename);
		if(!y){
			std::cout<<"Pacman Sprite not loaded from the following filename,"
				"Please check the basefilename "
				"of line 17. For help refer Readme.txt\n Filename:"
				<<temp_filename<<"\n";
			return false;
		}
		spritePacmanDeath[i].Invert();
		++i;
	}
	i = 10;
	while(i <= 14)
	{
		std::string temp  = baseFileName + "/" + "pacman" + "/" + 
							pacmanOrientationNames[i] + "_" + std::to_string(2*pixelSize) + ".png";
		char* temp_filename = const_cast<char*>(temp.data());
		bool y = spriteBigPacman[i-10].LoadPng(temp_filename);
		if(!y){
			std::cout<<"Big Pacman Sprite not loaded from the following filename,"
				"Please check the basefilename "
				"of line 17. For help refer Readme.txt\n Filename:"
				<<temp_filename<<"\n";
			return false;
		}
		spriteBigPacman[i-10].Invert();
		++i;
	}
	std::cout<<"Pacman Sprites Loaded successfully\n";
	return true;
}

bool Animation::loadFood()
{
	std::string temp = baseFileName + "/food/" +  "food_" + std::to_string(24) + ".png"; 
	char* temp_filename = const_cast<char*>(temp.data());
	bool y = spriteFood.LoadPng(temp_filename);
	if(!y){
		std::cout<<"Food/Pellet Sprite not loaded from the following filename,"
			"Please check the basefilename "
			"of line 17. For help refer Readme.txt\n Filename:"
			<<temp_filename<<"\n";
		return false;
	}
	spriteFood.Invert();

	temp = baseFileName + "/food/" +  "square_pellet_" + std::to_string(24) + ".png"; 
	char* temp_filename_2 = const_cast<char*>(temp.data());
	y = spriteSuperPellet.LoadPng(temp_filename_2);
	if(!y){
		std::cout<<"Super Pellet Sprite not loaded from the following filename,"
			"Please check the basefilename "
			"of line 17. For help refer Readme.txt\n Filename:"
			<<temp_filename_2<<"\n";
		return false;
	}
	spriteSuperPellet.Invert();
	std::cout<<"Food sprites loaded successfully\n";
	return true;
}

void Animation::loadMap()
{
	std::string temp  = "map.png";
	char* temp_filename = const_cast<char*>(temp.data());
	spriteMap.LoadPng(temp_filename);
	spriteMap.Invert();
}

bool Animation::loadWords()
{
	int i = 0;
	// std::cout<<"Fo";
	for(auto name: wordNames)
	{
		std::string temp = baseFileName + "/words/" + name + "_" + std::to_string(24) + ".png";
		char* temp_filename = const_cast<char*>(temp.data());
		bool y = spriteWords[i].LoadPng(temp_filename);
		if(!y)
		{
			std::cout<<"Words png file not loaded from the following filename,"
				"Please check the basefilename "
				"of line 17. For help refer Readme.txt\n Filename:"
				<<temp_filename<<"\n";
			return false;
		}
		spriteWords[i].Invert();
		++i;
	}
	std::string temp = baseFileName + "/ready_" +  std::to_string(24) + ".png";
	char* temp_filename = const_cast<char*>(temp.data());
	bool y = spriteReady.LoadPng(temp_filename);
	spriteReady.Invert();
	if(!y){
		std::cout<<"Ready sprite not loaded\n "<<temp_filename<<"\n";
		return false;
	}

	temp = baseFileName + "/gameover_" +  std::to_string(24) + ".png";
	temp_filename = const_cast<char*>(temp.data());
	y = spriteGameOver.LoadPng(temp_filename);
	spriteGameOver.Invert();
	if(!y){
		std::cout<<"Game Over sprite not loaded\n "<<temp_filename<<"\n";
		return false;
	}

	std::cout<<"Words sprites loaded successfully\n";
	return true;
}

bool Animation::loadScores()
{	
	int i = 0;
	// std::cout<<"Fo";
	for(auto name: scoreNames)
	{
		std::string temp = baseFileName + "/scores/" + name + "_" + std::to_string(24) + ".png";
		char* temp_filename = const_cast<char*>(temp.data());
		bool y = spriteScores[i].LoadPng(temp_filename);
		spriteScores[i].Invert();
		if(!y)
		{
			std::cout<<"Scores png file not loaded from the following filename,"
				"Please check the basefilename "
				"of line 17. For help refer Readme.txt\n Filename:"<< temp_filename<<"\n";
			return false;
		}
		i += 1;
	}
	std::cout<<"Score sprites sprites loaded successfully\n";
	return true;
}

void Animation::initialAnimation(){
	glViewport(0, 0, screenWidth, screenHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	renderWords(1500);
	FsPollDevice();
	auto key = FsInkey();
	if(key == FSKEY_SPACE || key == FSKEY_ESC){
		mode = false;
		return;
	}
	for(;;){
		key = FsInkey();
		if(key == FSKEY_SPACE || key == FSKEY_ESC){
			mode = false;
			return;
		}
		mode = false;
		int x = screenWidth - pixelSize;
		int y = screenHeight - 10*pixelSize;
		pacmanState[0] = x;
		pacmanState[1] = y;
		std::vector<int> ghostX = {2*pixelSize2, 3*pixelSize2, 4*pixelSize2, 5*pixelSize2};
		std::vector<int> ghostY = {y, y, y, y};
		int direction = -1;

		for(;;){
			FsPollDevice();
        	key = FsInkey();
			if(key == FSKEY_SPACE || key == FSKEY_ESC){
				mode = false;
				return;
			}
			if(x >= screenWidth)
				break;

			if(x <= 0 && direction == -1){
				mode = true;
				direction = 1;
			}
			renderWords(0);
			if(direction == 1){
				x += int(pixelSize/4);
				pacmanOrientation[0] = 2;
				pacmanOrientation[1] += 1; 
				renderPacman();
				std::vector<int> ghostCurrOrientation = {2, 2, 2, 2};
				updateGhosts(ghostCurrOrientation);
				renderGhosts({x + ghostX[0], x + ghostX[1], x + ghostX[2], x + ghostX[3]},
							 {y, y, y, y});

				pacmanState[0] += int(pixelSize/4);
				pacmanState[1] = y;
				
			}
			else if(direction == -1){
				pacmanOrientation[0] = 1;
				pacmanOrientation[1] += 1;
				renderPacman();
				std::vector<int> ghostCurrOrientation = {1, 1, 1, 1};
				updateGhosts(ghostCurrOrientation);
				renderGhosts({x + ghostX[0], x + ghostX[1], x + ghostX[2], x + ghostX[3]},
							 {y, y, y, y});

				pacmanState[0] -= int(pixelSize/4);
				x -= int(pixelSize/4);
			}
			FsSwapBuffers();
			FsSleep(50);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		}
	}
}

void Animation::levelUpAnimation()
{
	glViewport(0, 0, screenWidth, screenHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	int x = screenWidth - pixelSize;
	int y = int(screenHeight / 2);
	pacmanState[0] = x;
	pacmanState[1] = y;
	std::vector<int> ghostX = {2*pixelSize, 3*pixelSize, 4*pixelSize, 5*pixelSize};
	std::vector<int> ghostY = {y, y, y, y};
	int direction = -1;

	for(;;){
		if(x >= screenWidth)
			break;
		if(x <= 0 && direction == -1){
			mode = true;
			direction = 1;
		}
		if(direction == 1){
			x += int(pixelSize/4);
			pacmanOrientation[0] = 2;
			pacmanOrientation[1] += 1; 
			renderBigPacman();
			std::vector<int> ghostCurrOrientation = {2, 2, 2, 2};
			updateGhosts(ghostCurrOrientation);
			renderOneGhost(3, x+ghostX[0], y+4, 1, -1);
			// renderGhosts({x + ghostX[0], x + ghostX[1], x + ghostX[2], x + ghostX[3]},
			// 				{y, y, y, y});

			pacmanState[0] += int(pixelSize/4);
			pacmanState[1] = y;
			
		}
		else if(direction == -1){
			pacmanOrientation[0] = 1;
			pacmanOrientation[1] += 1;
			renderPacman();
			std::vector<int> ghostCurrOrientation = {1, 1, 1, 1};
			updateGhosts(ghostCurrOrientation);
			renderOneGhost(3, x+ghostX[0], y, 0, -1);
			// renderGhosts({x + ghostX[0], x + ghostX[1], x + ghostX[2], x + ghostX[3]},
			// 				{y, y, y, y});

			pacmanState[0] -= int(pixelSize/4);
			x -= int(pixelSize/4);
		}
		FsSwapBuffers();
		FsSleep(50);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
void Animation::pacmanDeathAnimation()
{	
	glRasterPos2i(pacmanState[0], pacmanState[1]);
	
	for(int i=0;i<10;++i)
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glDrawPixels(pixelSize2, pixelSize2, GL_RGBA, GL_UNSIGNED_BYTE,
					spritePacmanDeath[i].GetEditableBitmapPointer());
		FsSwapBuffers();
		if(i != 9)
		{
			FsSleep(100);
		}
	}
}

void Animation::updateGhosts(std::vector<int> nextDirection){
	// currDirection is a vector of size 4, either 0, 1, 2, 3 which shows the direction of
	// the 4 ghosts, nextDirection is the direction needed, 
	// 0 - down
	// 1 - left
	// 2 - right
	// 3 - up
	for(int i=0;i<nextDirection.size();++i){
		if(currState[i][0] == nextDirection[i]){
			currState[i][1] = abs(1 - currState[i][1]); 
		}
		else{
			currState[i][0] = nextDirection[i];
			currState[i][1] = 0;
		}
	}
	
}

void Animation::updateOneGhost(int ghostNo, int nextDirection)
{
	if(currState[ghostNo][0] == nextDirection){
			currState[ghostNo][1] = abs(1 - currState[ghostNo][1]); 
		}
		else{
			currState[ghostNo][0] = nextDirection;
			currState[ghostNo][1] = 0;
		}
}

void Animation::renderGhosts(std::vector<int>&& nx, std::vector<int>&& ny){
	for(int ghost_no=0;ghost_no<4;++ghost_no){
		if(!isValid(nx[ghost_no], ny[ghost_no]))
			continue;
		glRasterPos2i(nx[ghost_no], ny[ghost_no]);
		if(mode == false)
			glDrawPixels(pixelSize2, pixelSize2, GL_RGBA, GL_UNSIGNED_BYTE, 
						 spriteBitmaps[ghost_no][currState[ghost_no][0]]
						 [currState[ghost_no][1]].GetEditableBitmapPointer());	
		else{
			
			glDrawPixels(pixelSize2, pixelSize2, GL_RGBA, GL_UNSIGNED_BYTE, 
						 spriteGhostModeBlue[currState[ghost_no][1]].GetEditableBitmapPointer());
		}
	}
	//FsSwapBuffers();
	// FsSleep(10);
}

void Animation::renderOneGhost(int ghostNo, int x, int y, int mode, int direction)
{

	// Direction variable
	// 0 - down
	// 1 - left
	// 2 - right
	// 3 - up

	// Mode variable
	// 0 - normal ghost
	// 1 - blue frightened ghost
	// 2 - white frightened ghost
	// 3 - ghost eyes

	// ghostNo is the ghost id
	// 0 - blue
	// 1 - orange
	// 2 - pink
	// 3 - red

	// x, y are locations in pixel coordinates
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(direction != -1)
		updateOneGhost(ghostNo, direction);
	glRasterPos2i(x, y);
	if(mode == 0)
	{
		glDrawPixels(pixelSize2, pixelSize2, GL_RGBA, GL_UNSIGNED_BYTE,
					spriteBitmaps[ghostNo][currState[ghostNo][0]]
					[currState[ghostNo][1]].GetEditableBitmapPointer());
	}
	else if(mode == 1)
	{
		glDrawPixels(pixelSize2, pixelSize2, GL_RGBA, GL_UNSIGNED_BYTE,
					spriteGhostModeBlue[currState[ghostNo][1]].GetEditableBitmapPointer());
	}
	else if(mode == 2)
	{
		glDrawPixels(pixelSize2, pixelSize2, GL_RGBA, GL_UNSIGNED_BYTE,
		spriteGhostModeWhite[currState[ghostNo][1]].GetEditableBitmapPointer());
		
	}
	else if(mode == 3)
	{	
		glDrawPixels(pixelSize, pixelSize, GL_RGBA, GL_UNSIGNED_BYTE,
		spriteGhostEyes[currState[ghostNo][0]].GetEditableBitmapPointer());
	}
	glDisable(GL_BLEND);
}

bool Animation::renderPacman(){
	if(!isValid(pacmanState[0], pacmanState[1]))
		return false;
	
	glBegin(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(pacmanState[0], pacmanState[1]);
	glDrawPixels(pixelSize2, pixelSize2, GL_RGBA, GL_UNSIGNED_BYTE,
					spritePacman[pacmanOrientation[0]]
					[pacmanOrientation[1]%5].GetEditableBitmapPointer());
	glDisable(GL_BLEND);
	glEnd();
	//FsSwapBuffers();
	// FsSleep(100);
	return true;
}

void Animation::renderBigPacman(){
	if(!isValid(pacmanState[0], pacmanState[1]))
		return;
	glRasterPos2i(pacmanState[0], pacmanState[1]+int(pixelSize/2));
	glDrawPixels(2*pixelSize, 2*pixelSize, GL_RGBA, GL_UNSIGNED_BYTE,
				spriteBigPacman[pacmanOrientation[1]%5].GetEditableBitmapPointer());
}

void Animation::renderFood(int width, int height){
	for(int i=0;i<width;i+=pixelSize){
		for(int j=0;j<height;j+=pixelSize){
			if(occupiedPixels[int(i/pixelSize)][int(j/pixelSize)] == 1)
				continue;
			glRasterPos2i(i, j);
			glDrawPixels(pixelSize, pixelSize, GL_RGBA, GL_UNSIGNED_BYTE,
						 spriteFood.GetEditableBitmapPointer());
		}
	}
}

bool Animation::renderOneFood(int x, int y){
	if(occupiedPixels[int(x/pixelSize)][int(y/pixelSize)] == 1)
		return false;
	glRasterPos2i(x, y);
	glDrawPixels(pixelSize, pixelSize, GL_RGBA, GL_UNSIGNED_BYTE,
					spriteFood.GetEditableBitmapPointer());
	return true;
}

void Animation::renderSuperPellet(int x, int y){
	if(occupiedPixels[int(x/pixelSize)][int(y/pixelSize)] == 1)
		return;
	
	glRasterPos2i(x, y);
	glDrawPixels(pixelSize, pixelSize, GL_RGBA, GL_UNSIGNED_BYTE,
					spriteSuperPellet.GetEditableBitmapPointer());
}

void Animation::renderMap()
{
	glRasterPos2i(0, 0);
	glDrawPixels(screenWidth, screenHeight, GL_RGBA, GL_UNSIGNED_BYTE,
				 spriteMap.GetEditableBitmapPointer());
}

void Animation::renderWords(int sleep)
{
	int character_word_width = spriteWords[0].GetWidth();
	int character_word_height = spriteWords[0].GetHeight();
	int ghost_word_width = spriteWords[1].GetWidth();
	int ghost_word_height = spriteWords[1].GetHeight();
	for(int i=0;i<5;++i){
		if(i == 0){
			glRasterPos2i(wordY[0], wordX[i]);
			glDrawPixels(character_word_width, character_word_height, GL_RGBA,
						GL_UNSIGNED_BYTE, spriteWords[i].GetEditableBitmapPointer());
		}
		else
		{
			glRasterPos2i(wordY[1], wordX[i]);
			glDrawPixels(spriteWords[i].GetWidth(), spriteWords[i].GetHeight(), GL_RGBA,
						GL_UNSIGNED_BYTE, spriteWords[i].GetEditableBitmapPointer());
		}
		if(sleep == 0)
			continue;
		FsSwapBuffers();
		// FsSleep(100);
	}
	if(sleep == 0 && blink_counter > 5)
	{
		//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glRasterPos2i(wordY[2], wordX[5]);
		glDrawPixels(ghost_word_width, ghost_word_height, GL_RGBA,
					GL_UNSIGNED_BYTE, spriteWords[5].GetEditableBitmapPointer());
		//FsSleep(250);
		if (blink_counter > 10)
		{
			blink_counter = 0;
		}
	}
	++blink_counter;

}

void Animation::removeGhostMode()
{
	mode = false;
}

void Animation::assignTextPos(){
	wordX[0] = int(0.16 * screenHeight / pixelSize) * pixelSize;
	wordX[1] = int(0.24 * screenHeight / pixelSize) * pixelSize;
	wordX[2] = int(0.32 * screenHeight / pixelSize) * pixelSize;
	wordX[3] = int(0.40 * screenHeight / pixelSize) * pixelSize;
	wordX[4] = int(0.52 * screenHeight / pixelSize) * pixelSize;
	wordX[5] = int(0.88 * screenHeight / pixelSize) * pixelSize;

	wordY[0] = int(0.1 * screenWidth / pixelSize) * pixelSize;
	wordY[1] = int(0.15 * screenWidth / pixelSize) * pixelSize;
	wordY[2] = int(0.16 * screenWidth / pixelSize) * pixelSize; 

}

void Animation::renderPacManLives()
{	
	if(livesRemaining <= 0)
		return;
	
	for(int i=0;i<livesRemaining;++i)
	{		
		glRasterPos2i(i*pixelSize2, 35*pixelSize);
		glDrawPixels(pixelSize2, pixelSize2, GL_RGBA, GL_UNSIGNED_BYTE,
					 spritePacman[1][1].GetEditableBitmapPointer());
		//FsSleep(100);
	}
}

void Animation::renderReady()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(12*pixelSize, 21*pixelSize);
	glDrawPixels(spriteReady.GetWidth(), spriteReady.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE,
				 spriteReady.GetEditableBitmapPointer());	
	glDisable(GL_BLEND);
}

void Animation::renderScores(int scoreNo)
{
	glRasterPos2i(pacmanState[0], pacmanState[1]);
	glDrawPixels(pixelSize, pixelSize, GL_RGBA, GL_UNSIGNED_BYTE,
				spriteScores[scoreNo].GetEditableBitmapPointer());
	FsSleep(500);
}

void Animation::setPacManState(int x, int y, int orien1){
	pacmanState[0] = x;
	pacmanState[1] = y;
	//pacmanOrientation[0] = orien1;
}

void Animation::renderGameOver(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(10*pixelSize, 21*pixelSize);
	glDrawPixels(spriteGameOver.GetWidth(), spriteGameOver.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE,
				 spriteGameOver.GetEditableBitmapPointer());
	glDisable(GL_BLEND);
	FsSwapBuffers();
	//FsSleep(1000);
}

std::vector<int> Animation::blockToPixelCoords(int blockX, int blockY) {
	//std::cout<<"djdk";
	int wx = pixelSize * blockX;
	int wy = pixelSize * blockY + pixelSize;
	std::vector<int> x = {wx, wy};
	return x;
}

void Animation::resetAnimation(){
	int initialX = 13;
    int initialY = 26;
	std::vector<int> iniState = blockToPixelCoords(initialX, initialY);
	pacmanState[0] = iniState[0] + pixelSize/2;
    pacmanState[1] = iniState[1];
	pacmanOrientation[0] = 2;
    pacmanOrientation[1] = 0;
	occupiedPixels = std::vector<std::vector<int>>(int(screenWidth/pixelSize), 
								 std::vector<int>(int(screenHeight/pixelSize), 0));
}