#pragma once
#include "cPlayer.h"
#include "cMob.h"
#include "cBullet.h"

class cMobAdmin
{
public:
	cMobAdmin(cPlayer* player, vector<cBullet*>& bullet);
	~cMobAdmin();

	vector<cMob*> mobs;
	vector<cBullet*>& m_bullet;
	cPlayer* m_player;

	bool boss1 = false;
	bool boss2 = false;
	bool boss3 = false;
	bool boss4 = false;

	bool boss1S = true;
	bool boss2S = true;
	bool boss3S = true;
	bool boss4S = true;

	bool BossDead = false;

	bool mobSpawn = true;

	cTimer* NMS = nullptr;
	cTimer* BMS = nullptr;
	bool NM = true;
	bool BM = true;



	void Update();
	void Render();
	void UIRender();
	void CreateMob();
	void IsOut();
	void IsDestroy();
};

