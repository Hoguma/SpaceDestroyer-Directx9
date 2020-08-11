#pragma once
#include "cMob.h"
#include "cBullet.h"
#include "cPlayer.h"
class cBulletMob :
    public cMob
{
public:
    cBulletMob(Vec2 pos, cPlayer* player, vector<cBullet*>& bullet);
    virtual ~cBulletMob();

    bool b_Attack = true;
    cTimer* AS = nullptr;
    vector<cBullet*>& m_bullet;

    // cMob��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;
};

