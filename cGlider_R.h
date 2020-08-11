#pragma once
#include "cMob.h"
#include "cPlayer.h"
#include "cBullet.h"
class cGlider_R :
    public cMob
{
public:
    cGlider_R(Vec2 pos, cPlayer* player, vector<cBullet*>& bullet);
    virtual ~cGlider_R();

    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;

    vector<cBullet*>& m_bullet;

    int appear = 1;
    int death = 1;

    int pattern = 0;

    int pattern1 = 1;
    int pattern2 = 1;
    int pattern3 = 1;
    int count = 0;

    float RenderSize;
    float movePos;

    cTimer* p1 = nullptr;
    cTimer* deathT = nullptr;
    bool ready = false;
    bool b_once = true;
    bool b_bullet = false;
    bool b_effect = true;


    void Appear();
    void Pattern1();
    void Pattern2();
    void Pattern3();
    void Death();
    void Ready();
};

