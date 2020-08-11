#pragma once
#include "cMob.h"
#include "cBullet.h"
#include "cPlayer.h"
class cBulletMob_R :
    public cMob
{
public:
    cBulletMob_R(Vec2 pos, cPlayer* player, vector<cBullet*>& bullet);
    virtual ~cBulletMob_R();

    bool b_Attack = true;
    cTimer* AS = nullptr;
    vector<cBullet*>& m_bullet;

    // cMob을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;
};

