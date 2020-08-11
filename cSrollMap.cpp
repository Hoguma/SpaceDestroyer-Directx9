#include "DXUT.h"
#include "cSrollMap.h"

cSrollMap::cSrollMap(cTexture* img)
	:m_scroll(0), m_img(img)
{
}

cSrollMap::~cSrollMap()
{
}

void cSrollMap::Update(float speed)
{
	m_scroll += speed * Delta;
}

void cSrollMap::Render()
{
	float renderPos = (int)m_scroll % m_img->info.Height;
	RENDER->CenterRender(m_img, Vec2(WINSIZEX / 2, WINSIZEY / 2 + renderPos - m_img->info.Height));
	RENDER->CenterRender(m_img, Vec2(WINSIZEX / 2, WINSIZEY / 2 + renderPos));
}
