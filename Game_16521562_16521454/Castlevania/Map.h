#pragma once
#include "GameObject.h"
#include "HidenObject.h"
#include <vector>
using namespace std;

class CMap:public CGameObject
{
	;
public:
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CMap();
	~CMap();
};

