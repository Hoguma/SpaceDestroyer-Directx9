#include "DXUT.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
	:nowScene(nullptr), nextScene(nullptr)
{
	PlayerInit();
}

cSceneManager::~cSceneManager()
{
	Release();
}

cScene* cSceneManager::AddScene(const string& key, cScene* ptr)
{
	if (!ptr) return nullptr;
	if (m_scenes.find(key) != m_scenes.end()) return nullptr;
	m_scenes.insert(make_pair(key, ptr));
	return ptr;
}

cScene* cSceneManager::ChangeScene(const string& key)
{
	auto find = m_scenes.find(key);
	if (find == m_scenes.end()) return nullptr;
	nextScene = find->second;
	return nextScene;
}

void cSceneManager::Update()
{
	Cheat();
	if (nextScene)
	{
		if (nowScene) nowScene->Release();
		nextScene->Init();
		nowScene = nextScene;
		nextScene = nullptr;
	}
	if(nowScene) nowScene->Update();
}

void cSceneManager::Render()
{
	if (nowScene) nowScene->Render();
}

void cSceneManager::UIRender()
{
	if (nowScene) nowScene->UIRender();
}

void cSceneManager::Release()
{
	if (nowScene) nowScene->Release();
	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();
}

void cSceneManager::PlayerInit()
{
	m_Hp = 100;
	m_MaxHp = 100;
	m_AS_b = 0.2;
	m_AS_s = 0.4;
	m_damage = 10;
	m_Exp = 0;
	m_MaxExp = 2000;
	m_Level = 1;
	Score = 0;
}

void cSceneManager::Cheat()
{
}

void cSceneManager::RankRead()
{
	ranklist.clear();
	ifstream file_r("Ranking.txt");
	if (file_r.is_open() == false)
	{
		ofstream file_w("Ranking.txt");
		for (int i = 0; i < 10; i++)
		{
			file_w << "NONE" << endl;
			file_w << "0" << endl;
		}
		file_w.close();
		file_r.open("Ranking.txt");
	}
	for (int i = 0; i < 10; i++)
	{
		Rank temp;
		file_r.getline(temp.Name, 100);
		file_r.getline(temp.Score, 100);
		ranklist.push_back(temp);
	}
	file_r.close();
}

void cSceneManager::RankWrite()
{
	ofstream file_w("Ranking.txt");
	for (auto iter : ranklist)
	{
		file_w << iter.Name << endl;
		file_w << iter.Score << endl;
	}
	file_w.close();
}

void cSceneManager::RankSort()
{
	ranklist.sort([&](Rank prev, Rank next)->bool { return atoi(prev.Score) > atoi(next.Score); });
}

void cSceneManager::RankReset()
{
	ofstream file_w("Ranking.txt");
	for (int i = 0; i < 10; i++)
	{
		file_w << "NONE" << endl;
		file_w << "0" << endl;
	}
	file_w.close();
}
