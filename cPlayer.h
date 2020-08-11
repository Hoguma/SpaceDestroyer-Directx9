#pragma once
#include "cBullet.h"
#include "cShield.h"
#include "cBomb.h"
class cPlayer
{
public:
	cPlayer(vector<cBullet*>& bullet);
	~cPlayer();

	cShield* m_shield = nullptr;
	cBomb* m_bomb = nullptr;
	vector<cBullet*>& m_bullet;
	Vec2 m_pos;

	string itemTag;
	string MobTag;

	cTimer* pAS = nullptr;
	cTimer* m_shieldT = nullptr;
	cTimer* m_shieldCT = nullptr;
	cTimer* m_bombT = nullptr;
	cTimer* m_bombCT = nullptr;

	bool b_shield = false;
	bool b_bomb = false;
	bool b_bombCreate = false;
	bool b_LevelUP = false;
	bool b_invincible = false;

	bool shot = true;
	bool b_spread = false;

	float m_Hp;
	float m_MaxHp;
	float m_AS_b;
	float m_AS_s;
	float m_damage;
	float m_size;
	int	m_Exp;
	int m_MaxExp;
	int m_Level;
	int Score;

	void Update();
	void Render();
	void UIRender();

	void FireBullet();
	void Move();
	void OutMap();
	void TimerUpdate();
	void TimerDelete();
	void SkillUpdate();
	void SkillRender();
	void ItemUpdate();
	void LvUpdate();
	void ScoreUpdate();
	void Cheat();
};

