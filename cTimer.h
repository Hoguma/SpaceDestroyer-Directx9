#pragma once
class cTimer
{
public:
	cTimer(float time, function<void()> func, bool loop = false);
	~cTimer();

	float m_time;
	float m_curtime;
	float m_oldtime;
	bool m_loop;
	function<void()> func;

	void Update();
};

