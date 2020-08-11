#include "DXUT.h"
#include "cGlider.h"

cGlider::cGlider(Vec2 pos, cPlayer* player)
	:cMob(pos, player)
{
	m_Hp = 5000;
	m_Damage = 10;
	mobName = "Glider";
	mobType = "Boss";
	RenderSize = 0.5;
}

cGlider::~cGlider()
{
	SAFE_DELETE(p1);
}

void cGlider::Update()
{
	if (p1 != nullptr) p1->Update();
	if (m_Hp <= 0)
		m_size = 0;
	Appear();
	Ready();
	switch (pattern)
	{
	case 0:
		break;
	case 1:
		Pattern1();
		break;
	case 2:
		Pattern2();
		break;
	case 3:
		Pattern3();
		break;
	default:
		break;
	}
}

void cGlider::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("8B"), m_pos, -m_angle, RenderSize);
}

void cGlider::UIRender()
{
	RECT hprc = {
		0,
		0,
		((float)IMAGE->FindImage("hpgauge")->info.Width / 5000) * m_Hp,
		IMAGE->FindImage("hpgauge")->info.Height
	};
	UI->CropRender(IMAGE->FindImage("hpgauge"), Vec2(WINSIZEX - 280, 50), hprc);
	UI->CenterRender(IMAGE->FindImage("hp_frame"), Vec2(WINSIZEX - 280, 50));
}

void cGlider::Appear()
{
	switch (appear)
	{
	case 0:
		break;
	case 1:
		m_angle = atan2(700 - 1200, 1375 - 345);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 13;
		if (m_pos.y <= 700)
			appear++;
		break;
	case 2:
		m_angle = atan2(400 - 700, 345 - 1375);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 13;
		if (m_pos.y <= 400)
			appear++;
		break;
	case 3:
		m_angle = atan2(-100 - 400, 1375 - 345);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 13;
		if (m_pos.y <= -100)
			appear++;
		break;
	case 4:
		m_size = 100;
		ready = true;
		appear++;
		RenderSize = 1;
		break;
	default:
		break;
	}
}

void cGlider::Pattern1()
{
	if (pattern1)
	{
		p1 = new cTimer(1.5, [&]()->void{pattern1 = true; pattern = 0; ready = true; p1 = nullptr; });
		m_angle = atan2(m_player->m_pos.y - m_pos.y, m_player->m_pos.x - m_pos.x);
		pattern1 = false;
	}
	m_pos += Vec2(cos(m_angle), sin(m_angle)) * 20;
}

void cGlider::Pattern2()
{
	switch (pattern2)
	{
	case 0:
		break;
	case 1:
		m_angle = atan2(500 - 200, (m_pos.x - 615) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 500)
			pattern2++;
		break;
	case 2:
		m_angle = atan2(800 - 500, (m_pos.x + 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 800)
			pattern2++;
		break;
	case 3:
		m_angle = atan2(1200 - 800, (m_pos.x - 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 1200)
			pattern2++;
		break;
	case 4:
		ready = true;
		pattern2 = 1;
		pattern = 0;
		break;
	default:
		break;
	}
}

void cGlider::Pattern3()
{
	switch (pattern3)
	{
	case 0:
		break;
	case 1:
		m_angle = atan2(500 - 200, (m_pos.x + 615) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 500)
			pattern3++;
		break;
	case 2:
		m_angle = atan2(800 - 500, (m_pos.x - 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 800)
			pattern3++;
		break;
	case 3:
		m_angle = atan2(1200 - 800, (m_pos.x + 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 1200)
			pattern3++;
		break;
	case 4:
		ready = true;
		pattern3 = 1;
		pattern = 0;
		break;
	default:
		break;
	}
}

void cGlider::Death()
{
	m_Hp = 0;
	switch (death)
	{
	case 0:
		break;
	case 1:
		m_angle = atan2(500 - 200, (m_pos.x - 615) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 500)
			death++;
		break;
	case 2:
		m_angle = atan2(800 - 500, (m_pos.x + 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 800)
			death++;
		break;
	case 3:
		m_angle = atan2(1200 - 800, (m_pos.x - 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 17;
		if (m_pos.y >= 1200)
			death++;
		break;
	case 4:
		isDestroy = true;
		death = 1;
		pattern = 0;
		break;
	default:
		break;
	}
}

void cGlider::Ready()
{
	if (ready)
	{
		if (b_once) { 
			m_pos.x = m_player->m_pos.x; 
			m_pos.y = -100; 
			m_angle = D3DXToRadian(90);
			if (m_Hp <= 0)
			{
				RenderSize = 0.5;
				m_size = 0;
				m_Hp = 0;
				b_death = true;
			}
			b_once = false; 
		}
		if (m_pos.y < 200) {
			D3DXVec2Lerp(&m_pos, &m_pos, &Vec2(m_pos.x, 210), 0.04);
		}
		else {
			if (b_death)
			{
				Death();
			}
			else
			{
				ready = false;
				pattern = (rand() % 3) + 1;
				b_once = true;
			}
		}
	}
}
