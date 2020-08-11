#pragma once
#include "singleton.h"
class cUIManager :
    public singleton<cUIManager>
{
    LPD3DXSPRITE m_sprite;
    LPD3DXFONT m_font;
public:
    cUIManager();
    ~cUIManager();

    void Begin();
    void End();

    void LostDevice();
    void ResetDevice();

    void CenterRender(cTexture* ptr, Vec2 pos, float size = 1, float rot = 0);
    void CropRender(cTexture* ptr, Vec2 pos, RECT& rc, float size = 1);
    void PrintText(const string& str, Vec2 pos, float size, bool center = 1, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};

#define UI cUIManager::GetInstance()