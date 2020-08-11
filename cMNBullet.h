#pragma once
#include "cBullet.h"
class cMNBullet :
    public cBullet
{
public:
    float RenderSize;
    float m_speed;
    cMNBullet(Vec2 pos, Vec2 dir, float damage, float size = 10, float speed = 900);
    virtual ~cMNBullet();

    // cBullet��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
};

