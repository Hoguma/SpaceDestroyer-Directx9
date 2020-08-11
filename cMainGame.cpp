#include "DXUT.h"
#include "cMainGame.h"
#include "cStage1Scene.h"
#include "cStage2Scene.h"
#include "cMainScene.h"
#include "cResultScene.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	AddResource();
	SCENE->AddScene("cStage1Scene", new cStage1Scene);
	SCENE->AddScene("cStage2Scene", new cStage2Scene);
	SCENE->AddScene("cMainScene", new cMainScene);
	SCENE->AddScene("cResultScene", new cResultScene);
	SCENE->ChangeScene("cMainScene");
}

void cMainGame::Update()
{
	INPUT->Update();
	SCENE->Update();
	PART->Update();
	SOUND->Update();
}

void cMainGame::Render()
{
	SCENE->Render();
	PART->Render();
	UI->Begin();
	SCENE->UIRender();
	UI->End();
}

void cMainGame::Release()
{
	cImageManager::ReleaseInstance();
	cInputManager::ReleaseInstance();
	cRenderManager::ReleaseInstance();
	cSoundManager::ReleaseInstance();
	cParticleManager::ReleaseInstance();
	cSceneManager::ReleaseInstance();
	cUIManager::ReleaseInstance();
}

void cMainGame::LostDevice()
{
	UI->LostDevice();
}

void cMainGame::ResetDevice()
{
	UI->ResetDevice();
}

void cMainGame::AddResource()
{
	IMAGE->AddImage("1B", "1B");
	IMAGE->AddImage("8", "8");
	IMAGE->AddImage("8B", "8B");
	IMAGE->AddImage("9", "9");
	IMAGE->AddImage("9B", "9B");
	IMAGE->AddImage("background", "background");
	IMAGE->AddImage("background2", "background2");
	IMAGE->AddImage("background3", "background3");
	IMAGE->AddImage("background4", "background4");
	IMAGE->AddImage("cooldown", "cooldown");
	IMAGE->AddImage("CReset", "CReset");
	IMAGE->AddImage("EB", "EB");
	IMAGE->AddImage("exp_frame", "exp_frame");
	IMAGE->AddImage("expgauge", "expgauge");
	IMAGE->AddImage("expl_image", "expl_image");
	IMAGE->AddImage("Heal", "Heal");
	IMAGE->AddImage("help", "help");
	IMAGE->AddImage("hp_frame", "hp_frame");
	IMAGE->AddImage("hpgauge", "hpgauge");
	IMAGE->AddImage("Hull", "Hull");
	IMAGE->AddImage("Hull_R", "Hull_R");
	IMAGE->AddImage("Hull2", "Hull2");
	IMAGE->AddImage("Hull2_R", "Hull2_R");
	IMAGE->AddImage("LvUp", "LvUp");
	IMAGE->AddImage("PB", "PB");
	IMAGE->AddImage("Razer", "Razer");
	IMAGE->AddImage("spr_shield", "spr_shield");
	IMAGE->AddImage("spr_shield_image", "spr_shield_image");
	IMAGE->AddImage("expl", "Effect/expl", 32);

	SOUND->AddSound("Crate Waltz", L"Crate Waltz");
	SOUND->AddSound("explosion-2", L"explosion-2");
	SOUND->AddSound("impact-4", L"impact-4");
	SOUND->AddSound("Buttons", L"Buttons");
	SOUND->AddSound("Main Music 9000", L"Main Music 9000");
	SOUND->AddSound("MG 2", L"MG 2");
	SOUND->AddSound("Powerup Collect", L"Powerup Collect");
}
