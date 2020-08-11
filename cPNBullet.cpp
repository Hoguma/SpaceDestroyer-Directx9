#include "DXUT.h"
#include "cPNBullet.h"

cPNBullet::cPNBullet(Vec2 pos, Vec2 dir)
	: cBullet(pos, dir, 10)
{
	bulletType = "player";
}

cPNBullet::~cPNBullet()
{
}

void cPNBullet::Update()
{
	m_pos -= m_Dir * 900 * Delta;
}

void cPNBullet::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("PB"), m_pos);
}
