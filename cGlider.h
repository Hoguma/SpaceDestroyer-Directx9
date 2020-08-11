#pragma once
#include "cMob.h"
#include "cPlayer.h"
class cGlider :
    public cMob
{
public:
    cGlider(Vec2 pos, cPlayer* player);
    virtual ~cGlider();

    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;
    
    int appear = 1;
    int death = 1;

    int pattern = 0;

    bool pattern1 = 1;
    int pattern2 = 1;
    int pattern3 = 1;

    float RenderSize;

    cTimer* p1 = nullptr;
    bool ready = false;
    bool b_once = true;
    bool b_death = false;

    void Appear();
    void Pattern1();
    void Pattern2();
    void Pattern3();
    void Death();
    void Ready();
};

