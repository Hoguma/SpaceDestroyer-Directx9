#pragma once
class cShield
{
public:
	cShield(Vec2 pos);
	~cShield();

	float m_size = 120;
	Vec2 m_pos;

	void Update(Vec2 pos);
	void Render();
};

