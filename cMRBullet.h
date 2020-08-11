#pragma once
#include "cBullet.h"
class cMRBullet :
    public cBullet
{
public:
    cMRBullet(Vec2 pos, float damage);
    virtual ~cMRBullet();

    virtual void Update() override;
    virtual void Render() override;
};

