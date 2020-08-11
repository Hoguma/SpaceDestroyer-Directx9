#include "DXUT.h"
#include "cItem.h"

cItem::cItem(Vec2 pos)
	:m_pos(pos)
{
}

cItem::~cItem()
{
}

void cItem::Update()
{
	m_pos.y += 300 * Delta;
}

void cItem::Render()
{
	RENDER->CenterRender(m_img, m_pos);
}

bool cItem::IsOutMap()
{
	return (m_pos.x - m_size < -200
		|| m_pos.x - m_size > WINSIZEX + 200
		|| m_pos.y - m_size < -200
		|| m_pos.y - m_size > WINSIZEY + 200);
}
