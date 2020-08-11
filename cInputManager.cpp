#include "DXUT.h"
#include "cInputManager.h"

cInputManager::cInputManager()
{
}

cInputManager::~cInputManager()
{
}

void cInputManager::Update()
{
    for (int i = 0; i < 256; i++) OldKey[i] = NowKey[i];
    for (int i = 0; i < 256; i++)
    {
        if (GetAsyncKeyState(i)) NowKey[i] = true;
        else NowKey[i] = false;
    }
}

bool cInputManager::KeyPress(int key)
{
    return NowKey[key] == true && OldKey[key] == true;
}

bool cInputManager::KeyDown(int key)
{
    return NowKey[key] == true && OldKey[key] == false;
}

bool cInputManager::KeyUp(int key)
{
    return NowKey[key] == false && OldKey[key] == true;
}