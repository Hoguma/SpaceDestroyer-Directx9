#include "DXUT.h"
#include "cShield.h"

cShield::cShield(Vec2 pos)
	:m_pos(pos)
{
}

cShield::~cShield()
{
}

void cShield::Update(Vec2 pos)
{
	m_pos = pos;
}

void cShield::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("spr_shield"), m_pos);
}
