#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "InputImage.h"
#include <vector>
using namespace std;
#define WHIP_TEXTURE_PATH L"castlevania_texture\\Weapon\\Whip.png"

#define SIMON_WALKING_SPEED		0.1f
#define SIMON_JUMP_SPEED		0.2f
#define SIMON_GRAVITY			0.01f
#define SIMON_DEFLECT_SPEED		0.1f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_LEFT	10
#define SIMON_STATE_WALKING_RIGHT	20
#define SIMON_STATE_JUMP			30
#define SIMON_STATE_KNEE			40
#define SIMON_STATE_DIE				50

#define SIMON_ANI_WALKING_LEFT		0
#define SIMON_ANI_WALKING_RIGHT		1
#define SIMON_ANI_IDLE_LEFT			2
#define SIMON_ANI_IDLE_RIGHT		3
#define SIMON_ANI_JUMP_LEFT			4
#define SIMON_ANI_JUMP_RIGHT		5
#define SIMON_ANI_FIGHT_LEFT		6
#define SIMON_ANI_FIGHT_RIGHT		7
#define SIMON_ANI_KNEE_FIGHT_LEFT	8
#define SIMON_ANI_KNEE_FIGHT_RIGHT	9
#define SIMON_ANI_DIE_LEFT			10
#define SIMON_ANI_DIE_RIGHT			11

#define SIMON_BBOX_IDLE_WIDTH		18
#define SIMON_BBOX_IDLE_HEIGHT		34

#define SIMON_BBOX_KNEE_WIDTH		18
#define SIMON_BBOX_KNEE_HEIGHT		25

#define SIMON_BBOX_KNEE_FIGHT_WIDTH		18
#define SIMON_BBOX_KNEE_FIGHT_HEIGHT	25
class CSimon :public CGameObject
{
	int heart=0;
	int mx;
	int previousstate;
	CWhip *whip;
public:
	bool jump = true;
	bool fight = false;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	int GetPreviousState();
	void SetState(int state);
	CSimon() :CGameObject()
	{
		mx = 0;
		previousstate = state;
		whip = new CWhip();
		whip->AddAnimation(2000);
		whip->AddAnimation(2001);
	}

};

