#pragma once
#include "cMob.h"
class cNormalMob : public cMob
{
public:
    cNormalMob(Vec2 pos, cPlayer* player);
    virtual ~cNormalMob();
    bool b_once;

    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;
};

