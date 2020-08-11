#include "DXUT.h"
#include "cBulletMob.h"
#include "cMNBullet.h"

cBulletMob::cBulletMob(Vec2 pos, cPlayer* player, vector<cBullet*>& bullet)
	:cMob(pos, player), m_bullet(bullet)
{
	m_Hp = 60;
	m_Damage = 10;
	m_size = 10;
	mobName = "Bullet";
	mobType = "none";
}

cBulletMob::~cBulletMob()
{
	SAFE_DELETE(AS);
}

void cBulletMob::Update()
{
	if (AS != nullptr) AS->Update();
	if (m_pos.y < 200) { D3DXVec2Lerp(&m_pos, &m_pos, &Vec2(m_pos.x, 210), 0.04); }
	else
	{
		if (b_Attack)
		{
			AS = new cTimer(1, [&]()->void {b_Attack = true; AS = nullptr; });
			b_Attack = false;
			Vec2 temp;
			D3DXVec2Normalize(&temp, &(m_player->m_pos - m_pos));
			m_bullet.push_back(new cMNBullet(m_pos, temp, m_Damage));
		}
	}
}

void cBulletMob::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Hull"), m_pos);
}

void cBulletMob::UIRender()
{
}
