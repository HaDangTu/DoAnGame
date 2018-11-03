#pragma once
#include "GameObject.h"
#include <vector>
using namespace std;

#define WHITE_WHIP	0
#define BLUE_WHIP	1
#define YELLOW_WHIP 2
#define RED_WHIP 3

#define WHIP_ANI_LEFT		0
#define WHIP_ANI_RIGHT		1

#define WHITE_WHIP_BBOX_WIDTH	22
#define WHITE_WHIP_BBOX_HEIGHT	8

#define BLUE_WHIP_BBOX_WIDTH	24
#define BLUE_WHIP_BBOX_HEIGHT	8

#define YELLOW_WHIP_BBOX_WIDTH	24
#define YELLOW_WHIP_BBOX_HEIGHT	8

#define RED_WHIP_BBOX_WIDTH	   24
#define RED_WHIP_BBOX_HEIGHT	8
class CWhip :
	public CGameObject
{
	DWORD lastFrameTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	void LoadAnimaion();
public:
	bool fight;
	CWhip();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void Render(int ani);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void SetState(int state);
};

