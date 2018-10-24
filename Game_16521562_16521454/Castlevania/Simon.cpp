#include "Simon.h"
#include "debug.h"
#include "Candle.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObject, coEvents);

	if (state == SIMON_STATE_FIGHT)
		whip->Update(dt, coObject);
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
		if (ny != 0) {
			vy = 0; jump = 1;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CCandle *> (e->obj))
			{
				x += dx;
				y += dy;
			}
		}
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
			if (mx > 0)
			{
				ani = SIMON_ANI_JUMP_RIGHT; //SIMON_ANI_KNEE_RIGHT
				if (state == SIMON_STATE_FIGHT) ani = SIMON_ANI_KNEE_FIGHT_RIGHT;
			}
			if (state == SIMON_STATE_FIGHT && mx == 0)
				ani = SIMON_ANI_FIGHT_RIGHT;
		}
		else
		{
			ani = SIMON_ANI_IDLE_LEFT;
			if (mx > 0)
			{
				ani = SIMON_ANI_JUMP_LEFT; //SIMON_ANI_KNEE_LEFT
				if (state == SIMON_STATE_FIGHT) ani = SIMON_ANI_KNEE_FIGHT_LEFT;
			}
			if (state == SIMON_STATE_FIGHT && mx == 0)
				ani = SIMON_ANI_FIGHT_LEFT;
		}
	}
	else
	{
		if (nx < 0)
		{
			ani = SIMON_ANI_WALKING_LEFT;
			if (state == SIMON_STATE_FIGHT) ani =SIMON_ANI_FIGHT_LEFT;
		}
		else
		{
			ani = SIMON_ANI_WALKING_RIGHT;
			if (state == SIMON_STATE_FIGHT) ani = SIMON_ANI_FIGHT_RIGHT;
		}
	}


	if (vy < 0 && nx < 0)
		ani = SIMON_ANI_JUMP_LEFT;
	else if (vy < 0 && nx > 0)
		ani = SIMON_ANI_JUMP_RIGHT;
	if(ani==SIMON_ANI_FIGHT_LEFT) 
		whip->animations[0]->Render(x + 24, y + 6, x + 16, y + 4, x-22, y+5, 255);
	else if (ani == SIMON_ANI_FIGHT_RIGHT) 
		whip->animations[1]->Render(x - 7, y + 7, x - 16, y + 4, x + 22, y + 5, 255);
	else if (ani == SIMON_ANI_KNEE_FIGHT_LEFT)
		whip->animations[0]->Render(x + 24, y + 6, x + 16, y + 4, x - 22, y + 5, 255);
	else if (ani == SIMON_ANI_KNEE_FIGHT_RIGHT)
		whip->animations[1]->Render(x - 7, y + 7, x - 16, y + 4, x + 22, y + 5, 255);
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
		/*if (state == SIMON_STATE_FIGHT)
		{
			right = x + SIMON_BBOX_KNEE_FIGHT_WIDTH;
			bottom = y + SIMON_BBOX_KNEE_FIGHT_HEIGHT;
		}*/
	}
	else 
	{
		right = x + SIMON_BBOX_IDLE_WIDTH;
		bottom = y + SIMON_BBOX_IDLE_HEIGHT;
	}


}

int CSimon::GetPreviousState()
{
	if (state == SIMON_STATE_IDLE || state == SIMON_STATE_WALKING_LEFT ||
		state == SIMON_STATE_WALKING_RIGHT || state == SIMON_STATE_KNEE)
		previousstate = state;
	DebugOut(L"previous state = %d\n", previousstate);
	return previousstate;
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_LEFT:
		if (mx == 0 )
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
