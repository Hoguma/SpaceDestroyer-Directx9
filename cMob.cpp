#include "DXUT.h"
#include "cMob.h"

cMob::cMob(Vec2 pos, cPlayer* player)
	:m_pos(pos), m_player(player)
{
}

cMob::~cMob()
{
}

bool cMob::IsOutMap()
{
	return (m_pos.x - m_size < -200
		|| m_pos.x - m_size > WINSIZEX + 200
		|| m_pos.y - m_size < -200
		|| m_pos.y - m_size > WINSIZEY + 200);
}
