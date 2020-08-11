#include "DXUT.h"
#include "cMNBullet.h"

cMNBullet::cMNBullet(Vec2 pos, Vec2 dir, float damage, float size, float speed)
	:cBullet(pos, dir, size), m_speed(speed)
{
	m_Damage = damage;
	RenderSize = m_size / 10;
	bulletType = "mob";
}

cMNBullet::~cMNBullet()
{
}

void cMNBullet::Update()
{
	m_pos += m_Dir * m_speed * Delta;
}

void cMNBullet::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("EB"), m_pos, m_angle, RenderSize);
}
