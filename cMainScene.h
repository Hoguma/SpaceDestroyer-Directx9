#pragma once
#include "cScene.h"
class cMainScene :
    public cScene
{
public:
    int select = 1;
    bool help = false;
    bool rank = false;
    bool button = true;
    cMainScene();
    virtual ~cMainScene();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;
    virtual void Release() override;
};

