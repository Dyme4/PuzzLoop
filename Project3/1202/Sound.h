#pragma once
#include <windows.h>
#include <mmsystem.h>;                //À½¾Ç
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>;                //À½¾Ç
#include <string>
using namespace std;

class Sound
{
public:
    Sound();

    void playingBgm(bool b);

    void playingFireSfx();

    void playingHitSfx();
    void playingFadeoutSfx();



private:
    MCI_OPEN_PARMS openBgm;
    MCI_PLAY_PARMS playBgm;

    MCI_OPEN_PARMS openFireSfx;
    MCI_PLAY_PARMS playFireSfx;

    MCI_OPEN_PARMS openHitSfx;
    MCI_PLAY_PARMS playHitSfx;

    MCI_OPEN_PARMS openFadeoutSfx;
    MCI_PLAY_PARMS playFadeoutSfx;

    int dwID;
};

