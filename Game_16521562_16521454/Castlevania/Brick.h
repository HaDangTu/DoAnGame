#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH	15
#define BRICK_BBOX_HEIGHT	15

class CBrick:public CGameObject
{

public:
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	
};

