#include "DXUT.h"
#include "cLvUpItem.h"

cLvUpItem::cLvUpItem(Vec2 pos)
	:cItem(pos)
{
	m_itemName = "LvUp";
	m_img = IMAGE->FindImage("LvUp");
}

cLvUpItem::~cLvUpItem()
{
}
