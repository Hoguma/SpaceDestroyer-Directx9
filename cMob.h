#pragma once
class cPlayer;
class cMob abstract
{
public:
	cMob(Vec2 pos, cPlayer* player);
	virtual ~cMob();
	bool IsOutMap();

	string mobName;
	string mobType;
	cPlayer* m_player;
	Vec2 m_pos;
	bool isDestroy = false;
	float m_Hp;
	float m_size;
	float m_angle;
	float m_Damage;
	

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UIRender() = 0;
};

