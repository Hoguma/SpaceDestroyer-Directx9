#pragma once
#include "cMob.h"
class cNormalMob_R : public cMob
{
public:
    cNormalMob_R(Vec2 pos, cPlayer* player);
    virtual ~cNormalMob_R();
    bool b_once = true;
    bool b_rush = true;

    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;
};

