#include "Candle.h"



void CCandle::Render()
{
	if (state == CANDLE_STATE_NORMAL)
	{
		animations[0]->Render(x, y);
	}
	else if (state == CANDLE_STATE_DISAPPEAR)
	{
		int now = GetTickCount();
		Chiteffect *hiteffect = new Chiteffect();
		hiteffect->SetXY(x, y);
		hiteffect->Render();
		if (now - time >= FrameTime)
			SetState(CANDLE_STATE_DELETE);
	}
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
	CGameObject::SetState(state);
	switch (state)
	{
	case CANDLE_STATE_NORMAL:
		break;
	case CANDLE_STATE_DISAPPEAR:
		time = GetTickCount();
		break;
	case CANDLE_STATE_DELETE:
		break;
	}
}

