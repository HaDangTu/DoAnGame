#pragma once
#include "GameObject.h"

#define PANTHER_WALKING_SPEED 0.05f

#define PANTHER_JUMP_SPEED_X  0.1f
#define PANTHER_JUMP_SPEED_Y  0.5f
#define PANTHER_GRAVITY       0.002f

#define PANTHER_BBOX_WIDTH 16
#define PANTHER_BBOX_HEIGHT 15

#define PANTHER_STATE_IDLE          0     
#define PANTHER_STATE_WALKING_RIGHT 100
#define PANTHER_STATE_WALKING_LEFT  200
#define PANTHER_STATE_JUMP_RIGHT    300
#define PANTHER_STATE_JUMP_LEFT     400

#define PANTHER_ANI_IDLE_RIGHT    0
#define PANTHER_ANI_IDLE_LEFT     1
#define PANTHER_ANI_WALKING_RIGHT 2
#define PANTHER_ANI_WALKING_LEFT  3
#define PANTHER_ANI_JUMP_RIGHT    4
#define PANTHER_ANI_JUMP_LEFT     5


class CPanther : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void SetState(int state);
};