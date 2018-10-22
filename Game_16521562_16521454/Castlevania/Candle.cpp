#include "Candle.h"



void CCandle::Render()
{
	if (state != CANDLE_STATE_DISAPPEAR)
		animations[0]->Render(x, y);
	else
	{
	}
}

void CCandle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BBOX_WIDTH;
	bottom = y + CANDLE_BBOX_HEIGHT;
}

void CCandle::SetState(int state)
{
	switch (state)
	{
	case CANDLE_STATE_DISAPPEAR:
		break;
	}
}

