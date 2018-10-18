#include "Bat.h"

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (y  > Height_Fly + BAT_DISTANCE_FLY)
	{
		y = Height_Fly + BAT_DISTANCE_FLY;
		vy = -vy;
	}
	if (y  > Height_Fly - BAT_DISTANCE_FLY)
	{
		y = Height_Fly - BAT_DISTANCE_FLY;
		vy = -vy;
	}


}

void CBat::Render()
{
	int ani;
	if (nx > 0)
		ani = BAT_ANI_RIGHT;
	else
		ani = BAT_ANI_LEFT;
	animations[ani]->Render(x, y);
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_ANI_RIGHT:
		vx = BAT_WALKING_SPEED;
		nx = 1;
		break;
	case BAT_ANI_LEFT:
		vx = -BAT_WALKING_SPEED;
		nx = -1;
		break;
	}
}

void CBat::SetHeightFly(float height_fly)
{
	Height_Fly = height_fly;
}
