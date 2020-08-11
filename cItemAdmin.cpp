#include "DXUT.h"
#include "cItemAdmin.h"
#include "cHealItem.h"
#include "cCoolItem.h"
#include "cLvUpItem.h"

cItemAdmin::cItemAdmin(cPlayer* player)
	:m_player(player)
{

}

cItemAdmin::~cItemAdmin()
{
	for (auto iter : m_items) SAFE_DELETE(iter);
	m_items.clear();
}

void cItemAdmin::Update()
{
	for (auto iter : m_items) iter->Update();
	IsOut();
	IsDestroy();
	CreateItem();
	Cheat();
}

void cItemAdmin::Render()
{
	for (auto iter : m_items) iter->Render();
}

void cItemAdmin::IsOut()
{
	size_t size = m_items.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = m_items[i];
		if (iter->IsOutMap())
		{
			SAFE_DELETE(iter);
			m_items.erase(m_items.begin() + i);
			i--; size--;
		}
	}
}

void cItemAdmin::IsDestroy()
{
	size_t size = m_items.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = m_items[i];
		if (iter->isDestroy)
		{
			SAFE_DELETE(iter);
			m_items.erase(m_items.begin() + i);
			i--; size--;
		}
	}
}

void cItemAdmin::CreateItem()
{
	if (mobDead)
	{
		CreatePercent = rand() % 20;
		if (CreatePercent == 0)
		{
			float per = rand() % 10;
			if (per < 6)
			{
				m_items.push_back(new cHealItem(mobPos));
				mobDead = false;
			}
			if (per >= 6 && per < 9)
			{
				m_items.push_back(new cCoolItem(mobPos));
				mobDead = false;
			}
			if (per == 9)
			{
				if(m_player->m_Level < 5)
					m_items.push_back(new cLvUpItem(mobPos));
				else
					m_items.push_back(new cHealItem(mobPos));
				mobDead = false;
			}
		}
		else
			mobDead = false;
	}
}

void cItemAdmin::Cheat()
{
	if (INPUT->KeyDown(VK_F3))
	{
		float per = rand() % 10;
		if (per < 6)
		{
			m_items.push_back(new cHealItem(m_player->m_pos - Vec2(0, 400)));
		}
		if (per >= 6 && per < 9)
		{
			m_items.push_back(new cCoolItem(m_player->m_pos - Vec2(0, 400)));
		}
		if (per == 9)
		{
			if(m_player->m_Level < 5)
				m_items.push_back(new cLvUpItem(m_player->m_pos - Vec2(0, 400)));
			else
				m_items.push_back(new cHealItem(m_player->m_pos - Vec2(0, 400)));
		}
	}
}
