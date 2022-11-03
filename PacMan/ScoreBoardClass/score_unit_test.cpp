#include <string>
#include "scoreboard.h"

bool SetandGetScoreTest(ScoreBoard& s){
    
    long long int score = std::rand() % 1000000;
    long long int score_add = std::rand() % 1000;
    s.setScore(score);
    s.addScore(score_add);

    if(s.getScore() == score + score_add){
        return true;
    }
    return false;
}
bool displayScoreTest(ScoreBoard& s){
    
    long long int r = std::rand() %  1000000;
    
    s.readScores();
    s.setPlayerName("test");
    s.setScore(r);    

    s.saveScore();
   
    if (true == s.displayHighScoresConsole()){
        return true;
    }
    return false;
}
bool readScoreTest(ScoreBoard& s){
    return s.readScores();
}

int main(){

    int windowWid = 672;
    int windowHei = 900;

    ScoreBoard s(windowWid, windowHei);

    std::string highScoreTest =  "../../Strange_Team_Name_Here/PacMan/ScoreBoardClass/highscores_test.txt";

    s.setFileName(highScoreTest);

    if(false == SetandGetScoreTest(s)){
        return 1;
    }
    if(false == displayScoreTest(s)){
        return 1;
    }
    if(false == readScoreTest(s)){
        return 1;
    }

    return 0;
}