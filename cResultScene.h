#pragma once
#include "cScene.h"
class cResultScene :
    public cScene
{
public:
    char m_name[15] = "???\0";
    int nameNum = 0;
    bool type = true;
    
    cResultScene();
    virtual ~cResultScene();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void UIRender() override;
    virtual void Release() override;
};

