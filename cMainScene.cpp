#include "DXUT.h"
#include "cMainScene.h"

cMainScene::cMainScene()
{
}

cMainScene::~cMainScene()
{
}

void cMainScene::Init()
{
	SOUND->StopAll();
	SCENE->RankRead();
	SCENE->PlayerInit();
}

void cMainScene::Update()
{
	if (INPUT->KeyDown(VK_DOWN) && select < 4)
	{
		select++;
		help = false;
		rank = false;
		button = true;
		SOUND->Play("Buttons")->SetVolume(-1500);
	}
	if (INPUT->KeyDown(VK_UP) && select > 1)
	{
		select--;
		help = false;
		rank = false;
		button = true;
		SOUND->Play("Buttons")->SetVolume(-1500);
	}
	switch (select)
	{
	case 1:
		if (INPUT->KeyDown(90))
			SCENE->ChangeScene("cStage1Scene");
		break;
	case 2:
		if (INPUT->KeyDown(90))
			help = true;
		break;
	case 3:
		if (INPUT->KeyDown(90))
			rank = true;
		break;
	case 4:
		if (INPUT->KeyDown(90))
			exit(0);
		break;
	default:
		break;
	}
}

void cMainScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("background3"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
}

void cMainScene::UIRender()
{
	if (button)
	{
		if (select == 1)
			UI->PrintText("GAME START", Vec2(555, 400), 100);
		else
			UI->PrintText("GAME START", Vec2(555, 400), 80, 1, D3DCOLOR_XRGB(127, 127, 127));
		if (select == 2)
			UI->PrintText("HELP", Vec2(1365, 400), 100);
		else
			UI->PrintText("HELP", Vec2(1365, 400), 80, 1, D3DCOLOR_XRGB(127, 127, 127));
		if (select == 3)
			UI->PrintText("RANK", Vec2(555, 700), 100);
		else
			UI->PrintText("RANK", Vec2(555, 700), 80, 1, D3DCOLOR_XRGB(127, 127, 127));
		if (select == 4)
			UI->PrintText("EXIT", Vec2(1365, 700), 100);
		else
			UI->PrintText("EXIT", Vec2(1365, 700), 80, 1, D3DCOLOR_XRGB(127, 127, 127));
	}
	if (help)
	{
		button = false;
		UI->CenterRender(IMAGE->FindImage("help"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
	}
	if (rank)
	{
		button = false;
		UI->CenterRender(IMAGE->FindImage("background4"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
		UI->PrintText("Ranking", Vec2(WINSIZEX / 2, 150), 100);
		int i = 250;
		char Name[15] = "\0";
		char score[15] = "\0";
		for (auto& iter : SCENE->ranklist)
		{
			if (i == 1000) break;
			for (int i = 0; i < 15; i++)
			{
				Name[i] = iter.Name[i];
				score[i] = iter.Score[i];
			}
			UI->PrintText(Name, Vec2(500, i), 70);
			UI->PrintText(score, Vec2(1400, i), 70);
			i += 150;
		}
	}
}

void cMainScene::Release()
{
}
