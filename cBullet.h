#pragma once
class cBullet
{
public:
	Vec2 m_pos;
	Vec2 m_Dir;
	float m_angle;
	float m_size;
	bool isDestroy = false;
	string bulletType;
	float m_Damage;

	cBullet(Vec2 pos, Vec2 Dir, float size);
	virtual ~cBullet();

	virtual void Update() = 0;
	virtual void Render() = 0;

	bool IsOutMap();
};

