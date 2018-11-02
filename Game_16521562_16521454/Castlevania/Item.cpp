#include "Item.h"
#include "InputImage.h"

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
