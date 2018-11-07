#pragma once
#include "GameObject.h"
#include <vector>
using namespace std;

#define WHITE_WHIP	0
#define BLUE_WHIP	1
#define YELLOW_WHIP 2
#define RED_WHIP 3

#define WHITE_WHIP_BBOX_WIDTH	22
#define WHITE_WHIP_BBOX_HEIGHT	8

#define BLUE_WHIP_BBOX_WIDTH	24
#define BLUE_WHIP_BBOX_HEIGHT	8

#define YELLOW_WHIP_BBOX_WIDTH	39
#define YELLOW_WHIP_BBOX_HEIGHT	8

#define RED_WHIP_BBOX_WIDTH	   39
#define RED_WHIP_BBOX_HEIGHT	8

#define WHIP_STATE_LEFT 0
#define WHIP_STATE_RIGHT 1
class CWhip :
	public CGameObject
{
	DWORD lastFrameTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	int state_whip;
public:
	void LoadAnimaion();
	bool fight;
	CWhip();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void SetState(int state);
	void SetStateWhip(int state_whip){ this->state_whip = state_whip;}
};

