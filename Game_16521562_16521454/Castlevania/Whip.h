#pragma once
#include "GameObject.h"
#include <vector>
using namespace std;

#define SHORT_WHIP	1
#define LONG_WHIP	2

#define WHIP_ANI_LEFT		0
#define WHIP_ANI_RIGHT		1

#define SHORT_WHIP_BBOX_WIDTH	28
#define SHORT_WHIP_BBOX_HEIGHT	10

#define LONG_WHIP_BBOX_WIDTH	44
#define LONG_WHIP_BBOX_HEIGHT	10

class CWhip :
	public CGameObject
{
	DWORD lastFrameTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	void LoadAnimaion();
	bool fight;
public:
	CWhip();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void Render(int ani);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
};

