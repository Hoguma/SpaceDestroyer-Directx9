#include "DXUT.h"
#include "cResultScene.h"


cResultScene::cResultScene()
{
	SCENE->RankSort();
}

cResultScene::~cResultScene()
{
}

void cResultScene::Init()
{
	type = true;
	nameNum = 0;
	SOUND->StopAll();
	SOUND->Play("Crate Waltz", 1)->SetVolume(-1000);
}

void cResultScene::Update()
{
	if (type)
	{
		for (int i = 0; i < 256; i++)
		{
			if (INPUT->KeyDown(i) && nameNum != 3 && i != VK_BACK)
			{
				m_name[nameNum] = i;
				nameNum++;
			}
		}
		if (INPUT->KeyDown(VK_BACK) && nameNum != 0)
		{
			m_name[nameNum] = ' ';
			nameNum--;
		}
		if (INPUT->KeyDown(VK_RETURN))
		{
			type = false;
			Rank m_rank;
			for (int i = 0; i < 15; i++)
			{
				m_rank.Name[i] = ' ';
				m_rank.Score[i] = ' ';
			}
			for (int i = 0; i < 15; i++)
			{
				m_rank.Name[i] = m_name[i];
			}
			itoa(SCENE->Score, m_rank.Score, 10);
			SCENE->ranklist.push_back(m_rank);
			SCENE->RankSort();
			SCENE->RankWrite();
		}
	}
	else
		if (INPUT->KeyDown(VK_RETURN)) SCENE->ChangeScene("cMainScene");
}

void cResultScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("background3"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
}

void cResultScene::UIRender()
{
	UI->PrintText("Ranking", Vec2(WINSIZEX / 2, 350), 100);
	UI->PrintText(to_string(SCENE->Score), Vec2(1450, 450), 100);

	for (int i = 0; i < 3; i++)
	{
		char text[2];
		sprintf(text, "%c", m_name[i]);
		UI->PrintText(text, Vec2(450 + i * 40, 450), 100);
	}

	int i = 550;
	char Name[15] = "\0";
	char score[15] = "\0";
	for (auto& iter : SCENE->ranklist)
	{
		if (i == 950) break;
		for (int i = 0; i < 15; i++)
		{
			Name[i] = iter.Name[i];
			score[i] = iter.Score[i];
		}
		UI->PrintText(Name, Vec2(600, i), 70 , 0);
		UI->PrintText(score, Vec2(1200, i), 70, 0);
		i += 80;
	}
}

void cResultScene::Release()
{
	for (int i = 0; i < 15; i++)
		m_name[i] = ' ';
	m_name[0] = '?';
	m_name[1] = '?';
	m_name[2] = '?';
	m_name[3] = '\0';
}
