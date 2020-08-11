#pragma once
#include "singleton.h"
class cParticleManager :
    public singleton<cParticleManager>
{
    vector<cParticle*> m_particles;
public:
    cParticleManager();
    ~cParticleManager();

    void AddParticle(Vec2 pos, float size, float speed);
    void Update();
    void Render();
    void Release();
};

#define PART cParticleManager::GetInstance()