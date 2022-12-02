#include "Sound.h"

Sound::Sound() {
    openBgm.lpstrElementName = L"source/sound/bgm.mp3";         //���� ����
    openBgm.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    

    openFireSfx.lpstrElementName = L"source/sound/fire2.wav";    //���� ����
    openFireSfx.lpstrDeviceType = L"waveaudio";    //wav ����
    

    openHitSfx.lpstrElementName = L"source/sound/hit.wav";
    openHitSfx.lpstrDeviceType = L"waveaudio";
    

    openFadeoutSfx.lpstrElementName = L"source/sound/fadeout.wav";
    openFadeoutSfx.lpstrDeviceType = L"waveaudio";
    
}



void Sound::playingBgm(bool b) {
    if (b == true) {
        mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
        dwID = openBgm.wDeviceID;
        mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
        mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);    //���� �ݺ� ���
    }
    else {
        dwID = openBgm.wDeviceID;
        mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
    }
}

void Sound::playingFireSfx() {
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openFireSfx);
    dwID = openFireSfx.wDeviceID;
    mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //���� ��� ��ġ�� ó������ �ʱ�ȭ
    mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openFireSfx);    //������ �� �� ���
}

void Sound::playingHitSfx() {
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openHitSfx);
    dwID = openHitSfx.wDeviceID;
    mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //���� ��� ��ġ�� ó������ �ʱ�ȭ
    mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openHitSfx);    //������ �� �� ���
}

void Sound::playingFadeoutSfx() {
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openFadeoutSfx);
    dwID = openFadeoutSfx.wDeviceID;
    mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //���� ��� ��ġ�� ó������ �ʱ�ȭ
    mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openFadeoutSfx);    //������ �� �� ���
}