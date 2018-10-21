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

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.2f;
		if (ny < 0)
		{
			if (nx < 0)
				SetState(FISHMAN_STATE_WALKING_LEFT);
			else
				SetState(FISHMAN_STATE_WALKING_RIGHT);
			y += min_ty * dy + ny * 0.2f;
		}
		else
			y += dy;
		if (nx != 0) vx = 0;
	}
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
			ani = FISHMAN_ANI_FIRE_RIGHT;
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
