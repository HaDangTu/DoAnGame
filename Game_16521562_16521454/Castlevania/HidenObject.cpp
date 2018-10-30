#include "HidenObject.h"

void CHidenObject::Render()
{
	//animations[0]->Render(x, y);
}

void CHidenObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
