#ifndef SCOREBOARD_H_IS_INCLUDED
#define  SCOREBOARD_H_IS_INCLUDED

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "fssimplewindow.h"
#include "ysglfontdata.h"

class ScoreBoard {
/*
    This class controls the scoring mechanism for the game.
    It also store the score to a text file which can be loaded in the menu to show the high scores with the player name.

    Unit Tests for this class --
    1) Setting and getting random scores
	2) Saving the random scores to a file 
    3) Reading high scores from file and displaying it in the menu.
*/
private:
	long long int GameScore;
	long long int highScore;
	std::string highScoreFileName = "highscores.txt";
	std::string playerName; // from TextInput class
	int windowWid, windowHei;

	std::vector<std::string> names; std::vector<long long int> scores;

public:
	ScoreBoard(){;}
	ScoreBoard(int w, int h){
		windowWid = w;
		windowHei = h;
		GameScore = 0;
		highScore = 0;
	}

	void setFileName(std::string fName){
		highScoreFileName = fName;
	}

	long long int getScore() const{ // returns GameScore
		return GameScore;
	}
	std::string getPlayerName() const{
		return playerName;
	}
	void setScore(int val){ // change the game score to the argument value
		GameScore = val;
		if (GameScore > highScore){
			highScore = GameScore;
		}
	}
	void setPlayerName(std::string name){
		playerName = name;
	}
	void addScore(int num){ // Add the score in the argument to the game score
		GameScore += num;
		if (GameScore > highScore){
			highScore = GameScore;
		}
	}
	void drawScore(){
		glColor3ub(255, 255, 255);

		glRasterPos2d(int(windowWid/2) - 90, 35);
		YsGlDrawFontBitmap20x28("HIGH SCORE");

		auto str1 = std::to_string(highScore);
		glRasterPos2d(int(windowWid/2) - 35, 70);
		YsGlDrawFontBitmap20x28(str1.c_str());

		auto str2 = std::to_string(GameScore);
		glRasterPos2d(100, 70);
		YsGlDrawFontBitmap20x28(str2.c_str());
	}
	bool readScores(){
		// Read the file containing the scores
		FsChangeToProgramDir();
		std::ifstream in(highScoreFileName.c_str(), std::ios::in);

		std::string str;
		std::string nameStr;
		std::string numStr;
		bool num=false;
		
		if (in.is_open()){
			while (!in.eof())
			{
				std::getline(in, str);

				for(int i=0;i<str.size();++i){
					if (num == true && std::isdigit(str[i+1]) == false){
						if (std::isdigit(str[i])){
							numStr.push_back(str[i]);
						}
						scores.push_back(atoi(numStr.c_str()));
						numStr = "";
						num = false;
					}
					else if (str[i] == ' '){
						names.push_back(nameStr.c_str());
						nameStr = "";
						num = true;
					}
					else{
						if (num){
							numStr.push_back(str[i]);
						}
						else{
							nameStr.push_back(str[i]);
						}
					}
				}		
			}

			for(auto s : scores){
				if (s > highScore){
					highScore = s;
				}
			}

			return true;
		}

		return false;
	}

	bool displayHighScoresConsole(){

		std::cout << "---------HIGH SCORES----------" << std::endl;

		if (!names.empty() && !scores.empty()){
			for (int i=0;i<names.size();++i){
				std::cout << names[i] << " " << scores[i] << std::endl;
			}
			return true;
		}
		else{
			std::cout << "Highscore file is empty or not read" << std::endl;
			return false;
		}

		std::cout << "---------------------------------------" << std::endl;
	}

	void saveScore(){
		// save current scores and player name
		FsChangeToProgramDir();
		std::ofstream outfile;
		outfile.open(highScoreFileName.c_str(), std::ios_base::app);
		outfile << std::endl;
		outfile << playerName << " " << std::to_string(GameScore);
	}
	~ScoreBoard(){
		names.clear();
		scores.clear();
	}
};

#endif