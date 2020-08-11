#include "DXUT.h"
#include "cStage2Scene.h"

cStage2Scene::cStage2Scene()
{
}

cStage2Scene::~cStage2Scene()
{
	Release();
}

void cStage2Scene::Init()
{
	srand(time(NULL));
	bullet = new cBulletAdmin();
	map = new cSrollMap(IMAGE->FindImage("background"));
	player = new cPlayer(bullet->b);
	mob = new cMobAdmin(player, bullet->b);
	item = new cItemAdmin(player);
	coll = new cCollision(mob->mobs, bullet->b, item, player);
	SOUND->StopAll();
	SOUND->Play("Main Music 9000", 1)->SetVolume(-1500);
}

void cStage2Scene::Update()
{
	player->Update();
	bullet->Update();
	mob->Update();
	map->Update(50);
	item->Update();
	coll->Update();
	if (mob->BossDead) SCENE->ChangeScene("cResultScene");
}

void cStage2Scene::Render()
{
	map->Render();
	bullet->Render();
	mob->Render();
	player->Render();
	item->Render();
}

void cStage2Scene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cStage2Scene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(map);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}
