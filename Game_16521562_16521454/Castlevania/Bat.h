#pragma once
#include "GameObject.h"

#define BAT_WALKING_SPEED 0.05f;

#define BAT_DISTANCE_FLY 10

#define BAT_BBOX_WIDTH 16
#define BAT_BBOX_HEIGHT 15

#define BAT_ANI_LEFT  0
#define BAT_ANI_RIGHT 1


class CBat : public CGameObject
{
public:
	float Height_Fly;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void SetHeightFly(float height_fly);
}; 
