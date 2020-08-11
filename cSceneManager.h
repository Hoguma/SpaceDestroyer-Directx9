#pragma once
#include "singleton.h"
struct Rank
{
	char Name[15] = "\0";
	char Score[15] = "\0";
};
class cSceneManager : public singleton<cSceneManager>
{
public:
	cScene* nowScene;
	cScene* nextScene;
	map<string, cScene*> m_scenes;

	list<Rank> ranklist;

	cSceneManager();
	~cSceneManager();

	cScene* AddScene(const string& key, cScene* ptr);
	cScene* ChangeScene(const string& key);

	float m_Hp;
	float m_MaxHp;
	float m_AS_b;
	float m_AS_s;
	float m_damage;
	int	m_Exp;
	int m_MaxExp;
	int m_Level;
	int Score;

	void Update();
	void Render();
	void UIRender();
	void Release();

	void PlayerInit();
	void Cheat();

	void RankRead();
	void RankWrite();
	void RankSort();
	void RankReset();
};

#define SCENE cSceneManager::GetInstance()