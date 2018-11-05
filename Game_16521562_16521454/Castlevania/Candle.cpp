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
		hiteffect->SetPosition(x, y);
		//item->SetPosition(x+5, y+10);
		items->SetPosition(x + 5, y + 10);
		hiteffect->Render();
		if (now - Time >= FrameTime)
			SetState(CANDLE_STATE_DELETE);
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
		Time = GetTickCount();
		break;
	case CANDLE_STATE_DELETE:
		break;
	}
}


