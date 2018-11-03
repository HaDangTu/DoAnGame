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
	else if(state ==ITEM_STATE_WHIP_UPDATE)
	{
		right = x + WHIP_UPDATE_BBOX_WIDTH;
		bottom = y + WHIP_UPDATE_BBOX_HEIGHT;
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
	else if (state == ITEM_STATE_HEART_BIG)
	{
		animations[1]->Render(x, y, 255);
	}
	else if (state == ITEM_STATE_WHIP_UPDATE)
	{
		animations[2]->Render(x, y, 255);
	}
}

void CItem::SetState(int state)
{
	CGameObject::SetState(state);
}
void CItem::loaddata()
{
	LPANIMATION ani;
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	ifstream in("Data\\Item.txt");
	LPDIRECT3DTEXTURE9 texitem = texture->Get(ID_ITEM);
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1); // heart small
	animations->Add(6000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1); //heart big
	animations->Add(6001, ani);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1); //whip update
	animations->Add(6002, ani);
	in.close();
	AddAnimation(6000);
	AddAnimation(6001);
	AddAnimation(6002);
}
CItem::CItem(int state)
{
	SetState(state);
	loaddata();
}
CItem::~CItem()
{
}
