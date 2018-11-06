#include "Items.h"
#include <fstream>
#include "InputImage.h"
using namespace std;


CItems::CItems()
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	anims = CAnimations::GetInstance();
}


CItems::~CItems()
{
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += ITEM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
		y += dy;
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

void CItems::LoadData()
{
	textures->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	texitem = textures->Get(ID_ITEM);
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ITEM_STATE_ITEM)
		CItems::Update(dt, coObjects);
	else if (state == ITEM_STATE_WEAPON_RIGHT)
		SetPosition(x + 3, y);
	else if(state == ITEM_STATE_WEAPON_LEFT)
		SetPosition(x - 3, y);

}

void CDagger::LoadData()
{
	CItems::LoadData();
	LPANIMATION ani = new CAnimation(100);
	ifstream in("Data\\Dagger.txt");

	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	anims->Add(6000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	anims->Add(6001, ani);
	in.close();
	AddAnimation(6000);
	AddAnimation(6001);
}

void CDagger::Render()
{
	if (state == ITEM_STATE_WEAPON_LEFT)
	{
		animations[1]->Render(x, y);
	}
	else if (state != ITEM_STATE_DELETE)
	{
		animations[0]->Render(x, y);
	}
}

void CDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}

void CHeart::LoadData()
{
	CItems::LoadData();
	LPANIMATION ani = new CAnimation(100);
	ifstream in("Data\\Heart.txt");

	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	anims->Add(7000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	anims->Add(8000, ani);
	in.close();
	AddAnimation(7000);
	AddAnimation(8000);
}

void CHeart::Render()
{
	if (state != ITEM_STATE_DELETE)
	{
		switch (size)
		{
		case HEART_BIG:
			animations[1]->Render(x, y);
			break;
		case HEART_SMALL:
			animations[0]->Render(x, y);
			break;
		}
	}
}

void CHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	switch (size)
	{
	case HEART_BIG:
		right = x + HEART_BBOX_BIG_WIDTH;
		bottom = y + HEART_BBOX_BIG_HEIGHT;
		break;
	case HEART_SMALL:
		right = x + HEART_BBOX_SMALL_WIDTH;
		bottom = y + HEART_BBOX_SMALL_HEIGHT;
		break;
	}
}

void CWhipUpdate::LoadData()
{
	CItems::LoadData();
	LPANIMATION ani = new CAnimation(100);
	ifstream in("Data\\WhipUpdate.txt");

	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	anims->Add(9000, ani);
	in.close();
	AddAnimation(9000);
}

void CWhipUpdate::Render()
{
	if (state != ITEM_STATE_DELETE)
	{
		animations[0]->Render(x, y);
	}
}

void CWhipUpdate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_UPDATE_BBOX_WIDTH;
	bottom = y + WHIP_UPDATE_BBOX_HEIGHT;
}
