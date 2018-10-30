#pragma once
#include "GameObject.h"
class CHidenObject :
	public CGameObject
{
protected:
	float width;
	float height;

public:
	void GetSize(float &width, float &heigth) { width = this->width; height = this->height; }
	void SetSize(float width, float height) { this->width = width; this->height = height; }

	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

