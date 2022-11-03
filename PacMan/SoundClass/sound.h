#ifndef SOUND_H_IS_INCLUDED
#define SOUND_H_IS_INCLUDED

#include <vector>
#include <iostream>
#include <string>

#include "yssimplesound.h"

class SoundPlayer{

private:
    std::string pacmanMunch = "music/pacman_munch.wav";
    std::string introMusic = "music/pacman_beginning.wav";
    std::string pacmanDeath = "music/8d82b5_Pacman_Dies_Sound_Effect.wav";
    std::string eatGhost = "music/pacman_eatghost.wav";
    std::string intermission = "music/pacman_intermission.wav";

    YsSoundPlayer player;
    YsSoundPlayer::SoundData wav[5];

    float playBackVolume;

public:

    SoundPlayer(){
        player.MakeCurrent();

        wav[0].LoadWav(introMusic.c_str());
        wav[1].LoadWav(pacmanMunch.c_str());
        wav[2].LoadWav(intermission.c_str());
        wav[3].LoadWav(pacmanDeath.c_str());
        wav[4].LoadWav(eatGhost.c_str());

        playBackVolume = 0.7;

        for(int i=0;i<5;++i){
            player.SetVolume(wav[i], playBackVolume);
        }
    }

    void startPlay(){
        player.Start();
    }

    void playIntroMusic(){
        player.PlayBackground(wav[0]);
    }

    void playPacmanMunch(){
        // if( YSTRUE == player.IsPlaying(wav[4])){
        //     // stopAll();
        //     player.KeepPlaying();
        // }
        // stopAll();
        player.PlayOneShot(wav[1]);
    }

    void playIntermission(){
        // stopAll();
        player.PlayBackground(wav[2]);
    }

    void playPacmanDeath(){
        // if(checkIfPlaying() && YSTRUE != player.IsPlaying(wav[3])){
        //     stopAll();
        // }
        // stopAll();
        player.PlayOneShot(wav[3]);
    }

    void playEatGhost(){
        // stopAll();
        player.PlayOneShot(wav[4]);
    }

    void stop(YsSoundPlayer::SoundData& wav){
        player.Stop(wav);
    }

    void stopIntermission(){
        player.Stop(wav[2]);
    }

    void stopCurrent(){
        YsSoundPlayer::SoundData& curWav = getCurrentSound();
        player.Stop(curWav);
    }

    void stopAll(){
        if (YSTRUE == player.IsPlaying(wav[0])){
            player.Stop(wav[0]);
        }
        else if (YSTRUE == player.IsPlaying(wav[1])){
            player.Stop(wav[1]);
        }
        else if (YSTRUE == player.IsPlaying(wav[2])){
            player.Stop(wav[2]);
        }
        else if (YSTRUE == player.IsPlaying(wav[3])){
            player.Stop(wav[3]);
        }
        else if (YSTRUE == player.IsPlaying(wav[4])){
            player.Stop(wav[4]);
        }
    }

    bool checkIfPlaying(){
        if (YSTRUE == player.IsPlaying(wav[0]) || YSTRUE == player.IsPlaying(wav[1]) || YSTRUE == player.IsPlaying(wav[2]) ||
            YSTRUE == player.IsPlaying(wav[3]) || YSTRUE == player.IsPlaying(wav[4])){
                return true;
            }
            return false;
    }

    YsSoundPlayer::SoundData& getCurrentSound(){
        std::cout << __LINE__ << std::endl;
        if (YSTRUE == player.IsPlaying(wav[0])){
            return wav[0];
        }
        else if (YSTRUE == player.IsPlaying(wav[1])){
            return wav[1];
        }
        else if (YSTRUE == player.IsPlaying(wav[2])){
            std::cout << __LINE__ << std::endl;
            return wav[2];
        }
        else if (YSTRUE == player.IsPlaying(wav[3])){
            return wav[3];
        }
        else {
            return wav[4];
        }
    }

    void adjustVolume(double val){
        YsSoundPlayer::SoundData& curWav = getCurrentSound();
        if (val > 0 && playBackVolume + val >= 1){
            player.SetVolume(curWav, 1.);
            playBackVolume = 1.;
        }
        else if (val < 0 && playBackVolume + val <=0 ){
            player.SetVolume(curWav, 0.);
            playBackVolume = 0.;
        }
        else{
            player.SetVolume(curWav, playBackVolume + val);
            playBackVolume += val;
        }
        // std::cout << "Volume: " << playBackVolume << std::endl;
        
    }

    void endPlay(){
        player.End();
    }
};

#endif
