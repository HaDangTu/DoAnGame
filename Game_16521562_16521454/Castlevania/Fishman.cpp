#include "Fishman.h"

void CFishman::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + FISHMAN_BBOX_WIDTH;
	bottom = y + FISHMAN_BBOX_HEIGHT;
}

void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += FISHMAN_GRAVITY * dt;

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	/*if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}*/
}

void CFishman::Render()
{
	int ani;
	if (vy < 0)
	{
		if (vx < 0)
			ani = FISHMAN_ANI_FIRE_LEFT;
		else
			ani = FISHMAN_ANI_FIRE_RIGHT;
	}
	else if (vx == 0)
	{
		if (vx < 0)
			ani = FISHMAN_ANI_FIRE_LEFT;
		else
			ani= FISHMAN_ANI_FIRE_RIGHT;
	}
	else if (vx > 0)
		ani = FISHMAN_ANI_WALKING_RIGHT;
	else 
		ani = FISHMAN_ANI_WALKING_LEFT;
	animations[ani]->Render(x, y);
}

void CFishman::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FISHMAN_STATE_WALKING_RIGHT:
		vx = FISHMAN_WALKING_SPEED;
		nx = 1;
		break;
	case FISHMAN_STATE_WALKING_LEFT:
		vx = -FISHMAN_WALKING_SPEED;
		nx = -1;
		break;
	case FISHMAN_STATE_JUMP:
		vy = -FISHMAN_JUMP_SPEED_Y;
		break;
	case FISHMAN_STATE_FIRE:
		vx = 0;
		break;
	}
}
