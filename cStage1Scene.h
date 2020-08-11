#pragma once
#include "cScene.h"
#include "cPlayer.h"
#include "cBulletAdmin.h"
#include "cMobAdmin.h"
#include "cSrollMap.h"
#include "cItemAdmin.h"
#include "cCollision.h"
class cStage1Scene :
    public cScene
{
    cPlayer* player = nullptr;
    cBulletAdmin* bullet = nullptr;
    cMobAdmin* mob = nullptr;
    cSrollMap* map = nullptr;
    cItemAdmin* item = nullptr;
    cCollision* coll = nullptr;
public:
    cStage1Scene();
    virtual ~cStage1Scene();
    // cScene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;
    virtual void Release() override;
};

