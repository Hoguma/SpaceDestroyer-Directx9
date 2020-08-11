#include "DXUT.h"
#include "cBullet.h"

cBullet::cBullet(Vec2 pos, Vec2 Dir, float size)
	:m_pos(pos), m_Dir(Dir), m_size(size)
{
}

cBullet::~cBullet()
{
}

bool cBullet::IsOutMap()
{
	return (m_pos.x - m_size < -200
		|| m_pos.x - m_size > WINSIZEX + 200
		|| m_pos.y - m_size < -200
		|| m_pos.y - m_size > WINSIZEY + 200);
}
