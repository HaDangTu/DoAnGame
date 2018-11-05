#pragma once
#include <cstdlib>
#include <time.h>
#include "GameObject.h"
//#include "Item.h"
#include "Items.h"
#define DAGGER		0
#define HEART		1
#define WHIP_UPDATE	2

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
	//CItem* item;
	CItems *items;
	int Time;
public:
	void Render();
	void GetBoundingBox(float & left, float & top, float &right, float & bottom);
	void SetState(int state);
	//CItem* GetItem() { return item; }
	CItems *GetItems() { return items; }

	CCandle()
	{
		hiteffect = new Chiteffect();

		int random;
		srand(time(NULL));
		random = rand() % 2;

		switch (random)
		{
		case 0:
			items = new CDagger();
			break;
		case 1:
			random = rand() % 2;
			switch (random)
			{
			case 0:
				items = new CHeart(HEART_BIG);
				break;
			case 1:
				items = new CHeart(HEART_SMALL);
				break;
			}
			break;
		}
		items->LoadData();
		//items->SetState(0);
	}
	CCandle(int item) 
	{
		hiteffect = new Chiteffect();
		switch (item)
		{
		case DAGGER:
			items = new CDagger();
			break;
		case HEART:
			int random = rand() % 2;
			switch (random)
			{
			case 0:
				items = new CHeart(HEART_BIG);
				break;
			case 1:
				items = new CHeart(HEART_SMALL);
				break;
			}
			break;
		}
		items->LoadData();
	}
};

