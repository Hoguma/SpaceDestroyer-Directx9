#pragma once
#include "singleton.h"
class cSoundManager :
    public singleton<cSoundManager>
{
public:
    cSoundManager();
    ~cSoundManager();

    void Update();
    void Release();

    CSoundManager manager;
    list<LPDIRECTSOUNDBUFFER> m_channels;
    map<string, CSound*> m_sounds;

    LPDIRECTSOUNDBUFFER Play(string key, bool loop = false);
    void StopAll();
    void AddSound(string key, wstring path);
};

#define SOUND cSoundManager::GetInstance()