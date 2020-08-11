#pragma once
class cBomb
{
public:
	cBomb(Vec2 pos);
	~cBomb();

	float m_size = 120;
	float m_Rendersize = 1;
	Vec2 m_pos;

	void Update();
	void Render();
};

