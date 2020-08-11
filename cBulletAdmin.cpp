#include "DXUT.h"
#include "cBulletAdmin.h"

cBulletAdmin::cBulletAdmin()
{
}

cBulletAdmin::~cBulletAdmin()
{
	for (auto iter : b) SAFE_DELETE(iter);
	b.clear();
}

void cBulletAdmin::Update()
{
	for (auto iter : b) iter->Update();
	IsOut();
	IsDestroy();
}

void cBulletAdmin::Render()
{
	for (auto iter : b) iter->Render();
}

void cBulletAdmin::IsOut()
{
	size_t size = b.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = b[i];
		if (iter->IsOutMap())
		{
			SAFE_DELETE(iter);
			b.erase(b.begin() + i);
			i--; size--;
		}
	}
}

void cBulletAdmin::IsDestroy()
{
	size_t size = b.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = b[i];
		if (iter->isDestroy)
		{
			SAFE_DELETE(iter);
			b.erase(b.begin() + i);
			i--; size--;
		}
	}
}
