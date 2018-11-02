#pragma once
#include "GameObject.h"
#include "Item.h"

#define CANDLE_STATE_DELETE     20
#define CANDLE_STATE_NORMAL 0
#define CANDLE_STATE_DISAPPEAR	10
#define CANDLE_STATE_NORMAL 0
#define CANDLE_BBOX_WIDTH	18
#define CANDLE_BBOX_HEIGHT	34
#define FrameTime 200

class CCandle :
	public CGameObject
{
	Chiteffect *hiteffect;
	CItem* item;
	int time;
public:
	void Render();
	void GetBoundingBox(float & left, float & top, float &right, float & bottom);
	void SetState(int state);
	CCandle()
	{
		hiteffect = new Chiteffect();
		item = new CItem(ITEM_STATE_HEART_SMALL);
	}
};

