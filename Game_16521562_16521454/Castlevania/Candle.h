#pragma once
#include "GameObject.h"

#define CANDLE_STATE_DISAPPEAR	10
#define CANDLE_STATE_NORMAL 0
#define CANDLE_BBOX_WIDTH	18
#define CANDLE_BBOX_HEIGHT	34
class CCandle :
	public CGameObject
{
public:
	void Render();
	void GetBoundingBox(float & left, float & top, float &right, float & bottom);
	void SetState(int state);
};

