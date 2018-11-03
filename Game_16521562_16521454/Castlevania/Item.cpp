#include "Item.h"
#include "InputImage.h"
#include "HidenObject.h"
void CItem::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	if (state == ITEM_STATE_HEART_SMALL)
	{
		right = x + HEART_SMALL_BBOX_WIDTH;
		bottom = y + HEART_SMALL_BBOX_HEIGHT;
	}
	else if (state == ITEM_STATE_HEART_BIG)
	{
		right = x + HEART_BIG_BBOX_WIDTH;
		bottom = y + HEART_BIG_BBOX_HEIGHT;
	}
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += ITEM_GRAVITY;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CHidenObject *> (e->obj))
			{
				if (ny != 0) {
					vy = 0;
				}
			}
		}
	}
}


void CItem::Render()
{
	if (state == ITEM_STATE_HEART_SMALL)
	{
		animations[0]->Render(x, y, 255);
	}
}

void CItem::SetState(int state)
{
	CGameObject::SetState(state);
}
void CItem::loaddata(int state)
{
	if (state == ITEM_STATE_HEART_SMALL)
	{
		CTextures *texture = CTextures::GetInstance();
		texture->Add(ID_HEART_SMALL, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));

		CSprites *sprites = CSprites::GetInstance();
		CAnimations *animations = CAnimations::GetInstance();

		ifstream in("Data\\Item.txt");
		LPANIMATION ani;
		LPDIRECT3DTEXTURE9 texitem = texture->Get(ID_HEART_SMALL);
		ani = new CAnimation(100);
		CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
		animations->Add(6000, ani);
		in.close();
		AddAnimation(6000);
	}
}
CItem::CItem(int state)
{
	SetState(state);
	loaddata(state);
}
CItem::~CItem()
{
}
