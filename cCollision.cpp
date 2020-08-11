#include "DXUT.h"
#include "cCollision.h"
#include "cPNBullet.h"

cCollision::cCollision(vector<cMob*>& mob, vector<cBullet*>& bullet, cItemAdmin* m_iAdmin, cPlayer* player)
	:m_mob(mob), m_bullet(bullet), m_iAdmin(m_iAdmin), m_player(player), m_item(m_iAdmin->m_items)
{
}

cCollision::~cCollision()
{

}

void cCollision::Update()
{
	if (!m_player->b_invincible)
	{
		MPColl();
		MBPColl();
	}
	MPBColl();
	IPColl();
	if (m_player->b_bombCreate)
	{
		for (auto iter : m_mob)
		{
			iter->m_Hp -= 3000;
			if (iter->m_Hp <= 0)
			{
				if(iter->mobType != "Boss")
				iter->isDestroy = true;
				m_player->MobTag = iter->mobName;
				m_iAdmin->mobDead = true;
				m_iAdmin->mobPos = iter->m_pos;
			}
		}
		m_player->b_bombCreate = false;
	}
}

void cCollision::MPColl()
{
	for (auto iter = m_mob.begin(); iter != m_mob.end();)
	{
		if (!((*iter)->m_size + m_player->m_size > D3DXVec2Length(&((*iter)->m_pos - m_player->m_pos))))
			b_PMColl = false;
		if (!b_PMColl)
		{
			if ((*iter)->m_size + m_player->m_size > D3DXVec2Length(&((*iter)->m_pos - m_player->m_pos)))
			{
				m_player->m_Hp -= (*iter)->m_Damage;
				b_PMColl = true;
				if ((*iter)->mobType != "Boss")
					(*iter)->isDestroy = true;
			}
		}
		iter++;
	}
}

void cCollision::MPBColl()
{
	for (auto miter = m_mob.begin(); miter != m_mob.end();)
	{
		bool b_coll = false;
		for (auto pbiter = m_bullet.begin(); pbiter != m_bullet.end();)
		{
			if ((*pbiter)->bulletType == "player")
			{
				if ((*miter)->m_size + (*pbiter)->m_size > D3DXVec2Length(&((*miter)->m_pos - (*pbiter)->m_pos)))
				{
					SOUND->Play("MG 2")->SetVolume(-2500);
					if ((*miter)->mobName == "Normal")
					{
						m_player->Score += 1500;
					}
					if ((*miter)->mobName == "NormalR")
					{
						m_player->Score += 5000;
					}
					if ((*miter)->mobName == "Bullet")
					{
						m_player->Score += 2000;
					}
					if ((*miter)->mobName == "BulletR")
					{
						m_player->Score += 10000;
					}
					if ((*miter)->mobName == "Glider")
					{
						m_player->Score += 6000;
					}
					if ((*miter)->mobName == "GliderR")
					{
						m_player->Score += 10000;
					}
					if ((*miter)->mobName == "Destroyer")
					{
						m_player->Score += 30000;
					}
					if ((*miter)->mobName == "DestroyerR")
					{
						m_player->Score += 50000;
					}
					(*miter)->m_Hp -= m_player->m_damage;
					(*pbiter)->isDestroy = true;
					b_coll = true;
				}
			}
			pbiter++;
		}
		if (b_coll)
		{
			if ((*miter)->m_Hp <= 0 && (*miter)->m_size > 0)
			{
				if ((*miter)->mobType != "Boss")
					(*miter)->isDestroy = true;
				m_player->MobTag = (*miter)->mobName;
				m_iAdmin->mobDead = true;
				m_iAdmin->mobPos = (*miter)->m_pos;
			}
		}
		miter++;
	}
}

void cCollision::MBPColl()
{
	for (auto mbiter = m_bullet.begin(); mbiter != m_bullet.end();)
	{
		if ((*mbiter)->bulletType == "mob")
		{
			if (m_player->m_bomb != nullptr)
			{
				if (m_player->m_bomb->m_size + (*mbiter)->m_size > D3DXVec2Length(&(m_player->m_bomb->m_pos - (*mbiter)->m_pos)))
				{
					(*mbiter)->isDestroy = true;
				}
			}
			else if (m_player->m_shield != nullptr)
			{
				if (m_player->m_shield->m_size + (*mbiter)->m_size > D3DXVec2Length(&(m_player->m_shield->m_pos - (*mbiter)->m_pos)))
				{
					(*mbiter)->isDestroy = true;
					if (m_player->m_Level >= 5)
						m_bullet.push_back(new cPNBullet((*mbiter)->m_pos));
				}
			}
			else
			{
				if (m_player->m_size + (*mbiter)->m_size > D3DXVec2Length(&(m_player->m_pos - (*mbiter)->m_pos)))
				{
					m_player->m_Hp -= (*mbiter)->m_Damage;
					(*mbiter)->isDestroy = true;
				}
			}
		}
		mbiter++;
		
	}
}

void cCollision::IPColl()
{
	for (auto iter = m_item.begin(); iter != m_item.end();)
	{
		if (m_player->m_size + (*iter)->m_size > D3DXVec2Length(&(m_player->m_pos - (*iter)->m_pos)))
		{
			m_player->itemTag = (*iter)->m_itemName;
			(*iter)->isDestroy = true;
		}
		iter++;
	}
}
