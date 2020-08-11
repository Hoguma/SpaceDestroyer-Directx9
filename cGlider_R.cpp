#include "DXUT.h"
#include "cMNBullet.h"
#include "cGlider_R.h"

cGlider_R::cGlider_R(Vec2 pos, cPlayer* player, vector<cBullet*>& bullet)
	:cMob(pos, player), m_bullet(bullet)
{
	m_Hp = 7500;
	m_Damage = 15;
	mobName = "Glider_R";
	mobType = "Boss";
	RenderSize = 0.5;
}

cGlider_R::~cGlider_R()
{
	SAFE_DELETE(p1);
	SAFE_DELETE(deathT);
}

void cGlider_R::Update()
{
	if (p1 != nullptr) p1->Update();
	if (deathT != nullptr) deathT->Update();
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

void cGlider_R::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("8"), m_pos, -m_angle, RenderSize);
}

void cGlider_R::UIRender()
{
	RECT hprc = {
		0,
		0,
		((float)IMAGE->FindImage("hpgauge")->info.Width / 7500) * m_Hp,
		IMAGE->FindImage("hpgauge")->info.Height
	};
	UI->CropRender(IMAGE->FindImage("hpgauge"), Vec2(WINSIZEX - 280, 50), hprc);
	UI->CenterRender(IMAGE->FindImage("hp_frame"), Vec2(WINSIZEX - 280, 50));
}

void cGlider_R::Appear()
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

void cGlider_R::Pattern1()
{
	if (pattern1)
	{
		p1 = new cTimer(1.5, [&]()->void {pattern1 = true; pattern = 0; ready = true; p1 = nullptr; });
		m_angle = atan2(m_player->m_pos.y - m_pos.y, m_player->m_pos.x - m_pos.x);
		pattern1 = false;
	}
	m_pos += Vec2(cos(m_angle), sin(m_angle)) * 23;
}

void cGlider_R::Pattern2()
{
	switch (pattern2)
	{
	case 0:
		break;
	case 1:
		m_angle = atan2(500 - 200, (m_pos.x - 615) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 18;
		if (m_pos.y >= 500)
		{
			pattern2++;
			b_bullet = true;
		}
		if (b_bullet)
		{
			float angle = 0;
			float rad = D3DX_PI * 2 / 45;
			for (int i = 0; i < 45; i++, angle += rad)
			{
				Vec2 dir = Vec2(m_pos.x + cos(angle) * 5, m_pos.y + sin(angle) * 5);
				D3DXVec2Normalize(&dir, &(dir - m_pos));
				m_bullet.push_back(new cMNBullet(m_pos, dir, m_Damage));
			}
			b_bullet = false;
		}
		break;
	case 2:
		m_angle = atan2(800 - 500, (m_pos.x + 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 18;
		if (m_pos.y >= 800)
		{
			pattern2++;
			b_bullet = true;
		}
		if (b_bullet)
		{
			float angle = 0;
			float rad = D3DX_PI * 2 / 45;
			for (int i = 0; i < 45; i++, angle += rad)
			{
				Vec2 dir = Vec2(m_pos.x + cos(angle) * 5, m_pos.y + sin(angle) * 5);
				D3DXVec2Normalize(&dir, &(dir - m_pos));
				m_bullet.push_back(new cMNBullet(m_pos, dir, m_Damage));
			}
			b_bullet = false;
		}
		break;
	case 3:
		m_angle = atan2(1200 - 800, (m_pos.x - 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 18;
		if (m_pos.y >= 1200)
		{
			pattern2++;
			b_bullet = true;
		}
		if (b_bullet)
		{
			float angle = 0;
			float rad = D3DX_PI * 2 / 45;
			for (int i = 0; i < 45; i++, angle += rad)
			{
				Vec2 dir = Vec2(m_pos.x + cos(angle) * 5, m_pos.y + sin(angle) * 5);
				D3DXVec2Normalize(&dir, &(dir - m_pos));
				m_bullet.push_back(new cMNBullet(m_pos, dir, m_Damage));
			}
			b_bullet = false;
		}
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

void cGlider_R::Pattern3()
{
	switch (pattern3)
	{
	case 0:
		break;
	case 1:
		m_angle = atan2(500 - 200, (m_pos.x + 615) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 18;
		if (m_pos.y >= 500)
		{
			pattern3++;
			b_bullet = true;
		}
		if (b_bullet)
		{
			float angle = 0;
			float rad = D3DX_PI * 2 / 45;
			for (int i = 0; i < 45; i++, angle += rad)
			{
				Vec2 dir = Vec2(m_pos.x + cos(angle) * 5, m_pos.y + sin(angle) * 5);
				D3DXVec2Normalize(&dir, &(dir - m_pos));
				m_bullet.push_back(new cMNBullet(m_pos, dir, m_Damage));
			}
			b_bullet = false;
		}
		break;
	case 2:
		m_angle = atan2(800 - 500, (m_pos.x - 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 18;
		if (m_pos.y >= 800)
		{
			pattern3++;
			b_bullet = true;
		}
		if (b_bullet)
		{
			float angle = 0;
			float rad = D3DX_PI * 2 / 45;
			for (int i = 0; i < 45; i++, angle += rad)
			{
				Vec2 dir = Vec2(m_pos.x + cos(angle) * 5, m_pos.y + sin(angle) * 5);
				D3DXVec2Normalize(&dir, &(dir - m_pos));
				m_bullet.push_back(new cMNBullet(m_pos, dir, m_Damage));
			}
			b_bullet = false;
		}
		break;
	case 3:
		m_angle = atan2(1200 - 800, (m_pos.x + 1230) - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 18;
		if (m_pos.y >= 1200)
		{
			pattern3++;
			b_bullet = true;
		}
		if (b_bullet)
		{
			float angle = 0;
			float rad = D3DX_PI * 2 / 45;
			for (int i = 0; i < 45; i++, angle += rad)
			{
				Vec2 dir = Vec2(m_pos.x + (cosf(angle) * 5), m_pos.y + (sinf(angle) * 5));
				D3DXVec2Normalize(&dir, &(dir - m_pos));
				m_bullet.push_back(new cMNBullet(m_pos, dir, m_Damage));
			}
			b_bullet = false;
		}
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

void cGlider_R::Death()
{
	if (count == 20)
	{
		PART->AddParticle(m_pos, 10, 0.01);
		SAFE_DELETE(deathT);
		isDestroy = true;
	}
	if (b_effect)
	{
		b_effect = false;
		deathT = new cTimer(0.25, [&]()->void
		{
			Vec2 randPos = { (float)(rand() % 200 - 100), (float)(rand() % 200 - 100) };
			PART->AddParticle(m_pos + randPos, 2, 0.01);
			count++;
		}, 1);
	}
}

void cGlider_R::Ready()
{
	if (ready)
	{
		if (b_once) {
			m_pos.x = m_player->m_pos.x;
			m_pos.y = -100;
			m_angle = D3DXToRadian(90);
			if (m_Hp <= 0)
			{
				m_size = -1;
				m_Hp = 0;
			}
			b_once = false;
		}
		if (m_pos.y < 200) {
			D3DXVec2Lerp(&m_pos, &m_pos, &Vec2(m_pos.x, 210), 0.04);
		}
		else {
			if (m_Hp <= 0)
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
