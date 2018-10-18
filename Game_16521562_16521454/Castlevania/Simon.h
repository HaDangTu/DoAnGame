#pragma once
#include "GameObject.h"
#include <vector>
using namespace std;
#define SIMON_WALKING_SPEED		0.1f
#define SIMON_JUMP_SPEED		0.4f
#define SIMON_GRAVITY			0.002f
#define SIMON_DEFLECT_SPEED		0.1f

#define SIMON_STATE_IDLE		0
#define SIMON_STATE_WALKING_LEFT	10
#define SIMON_STATE_WALKING_RIGHT	20
#define SIMON_STATE_JUMP			30
#define SIMON_STATE_KNEE			40
#define SIMON_STATE_DIE				50
#define SIMON_STATE_FIGHT			60

#define SIMON_ANI_WALKING_LEFT		0
#define SIMON_ANI_WALKING_RIGHT		1
#define SIMON_ANI_IDLE_LEFT			2
#define SIMON_ANI_IDLE_RIGHT		3
#define SIMON_ANI_JUMP_LEFT			4
#define SIMON_ANI_JUMP_RIGHT		5
#define SIMON_ANI_FIGHT_LEFT		6
#define SIMON_ANI_FIGHT_RIGHT		7
#define SIMON_ANI_DIE_LEFT			8
#define SIMON_ANI_DIE_RIGHT			9

#define SIMON_BBOX_IDLE_WIDTH		18
#define SIMON_BBOX_IDLE_HEIGHT		34
#define SIMON_BBOX_KNEE_WIDTH		18
#define SIMON_BBOX_KNEE_HEIGHT		25

class CSimon :public CGameObject
{
	int mx;
	int level;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void SetLevel(int level) { this->level = level; }
	void SetState(int state);
	CSimon():CGameObject()
	{
		mx = 0; //not knee
		level = 1;
	}
};

