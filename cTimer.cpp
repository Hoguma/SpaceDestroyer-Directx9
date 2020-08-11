#include "DXUT.h"
#include "cTimer.h"

cTimer::cTimer(float time, function<void()> func, bool loop)
	:m_time(time * 1000), func(func), m_loop(loop)
{
	m_oldtime = GetTickCount();
	m_curtime = m_oldtime;
}

cTimer::~cTimer()
{
}

void cTimer::Update()
{
	m_curtime = GetTickCount();
	if (m_curtime - m_oldtime >= m_time)
	{
		func();
		if (m_loop)
			m_oldtime = GetTickCount();
		else
			delete this;
	}
}
