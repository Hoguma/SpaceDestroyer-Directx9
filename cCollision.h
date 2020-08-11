#pragma once
#include "cMob.h"
#include "cBullet.h"
#include "cPlayer.h"
#include "cBomb.h"
#include "cShield.h"
#include "cItem.h"
#include "cItemAdmin.h"

class cCollision
{
public:
	vector<cMob*>& m_mob;
	vector<cBullet*>& m_bullet;
	vector<cItem*>& m_item;
	cItemAdmin* m_iAdmin;
	cPlayer* m_player;
	bool b_PMColl = false;

	cCollision(vector<cMob*>& mob, vector<cBullet*>& bullet, cItemAdmin* m_iAdmin, cPlayer* player);
	~cCollision();

	void Update();

	void MPColl();
	void MPBColl();
	void MBPColl();
	void IPColl();
};

