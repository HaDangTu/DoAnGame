#include "Simon.h"
#include "debug.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
}

void CSimon::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0)
		{
			ani = SIMON_ANI_IDLE_RIGHT;
			if (mx > 0) ani = SIMON_ANI_JUMP_RIGHT; //SIMON_ANI_KNEE_RIGHT
			if (state == SIMON_STATE_FIGHT)
				ani = SIMON_ANI_FIGHT_RIGHT;
				//DebugOut(L"ani: %d", ani);
		}
		else
		{
			ani = SIMON_ANI_IDLE_LEFT;
			if (mx > 0) ani = SIMON_ANI_JUMP_LEFT; //SIMON_ANI_KNEE_LEFT
			if (state == SIMON_STATE_FIGHT) ani = SIMON_ANI_FIGHT_LEFT;
		}
	}
	else
	{
		if (nx < 0) ani = SIMON_ANI_WALKING_LEFT;
		else
			ani = SIMON_ANI_WALKING_RIGHT;
	}

	if (vy < 0 && nx < 0)
		ani = SIMON_ANI_JUMP_LEFT;
	else if (vy < 0 && nx > 0)
		ani = SIMON_ANI_JUMP_RIGHT;
	
	animations[ani]->Render(x, y, 255);
	RenderBoundingBox();
}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	left = x;
	top = y;
	if (vx == 0 && mx == 1)
	{
		right = x + SIMON_BBOX_KNEE_WIDTH;
		bottom = y + SIMON_BBOX_KNEE_HEIGHT;
	}
	else
	{
		right = x + SIMON_BBOX_IDLE_WIDTH;
		bottom = y + SIMON_BBOX_IDLE_HEIGHT;
	}


}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_LEFT:
		if (mx == 0)
			vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_WALKING_RIGHT:
		if (mx == 0)
			vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED;
		//break;
	case SIMON_STATE_IDLE:
		vx = 0;
		mx = 0;
		break;
	case SIMON_STATE_KNEE:
		vx = 0;
		mx = 1;
		break;
	case SIMON_STATE_FIGHT:
		vx = 0;
		break;
	}
}