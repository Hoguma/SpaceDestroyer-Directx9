#include "DXUT.h"
#include "cPlayer.h"
#include "cPNBullet.h"

cPlayer::cPlayer(vector<cBullet*>& bullet)
	:m_pos(WINSIZEX/2, 900), m_bullet(bullet), m_size(7)
{
	m_Hp =		SCENE->m_Hp;
	m_MaxHp =	SCENE->m_MaxHp;
	m_AS_b =	SCENE->m_AS_b;
	m_AS_s =	SCENE->m_AS_s;
	m_damage =	SCENE->m_damage;
	m_Exp =		SCENE->m_Exp;
	m_MaxExp =	SCENE->m_MaxExp;
	m_Level =	SCENE->m_Level;
	Score =		SCENE->Score;
}

cPlayer::~cPlayer()
{
	TimerDelete();
	SCENE->m_Hp = m_Hp;
	SCENE->m_MaxHp = m_MaxHp;
	SCENE->m_AS_b = m_AS_b;
	SCENE->m_AS_s = m_AS_s;
	SCENE->m_damage = m_damage;
	SCENE->m_Exp = m_Exp;
	SCENE->m_MaxExp = m_MaxExp;
	SCENE->m_Level = m_Level;
	SCENE->Score = Score;
}

void cPlayer::Update()
{
	if (m_Hp <= 0)
	{
		m_Hp = 0;
		b_invincible = true;
		SCENE->ChangeScene("cResultScene");
	}
	Move();
	FireBullet();
	TimerUpdate();
	OutMap();
	SkillUpdate();
	ItemUpdate();
	LvUpdate();
	ScoreUpdate();
	Cheat();
}

void cPlayer::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("1B"), m_pos);
	SkillRender();
}

void cPlayer::UIRender()
{
	RECT hprc = {
		0,
		0,
		((float)IMAGE->FindImage("hpgauge")->info.Width / m_MaxHp) * m_Hp,
		IMAGE->FindImage("hpgauge")->info.Height
	};
	UI->CropRender(IMAGE->FindImage("hpgauge"), Vec2(280, 50), hprc);
	UI->CenterRender(IMAGE->FindImage("hp_frame"), Vec2(280, 50));
	RECT exprc = {
		0,
		0,
		((float)IMAGE->FindImage("expgauge")->info.Width / m_MaxExp) * m_Exp,
		IMAGE->FindImage("expgauge")->info.Height
	};
	UI->CropRender(IMAGE->FindImage("expgauge"), Vec2(280, 96), exprc);
	UI->CenterRender(IMAGE->FindImage("exp_frame"), Vec2(280, 96));
	UI->PrintText(to_string(m_Level), Vec2(30, 70), 45);
	char score[15];
	sprintf(score, "%012d", Score);
	UI->PrintText(score, Vec2(280, 140), 45);

	if (INPUT->KeyPress(VK_F7))
	{
		int Exp = 0;
		for (int i = 1; i < m_Level; i++)
			Exp += (i + 1) * 1000;
		UI->PrintText("EXP : " + to_string((int)m_Exp + Exp), Vec2(150, 300), 45);
		UI->PrintText("Lv 1 = 0", Vec2(50, 350), 45, 0);
		UI->PrintText("Lv 2 = 2000", Vec2(50, 400), 45, 0);
		UI->PrintText("Lv 3 = 5000", Vec2(50, 450), 45, 0);
		UI->PrintText("Lv 4 = 9000", Vec2(50, 500), 45, 0);
		UI->PrintText("Lv 5 = 14000 ", Vec2(50, 550), 45, 0);
	}
}

void cPlayer::FireBullet()
{
	if (INPUT->KeyDown(VK_SPACE)) b_spread = !b_spread;
	if (INPUT->KeyPress(90) && shot)
	{
		SOUND->Play("impact-4")->SetVolume(-1800);
		if (!b_spread)
		{
			shot = false;
			pAS = new cTimer(m_AS_b, [&]()->void {shot = true; pAS = nullptr; });
			m_bullet.push_back(new cPNBullet(m_pos));
			m_bullet.push_back(new cPNBullet(Vec2(m_pos.x - 15, m_pos.y + 15)));
			m_bullet.push_back(new cPNBullet(Vec2(m_pos.x + 15, m_pos.y + 15)));
		}
		else
		{
			shot = false;
			pAS = new cTimer(m_AS_s, [&]()->void {shot = true; pAS = nullptr; });
			m_bullet.push_back(new cPNBullet(m_pos));
			m_bullet.push_back(new cPNBullet(Vec2(m_pos.x - 10, m_pos.y + 5), Vec2(0.0625, 1)));
			m_bullet.push_back(new cPNBullet(Vec2(m_pos.x - 15, m_pos.y + 10), Vec2(0.125, 1)));
			m_bullet.push_back(new cPNBullet(Vec2(m_pos.x - 20, m_pos.y + 15), Vec2(0.1875, 1)));
			m_bullet.push_back(new cPNBullet(Vec2(m_pos.x + 10, m_pos.y + 5), Vec2(-0.0625, 1)));
			m_bullet.push_back(new cPNBullet(Vec2(m_pos.x + 15, m_pos.y + 10), Vec2(-0.125, 1)));
			m_bullet.push_back(new cPNBullet(Vec2(m_pos.x + 20, m_pos.y + 15), Vec2(-0.1875, 1)));
		}
	}
}

void cPlayer::Move()
{
	if (INPUT->KeyPress(VK_UP)) m_pos.y -= 450 * DXUTGetElapsedTime();
	if (INPUT->KeyPress(VK_DOWN)) m_pos.y += 450 * DXUTGetElapsedTime();
	if (INPUT->KeyPress(VK_LEFT)) m_pos.x -= 450 * DXUTGetElapsedTime();
	if (INPUT->KeyPress(VK_RIGHT)) m_pos.x += 450 * DXUTGetElapsedTime();
}

void cPlayer::OutMap()
{
	if(m_pos.x < 0) m_pos.x += 450 * DXUTGetElapsedTime();
	if(m_pos.x > WINSIZEX) m_pos.x -= 450 * DXUTGetElapsedTime();
	if(m_pos.y < 0) m_pos.y += 450 * DXUTGetElapsedTime();
	if(m_pos.y > WINSIZEY) m_pos.y -= 450 * DXUTGetElapsedTime();
}

void cPlayer::TimerUpdate()
{
	if (pAS != nullptr) pAS->Update();
	if (m_shieldT != nullptr) m_shieldT->Update();
	if (m_shieldCT != nullptr) m_shieldCT->Update();
	if (m_bombT != nullptr) m_bombT->Update();
	if (m_bombCT != nullptr) m_bombCT->Update();
}

void cPlayer::TimerDelete()
{
	SAFE_DELETE(pAS);
	SAFE_DELETE(m_shieldT);
	SAFE_DELETE(m_shieldCT);
	SAFE_DELETE(m_bombT);
	SAFE_DELETE(m_bombCT);
	SAFE_DELETE(m_shield);
	SAFE_DELETE(m_bomb);
}

void cPlayer::SkillUpdate()
{
	if (m_shield != nullptr) m_shield->Update(m_pos);
	if (m_bomb != nullptr) m_bomb->Update();
	if (INPUT->KeyDown(88) && !b_shield && m_Level >= 3)
	{
		m_shield = new cShield(m_pos);
		m_shieldT = new cTimer(5, [&]()->void {SAFE_DELETE(m_shield) m_shieldT = nullptr; });
		m_shieldCT = new cTimer(30, [&]()->void {b_shield = false; m_shieldCT = nullptr; });
		b_shield = true;
	}
	if (INPUT->KeyDown(67) && !b_bomb && m_Level >= 5)
	{
		m_bomb = new cBomb(m_pos);
		m_bombT = new cTimer(3, [&]()->void {SAFE_DELETE(m_bomb) m_bombT = nullptr; });
		m_bombCT = new cTimer(60, [&]()->void {b_bomb = false; m_bombCT = nullptr; });
		b_bomb = true;
		b_bombCreate = true;
	}
}

void cPlayer::SkillRender()
{
	if (m_shield != nullptr) m_shield->Render();
	if (m_bomb != nullptr) m_bomb->Render();
}

void cPlayer::ItemUpdate()
{
	if (m_Hp > m_MaxHp) m_Hp = m_MaxHp;

	if (itemTag == "Heal")
	{
		m_Hp += m_MaxHp * 0.2;
		itemTag = "none";
	}
	if (itemTag == "Cool")
	{
		m_shield = nullptr;
		m_shieldT = nullptr;
		m_bombT = nullptr;
		m_bombCT = nullptr;
		b_bomb = false;
		m_shield = false;
		itemTag = "none";
	}
	if (itemTag == "LvUp" && m_Level < 5)
	{
		b_LevelUP = true;
		itemTag = "none";
	}
}

void cPlayer::LvUpdate()
{
	if (MobTag == "Normal")
		m_Exp += 40;
	if (MobTag == "NormalR")
		m_Exp += 50;
	if (MobTag == "Bullet")
		m_Exp += 60;
	if (MobTag == "BulletR")
		m_Exp += 70;
	if (MobTag == "Glider")
		m_Exp += 200;
	if (MobTag == "GliderR")
		m_Exp += 300;
	if (MobTag == "Destroyer")
		m_Exp += 500;
	if (MobTag == "DestroyerR")
		m_Exp += 700;

	if (m_Exp >= m_MaxExp && m_Level < 5) b_LevelUP = true;
	if (m_Level >= 5) m_MaxExp = m_Exp - 1;
	if (b_LevelUP)
	{
		m_Level++;
		m_Exp = 0;
		m_MaxExp += 1000;
		m_damage = ceil(m_damage + m_damage * 0.2);
		m_MaxHp = ceil(m_MaxHp + m_MaxHp * 0.2);
		m_AS_b = m_AS_b - m_AS_b * 0.2;
		m_AS_s = m_AS_s - m_AS_s * 0.2;
		m_Hp = m_MaxHp;
		b_LevelUP = false;
	}
}

void cPlayer::ScoreUpdate()
{
	if (MobTag == "Normal")
	{
		Score += 10000;
		MobTag = "none";
	}
	if (MobTag == "Normal_R")
	{
		Score += 150000;
		MobTag = "none";
	}
	if (MobTag == "Bullet")
	{
		Score += 15000;
		MobTag = "none";
	}
	if (MobTag == "Bullet_R")
	{
		Score += 200000;
		MobTag = "none";
	}
	if (MobTag == "Glider")
	{
		Score += 4000000;
		MobTag = "none";
	}
	if (MobTag == "Glider_R")
	{
		Score += 10000000;
		MobTag = "none";
	}
	if (MobTag == "Destroyer")
	{
		Score += 25000000;
		MobTag = "none";
	}
	if (MobTag == "Destroyer_R")
	{
		Score += 100000000;
		MobTag = "none";
	}
}

void cPlayer::Cheat()
{
	if (INPUT->KeyDown(VK_F1)) b_invincible = !b_invincible;
	if (INPUT->KeyDown(VK_F2) && m_Level < 5) b_LevelUP = true;
	if (INPUT->KeyDown(VK_F9)) b_LevelUP = true;
	if (INPUT->KeyDown(VK_F10)) { m_Level--; b_LevelUP = true; }
	if (INPUT->KeyDown(VK_F11)) Score += 1000000;
}
