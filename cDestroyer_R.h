#pragma once
#include "cMob.h"
#include "cPlayer.h"
#include "cBullet.h"
class cDestroyer_R :
    public cMob
{
public:
    cDestroyer_R(Vec2 pos, cPlayer* player, vector<cBullet*>& bullet);
    virtual ~cDestroyer_R();

    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;

    vector<cBullet*>& m_bullet;

    bool appearmove = 1;
    bool appear = 1;
    bool death = 0;

    int pattern = 0;

    bool pattern1 = 0;
    bool pattern2 = 0;
    bool pattern3 = 0;

    float RenderSize;
    float movePos;
    
    int count = 0;

    cTimer* AS = nullptr;
    cTimer* Razer = nullptr;
    cTimer* deathT = nullptr;
    bool ready = false;
    bool b_once = true;
    bool b_3move = true;
    bool b_3setPos = true;
    bool b_move = true;
    bool b_beam = false;
    bool b_effect = true;

    void Appear();
    void Pattern1();
    void Pattern2();
    void Pattern3();
    void Death();
    void Ready();
};

