#include "DXUT.h"
#include "cBulletMob_R.h"
#include "cMNBullet.h"

cBulletMob_R::cBulletMob_R(Vec2 pos, cPlayer* player, vector<cBullet*>& bullet)
	:cMob(pos, player), m_bullet(bullet)
{
	m_Hp = 100;
	m_Damage = 15;
	m_size = 10;
	mobName = "Bullet_R";
	mobType = "none";
}

cBulletMob_R::~cBulletMob_R()
{
	SAFE_DELETE(AS);
}

void cBulletMob_R::Update()
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
			m_bullet.push_back(new cMNBullet(m_pos, temp - Vec2(0.0625, 0), m_Damage));
			m_bullet.push_back(new cMNBullet(m_pos, temp + Vec2(0.0625, 0), m_Damage));
		}
	}
}

void cBulletMob_R::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Hull_R"), m_pos);
}

void cBulletMob_R::UIRender()
{
}
