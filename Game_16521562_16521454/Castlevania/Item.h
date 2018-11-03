#pragma once
#include "GameObject.h"
#define ITEM_GRAVITY  0.01f

#define HEART_SMALL_BBOX_WIDTH 8
#define HEART_SMALL_BBOX_HEIGHT 9
#define HEART_BIG_BBOX_WIDTH 12
#define HEART_BIG_BBOX_HEIGHT 9
#define WHIP_UPDATE_BBOX_WIDTH 18
#define WHIP_UPDATE_BBOX_HEIGHT 16


#define ITEM_STATE_DELETE 0
#define ITEM_STATE_HEART_SMALL 1
#define ITEM_STATE_HEART_BIG 2
#define ITEM_STATE_WHIP_UPDATE 3
#define ID_ITEM 11
#define ITEM_TEXTURE_PATH L"Item.png"
class CItem : public CGameObject
{
public:
	int tao = false;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void loaddata();
	CItem(int state);
	~CItem();
};
