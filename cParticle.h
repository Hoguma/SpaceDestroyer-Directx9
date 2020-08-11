#pragma once
class cParticle abstract
{
public:
	cParticle(Vec2 pos, float size);
	virtual ~cParticle();

	virtual void Update() = 0;
	virtual void Render() = 0;

	Vec2 m_pos;
	float RenderSize;
	bool isDestroy = false;
};

