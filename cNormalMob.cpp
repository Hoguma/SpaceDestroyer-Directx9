#include "DXUT.h"
#include "cNormalMob.h"
#include "cPlayer.h"

cNormalMob::cNormalMob(Vec2 pos, cPlayer* player)
	:cMob(pos, player)
{
	m_Hp = 40;
	m_Damage = 10;
	m_size = 10;
	mobName = "Normal";
	mobType = "none";
}

cNormalMob::~cNormalMob()
{
}

void cNormalMob::Update()
{
	if (m_pos.x < rand() % 200 + 300 && b_once) { m_pos.x += 6; m_angle = 0; }
	else if (m_pos.x > WINSIZEX - (rand() % 200 + 300) && b_once) { m_pos.x -= 6; m_angle = D3DXToRadian(180); }
	else
	{
		b_once = false;
		m_angle = atan2(m_player->m_pos.y - m_pos.y, m_player->m_pos.x - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 4;
	}
}

void cNormalMob::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Hull2"), m_pos, -m_angle);
}

void cNormalMob::UIRender()
{
}
