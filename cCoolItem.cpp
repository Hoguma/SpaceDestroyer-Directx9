#include "DXUT.h"
#include "cCoolItem.h"

cCoolItem::cCoolItem(Vec2 pos)
	:cItem(pos)
{
	m_itemName = "Cool";
	m_img = IMAGE->FindImage("CReset");
}

cCoolItem::~cCoolItem()
{
}
