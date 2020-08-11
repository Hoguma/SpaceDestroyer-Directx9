#pragma once
#include "singleton.h"
class cInputManager :
    public singleton<cInputManager>
{
    bool NowKey[256];
    bool OldKey[256];
public:

    cInputManager();
    ~cInputManager();

    void Update();
    bool KeyPress(int key);
    bool KeyDown(int key);
    bool KeyUp(int key);
};

#define INPUT cInputManager::GetInstance()