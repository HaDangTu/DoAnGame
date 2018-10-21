#pragma once
#include "GameObject.h"

#define FISHMAN_WALKING_SPEED 0.05f

#define FISHMAN_JUMP_SPEED_Y  0.7f
#define FISHMAN_GRAVITY       0.002f

#define FISHMAN_BBOX_WIDTH 17
#define FISHMAN_BBOX_HEIGHT 34

#define FISHMAN_STATE_WALKING_RIGHT 0
#define FISHMAN_STATE_WALKING_LEFT  100
#define FISHMAN_STATE_JUMP          200
#define FISHMAN_STATE_FIRE          300

#define FISHMAN_ANI_FIRE_LEFT     0
#define FISHMAN_ANI_JUMP_LEFT     1
#define FISHMAN_ANI_WALKING_LEFT  2
#define FISHMAN_ANI_FIRE_RIGHT    3
#define FISHMAN_ANI_JUMP_RIGHT    4
#define FISHMAN_ANI_WALKING_RIGHT 5



class CFishman : public CGameObject
{
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
};