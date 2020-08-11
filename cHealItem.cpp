#include "DXUT.h"
#include "cHealItem.h"

cHealItem::cHealItem(Vec2 pos)
	:cItem(pos)
{
	m_itemName = "Heal";
	m_img = IMAGE->FindImage("Heal");
}

cHealItem::~cHealItem()
{
}
