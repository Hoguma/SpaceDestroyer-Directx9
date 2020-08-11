#pragma once
#include "cBullet.h"
class cBulletAdmin
{
public:
	vector<cBullet*> b;
	cBulletAdmin();
	~cBulletAdmin();

	void Update();
	void Render();
	void IsOut();
	void IsDestroy();
};

