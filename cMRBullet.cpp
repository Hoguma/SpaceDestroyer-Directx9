#include "DXUT.h"
#include "cMRBullet.h"

cMRBullet::cMRBullet(Vec2 pos, float damage)
	:cBullet(pos, Vec2(0,1), 170)
{
	m_Damage = damage;
	bulletType = "mob";
}

cMRBullet::~cMRBullet()
{
}

void cMRBullet::Update()
{
	m_pos += m_Dir * 600 * Delta;
}

void cMRBullet::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Razer"), m_pos);
}
