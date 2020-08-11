#pragma once
#include "cBullet.h"
class cPNBullet :
    public cBullet
{
public:
    cPNBullet(Vec2 pos, Vec2 dir = Vec2(0,1));
    virtual ~cPNBullet();

    virtual void Update() override;
    virtual void Render() override;
};

