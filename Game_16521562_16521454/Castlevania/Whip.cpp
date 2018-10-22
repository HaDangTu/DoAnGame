#include "Whip.h"



void CWhip::Render()
{
	animations[0]->Render(x, y);
}
void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{

}
void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == SHORT_WHIP)
	{
		right = x + SHORT_WHIP_BBOX_WIDTH;
		bottom = y + SHORT_WHIP_BBOX_HEIGHT;
	}
	else
	{
		right = x + LONG_WHIP_BBOX_WIDTH;
		bottom = y + LONG_WHIP_BBOX_HEIGHT;
	}
}

