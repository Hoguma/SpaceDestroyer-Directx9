#include "DXUT.h"
#include "cBomb.h"

cBomb::cBomb(Vec2 pos)
	:m_pos(pos)
{
}

cBomb::~cBomb()
{
}

void cBomb::Update()
{
	m_size *= 1.5;
	m_Rendersize += 0.5;
}

void cBomb::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("spr_shield"), m_pos, 0, m_Rendersize);
}
