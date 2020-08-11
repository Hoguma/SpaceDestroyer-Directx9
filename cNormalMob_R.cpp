#include "DXUT.h"
#include "cNormalMob_R.h"
#include "cPlayer.h"

cNormalMob_R::cNormalMob_R(Vec2 pos, cPlayer* player)
	:cMob(pos, player)
{
	m_Hp = 40;
	m_Damage = 10;
	m_size = 10;
	mobName = "Normal_R";
	mobType = "none";
}

cNormalMob_R::~cNormalMob_R()
{
}

void cNormalMob_R::Update()
{
	if (m_pos.x < rand() % 200 + 300 && b_once) { m_pos.x += 6; m_angle = 0; }
	else if (m_pos.x > WINSIZEX - (rand() % 200 + 300) && b_once) { m_pos.x -= 6; m_angle = D3DXToRadian(180); }
	else
	{
		b_once = false;
		if (b_rush)
		{
			m_angle = atan2(m_player->m_pos.y - m_pos.y, m_player->m_pos.x - m_pos.x);
			b_rush = false;
		}
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 18;
	}
}

void cNormalMob_R::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Hull2_R"), m_pos, -m_angle);
}

void cNormalMob_R::UIRender()
{
}
