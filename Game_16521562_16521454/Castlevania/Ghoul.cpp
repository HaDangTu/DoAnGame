#include "Ghoul.h"

void CGhoul::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOUL_BBOX_WIDTH;
	bottom = y + GHOUL_BBOX_HEIGHT;
}

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

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

void CGhoul::Render()
{
	int ani;
	if (nx > 0)
		ani = GHOUL_ANI_RIGHT;
	else
		ani = GHOUL_ANI_LEFT;
	animations[ani]->Render(x, y);
}

void CGhoul::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GHOUL_ANI_RIGHT:
		vx = GHOUL_WALKING_SPEED;
		nx = 1;
		break;
	case GHOUL_ANI_LEFT:
		vx = -GHOUL_WALKING_SPEED;
		nx = -1;
		break;
	}
}
