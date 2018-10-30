#include "Map.h"

CMap::CMap()
{
	
}


CMap::~CMap()
{
}

void CMap::Render()
{
	animations[0]->Render(x, y);
}

void CMap::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	//CGameObject::GetBoundingBox(left,top,right, bottom);
}
