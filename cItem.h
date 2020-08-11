#pragma once
class cItem
{
public:
	Vec2 m_pos;
	cTexture* m_img;
	float m_size = 30;
	string m_itemName;
	bool isDestroy = false;

	cItem(Vec2 pos);
	virtual ~cItem();

	void Update();
	void Render();

	bool IsOutMap();
};

