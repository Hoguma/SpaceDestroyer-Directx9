#pragma once
#include "cItem.h"
#include "cPlayer.h"
class cItemAdmin
{
public:
	vector<cItem*> m_items;
	Vec2 mobPos;
	cPlayer* m_player;
	float CreatePercent;
	bool mobDead = false;

	cItemAdmin(cPlayer* player);
	~cItemAdmin();
	void Update();
	void Render();
	void IsOut();
	void IsDestroy();
	void CreateItem();
	void Cheat();
};

