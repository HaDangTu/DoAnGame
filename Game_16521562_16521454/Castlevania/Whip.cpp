#include "Whip.h"
#include "Candle.h"
#include <vector>
using namespace std;


void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	CalcPotentialCollisions(coObjects, coEvents);

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (dynamic_cast<CCandle *> (e->obj))
		{
			CCandle  *candle = dynamic_cast<CCandle *>(e->obj);
			if (candle->GetState() != CANDLE_STATE_DISAPPEAR)
				candle->SetState(CANDLE_STATE_DISAPPEAR);
		}
	}

}

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

