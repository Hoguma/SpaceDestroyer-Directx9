#pragma once
class cSrollMap
{
public:
	cSrollMap(cTexture* img);
	~cSrollMap();

	cTexture* m_img;
	float m_scroll;

	void Update(float speed);
	void Render();
};

