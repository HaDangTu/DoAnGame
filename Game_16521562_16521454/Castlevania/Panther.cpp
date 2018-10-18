#include "Panther.h"

void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += PANTHER_GRAVITY * dt;

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

void CPanther::Render()
{
	int ani;
	if (state = PANTHER_STATE_IDLE)
	{
		if (nx > 0) ani = PANTHER_ANI_IDLE_RIGHT;
		else ani = PANTHER_ANI_IDLE_LEFT;
	}
	if (state = PANTHER_STATE_JUMP_RIGHT)
	{
		ani = PANTHER_ANI_JUMP_RIGHT;
	}
	if (state = PANTHER_STATE_JUMP_LEFT)
	{
		ani = PANTHER_ANI_JUMP_LEFT;
	}
	if (state = PANTHER_STATE_WALKING_RIGHT)
	{
		ani = PANTHER_ANI_WALKING_RIGHT;
	}
	if (state = PANTHER_STATE_WALKING_LEFT)
	{
		ani = PANTHER_ANI_WALKING_LEFT;
	}
	animations[ani]->Render(x, y);
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PANTHER_STATE_WALKING_RIGHT:
		vx = PANTHER_WALKING_SPEED;
		nx = 1;
		break;
	case PANTHER_STATE_WALKING_LEFT:
		vx = -PANTHER_WALKING_SPEED;
		nx = -1;
		break;
	case PANTHER_STATE_JUMP_RIGHT:
		vy = -PANTHER_JUMP_SPEED_Y;
		vx = PANTHER_JUMP_SPEED_X;
		nx = 1;
		break;
	case PANTHER_STATE_JUMP_LEFT:
		vy = -PANTHER_JUMP_SPEED_Y;
		vx = -PANTHER_JUMP_SPEED_X;
		nx = -1;
		break;
	case PANTHER_STATE_IDLE: 
		vx = 0;
		break;
	}
}
