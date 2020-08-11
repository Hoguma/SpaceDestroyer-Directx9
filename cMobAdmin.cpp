#include "DXUT.h"
#include "cMobAdmin.h"
#include "cNormalMob.h"
#include "cNormalMob_R.h"
#include "cBulletMob.h"
#include "cBulletMob_R.h"
#include "cGlider.h"
#include "cGlider_R.h"
#include "cDestroyer.h"
#include "cDestroyer_R.h"

cMobAdmin::cMobAdmin(cPlayer* player, vector<cBullet*>& bullet)
	:m_player(player), m_bullet(bullet)
{
}

cMobAdmin::~cMobAdmin()
{
	for (auto iter : mobs) SAFE_DELETE(iter);
	mobs.clear();
	SAFE_DELETE(NMS);
	SAFE_DELETE(BMS);
}

void cMobAdmin::Update()
{
	for (auto iter : mobs) iter->Update();
	IsOut();
	IsDestroy();
	CreateMob();
}

void cMobAdmin::Render()
{
	for (auto iter : mobs) iter->Render();
}

void cMobAdmin::UIRender()
{
	for (auto iter : mobs) iter->UIRender();
}

void cMobAdmin::CreateMob()
{
	if (NMS != nullptr) NMS->Update();
	if (BMS != nullptr) BMS->Update();
	if (m_player->Score >= 1000000 && boss1S && m_player->Score <= 1100000) { boss1 = true; mobSpawn = false; }
	if (m_player->Score >= 10000000 && boss2S && m_player->Score <= 11000000) { boss2 = true; mobSpawn = false; }
	if (m_player->Score >= 30000000 && boss3S && m_player->Score <= 31000000) { boss3 = true; mobSpawn = false; }
	if (m_player->Score >= 85000000 && boss4S && m_player->Score <= 86000000) { boss4 = true; mobSpawn = false; }
	if (mobSpawn)
	{
		if (NM && m_player->Score <= 10000000)
		{
			NMS = new cTimer(0.8, [&]()->void {NM = true; NMS = nullptr; });
			NM = false;
			mobs.push_back(new cNormalMob(Vec2(-10, 200), m_player));
			mobs.push_back(new cNormalMob(Vec2(WINSIZEX + 10, 200), m_player));
		}
		if (BM && m_player->Score <= 10000000)
		{
			BMS = new cTimer(1, [&]()->void {BM = true; BMS = nullptr; });
			BM = false;
			mobs.push_back(new cBulletMob(Vec2(rand() % 1320 + 300, -10), m_player, m_bullet));
		}
		if (NM && m_player->Score >= 10000000)
		{
			NMS = new cTimer(0.8, [&]()->void {NM = true; NMS = nullptr; });
			NM = false;
			mobs.push_back(new cNormalMob_R(Vec2(-10, 200), m_player));
			mobs.push_back(new cNormalMob_R(Vec2(WINSIZEX + 10, 200), m_player));
		}
		if (BM && m_player->Score >= 10000000)
		{
			BMS = new cTimer(1, [&]()->void {BM = true; BMS = nullptr; });
			BM = false;
			mobs.push_back(new cBulletMob_R(Vec2(rand() % 1320 + 300, -10), m_player, m_bullet));
		}
	}
	if (boss1S && boss1)
	{
		mobs.push_back(new cGlider(Vec2(345, 1000), m_player));
		boss1S = false;
	}
	if (boss2S && boss2)
	{
		mobs.push_back(new cGlider_R(Vec2(345, 1000), m_player, m_bullet));
		boss2S = false;
	}
	if (boss3S && boss3)
	{
		mobs.push_back(new cDestroyer(Vec2(WINSIZEX / 2, 1400), m_player, m_bullet));
		boss3S = false;
	}
	if (boss4S && boss4)
	{
		mobs.push_back(new cDestroyer_R(Vec2(WINSIZEX / 2, 1400), m_player, m_bullet));
		boss4S = false;
	}
}

void cMobAdmin::IsOut()
{
	size_t size = mobs.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = mobs[i];
		if (iter->IsOutMap() && iter->mobType != "Boss")
		{
			SAFE_DELETE(iter);
			mobs.erase(mobs.begin() + i);
			i--; size--;
		}
	}
}

void cMobAdmin::IsDestroy()
{
	size_t size = mobs.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = mobs[i];
		if (iter->isDestroy)
		{
			if (iter->mobName == "Glider")
			{
				boss1 = false;
				mobSpawn = true;
			}
			if (iter->mobName == "Glider_R")
			{
				boss2 = false;
				BossDead = true;
			}
			if (iter->mobName == "Destroyer")
			{
				boss3 = false;
				mobSpawn = true;
			}
			if (iter->mobName == "Destroyer_R")
			{
				boss4 = false;
				BossDead = true;
			}
			if (iter->mobType != "Boss")
				PART->AddParticle(iter->m_pos, 1, 0.01);
			SAFE_DELETE(iter);
			mobs.erase(mobs.begin() + i);
			i--; size--;
		}
	}
}
