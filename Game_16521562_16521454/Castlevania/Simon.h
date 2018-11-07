#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "InputImage.h"
#include <vector>
#include "Items.h"
using namespace std;
#define WHIP_TEXTURE_PATH L"castlevania_texture\\Weapon\\Whip.png"

#define SIMON_WALKING_SPEED		0.1f
#define SIMON_JUMP_SPEED		0.2f
#define SIMON_GRAVITY			0.01f
#define SIMON_DEFLECT_SPEED		0.1f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_LEFT	1
#define SIMON_STATE_WALKING_RIGHT	2
#define SIMON_STATE_JUMP			3
#define SIMON_STATE_KNEE			4
#define SIMON_STATE_DIE				5
#define SIMON_STATE_UPDATE          6

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
#define SIMON_BBOX_IDLE_HEIGHT		35

#define SIMON_BBOX_KNEE_WIDTH		18
#define SIMON_BBOX_KNEE_HEIGHT		25

#define SIMON_BBOX_KNEE_FIGHT_WIDTH		18
#define SIMON_BBOX_KNEE_FIGHT_HEIGHT	25

class CSimon :public CGameObject
{
	int heart=0;
	int mx;
	int previousstate;
	int state_update;
	CWhip *whip;
	DWORD FrameUpdate;
	DWORD FrameWeapon;
	bool OnSkill = false;
	bool skill = false;
	bool jump = true;
	bool fight = false;
	int alpha = 255;
	CItems* weapon;
public:
	DWORD FrameStart;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	int GetPreviousState();
	void SetState(int state);
	bool GetSkill() { return skill; }
	void SetSkill(bool skill) { this->skill = skill; }
	bool GetJump() { return jump; }
	void SetJump(bool jump) { this->jump = jump; }
	bool GetFight() { return fight; }
	void SetFight(bool fight) { this->fight = fight; }
	void SetFramWeapon() { FrameWeapon = GetTickCount(); }
	DWORD GetFramWeapon() { return FrameWeapon; }
	bool GetOnSkill() { return OnSkill; }
	CItems* GetWeapon() { return weapon; }
	DWORD GetFrameUpdate()
	{
		return FrameUpdate;
	}
	CSimon() :CGameObject()
	{
		mx = 0;
		previousstate = state;
		whip = new CWhip();
		whip->SetState(WHITE_WHIP);
		whip->AddAnimation(2000);
		whip->AddAnimation(2001);
		whip->AddAnimation(2002);
		whip->AddAnimation(2003);
		whip->AddAnimation(2004);
		whip->AddAnimation(2005);
		whip->AddAnimation(2006);
		whip->AddAnimation(2007);

	}

};

