#pragma once
#include "GameObject.h"

#define GHOUL_WALKING_SPEED 0.05f;

#define GHOUL_BBOX_WIDTH 16
#define GHOUL_BBOX_HEIGHT 15
#define GHOUL_ANI_LEFT  0
#define GHOUL_ANI_RIGHT 1

class CGhoul : public CGameObject
{
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
};