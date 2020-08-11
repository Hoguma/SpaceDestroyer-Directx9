#include "DXUT.h"
#include "cDestroyer_R.h"
#include "cMNBullet.h"
#include "cMRBullet.h"

cDestroyer_R::cDestroyer_R(Vec2 pos, cPlayer* player, vector<cBullet*>& bullet)
	:cMob(pos, player), m_bullet(bullet)
{
	m_Hp = 12500;
	m_Damage = 20;
	m_angle = 0;
	mobName = "Destroyer_R";
	mobType = "Boss";
	RenderSize = 0.5;
}

cDestroyer_R::~cDestroyer_R()
{
	SAFE_DELETE(AS);
	SAFE_DELETE(Razer);
	SAFE_DELETE(deathT);
}

void cDestroyer_R::Update()
{
	if (m_Hp <= 0)
	{
		m_Hp = 0;
		m_size = -1;
		ready = false;
		AS = nullptr;
		Razer = nullptr;
		pattern = 0;
		Death();
	}
	if (Razer != nullptr) Razer->Update();
	if (deathT != nullptr) deathT->Update();
	if (AS != nullptr) AS->Update();
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
	m_Hp -= 20;
}

void cDestroyer_R::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("9"), m_pos, m_angle, RenderSize);
}

void cDestroyer_R::UIRender()
{
	RECT hprc = {
		0,
		0,
		((float)IMAGE->FindImage("hpgauge")->info.Width / 12500) * m_Hp,
		IMAGE->FindImage("hpgauge")->info.Height
	};
	UI->CropRender(IMAGE->FindImage("hpgauge"), Vec2(WINSIZEX - 280, 50), hprc);
	UI->CenterRender(IMAGE->FindImage("hp_frame"), Vec2(WINSIZEX - 280, 50));
}

void cDestroyer_R::Appear()
{
	if (appear)
	{
		if (m_pos.y >= -400 && appearmove)
		{
			m_pos.y -= 300 * Delta;
			if (RenderSize < 1.8) RenderSize += 0.005;
		}
		else appearmove = false;
		if (m_pos.y < 200 && !appearmove)
		{
			m_angle = D3DXToRadian(180);
			RenderSize = 1.8;
			m_size = 150;
			D3DXVec2Lerp(&m_pos, &m_pos, &Vec2(m_pos.x, 210), 0.04);
		}
		else if (!appearmove && m_pos.y > 200) { ready = true; appear = false; }
	}
}

void cDestroyer_R::Pattern1()
{
	if (pattern1)
	{
		Vec2 temp;
		D3DXVec2Normalize(&temp, &Vec2(m_player->m_pos - m_pos));
		m_bullet.push_back(new cMNBullet(m_pos, temp, m_Damage * 1.8, 150));
		pattern1 = false;
		ready = true;
	}
}

void cDestroyer_R::Pattern2()
{
	if (pattern2)
	{
		Vec2 dir;
		D3DXVec2Normalize(&dir, &(m_player->m_pos - m_pos));
		float angle = 0;
		float rad = D3DX_PI * 2 / 30;
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 150 * cos(angle) * 1, m_pos.y + 150 * sin(angle) * 1), dir, m_Damage * 0.2));
		}
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 100 * cos(angle) * 1, m_pos.y + 100 * sin(angle) * 1), dir, m_Damage * 0.2));
		}
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 50 * cos(angle) * 1, m_pos.y + 50 * sin(angle) * 1), dir, m_Damage * 0.2));
		}
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 150 * cos(angle) * 1, m_pos.y + 150 * sin(angle) * 1), dir + Vec2(0.0625, 0), m_Damage * 0.2));
		}
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 100 * cos(angle) * 1, m_pos.y + 100 * sin(angle) * 1), dir + Vec2(0.0625, 0), m_Damage * 0.2));
		}
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 50 * cos(angle) * 1, m_pos.y + 50 * sin(angle) * 1), dir + Vec2(0.0625, 0), m_Damage * 0.2));
		}
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 150 * cos(angle) * 1, m_pos.y + 150 * sin(angle) * 1), dir - Vec2(0.0625, 0), m_Damage * 0.2));
		}
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 100 * cos(angle) * 1, m_pos.y + 100 * sin(angle) * 1), dir - Vec2(0.0625, 0), m_Damage * 0.2));
		}
		for (int i = 0; i < 30; i++, angle += rad)
		{
			m_bullet.push_back(new cMNBullet(Vec2(m_pos.x + 50 * cos(angle) * 1, m_pos.y + 50 * sin(angle) * 1), dir - Vec2(0.0625, 0), m_Damage * 0.2));
		}

		pattern2 = false;
		ready = true;
	}
}

void cDestroyer_R::Pattern3()
{
	if (pattern3)
	{
		if (b_3move)
		{
			if (b_3setPos)
			{
				movePos = rand() % 710 + 605;
				b_3setPos = false;
			}
			if (movePos > m_pos.x && b_move)
			{
				D3DXVec2Lerp(&m_pos, &m_pos, &Vec2(movePos + 10, m_pos.y), 0.04);
				if (movePos <= m_pos.x)
				{
					b_move = false;
					b_3move = false;
					b_beam = true;
				}
			}
			else if (movePos < m_pos.x && b_move)
			{
				D3DXVec2Lerp(&m_pos, &m_pos, &Vec2(movePos - 10, m_pos.y), 0.04);
				if (movePos >= m_pos.x)
				{
					b_move = false;
					b_3move = false;
					b_beam = true;
				}
			}
			else
			{
				b_move = false;
				b_3move = false;
				b_beam = true;
			}
		}
		if (b_beam)
		{
			b_beam = false;
			Razer = new cTimer(5, [&]()->void {
				b_move = true;
				b_3move = true;
				b_3setPos = true;
				pattern3 = false;
				ready = true;
				Razer = nullptr;
			});
		}
		if (!b_3move)
			m_bullet.push_back(new cMRBullet(m_pos + Vec2(0, 300), m_Damage * 0.3));
	}
}

void cDestroyer_R::Death()
{
	if (count == 20)
	{
		PART->AddParticle(m_pos, 10, 0.01);
		deathT = nullptr;
		isDestroy = true;
	}
	if (b_effect)
	{
		b_effect = false;
		deathT = new cTimer(0.25, [&]()->void
		{
			Vec2 randPos = { (float)(rand() % 400 - 200), (float)(rand() % 400 - 200) };
			PART->AddParticle(m_pos + randPos, 2, 0.01);
			count++;
		}, 1);
	}
}

void cDestroyer_R::Ready()
{
	if (ready)
	{
		ready = false;
		pattern = 0;
		AS = new cTimer(1, [&]()->void {
			pattern = rand() % 3 + 1;
			if (pattern == 1) pattern1 = true;
			if (pattern == 2) pattern2 = true;
			if (pattern == 3) pattern3 = true;
			AS = nullptr;
		});
	}
}
