#include "Whip.h"
#include "Candle.h"
#include "InputImage.h"
#include <vector>

#define WHIP_TEXTURE_PATH L"castlevania_texture\\Weapon\\Whip.png"
#define ID_WHIP		6
using namespace std;


void CWhip::LoadAnimaion()
{
	CTextures *texture = CTextures::GetInstance();
	texture->Add(ID_WHIP, WHIP_TEXTURE_PATH, D3DCOLOR_XRGB(0, 128, 128));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	ifstream in("Data\\Whip.txt");
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 texwhip = texture->Get(ID_WHIP);
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3);
	animations->Add(801, ani);
	in.close();
}

CWhip::CWhip()
{
	LoadAnimaion();
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	CalcPotentialCollisions(coObjects, coEvents);

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (dynamic_cast<CCandle *> (e->obj))
		{
			CCandle  *candle = dynamic_cast<CCandle *>(e->obj);
			if (candle->GetState() != CANDLE_STATE_DISAPPEAR)
				candle->SetState(CANDLE_STATE_DISAPPEAR);
		}
	}

}

void CWhip::Render()
{
	animations[0]->Render(x, y);
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == SHORT_WHIP)
	{
		right = x + SHORT_WHIP_BBOX_WIDTH;
		bottom = y + SHORT_WHIP_BBOX_HEIGHT;
	}
	else
	{
		right = x + LONG_WHIP_BBOX_WIDTH;
		bottom = y + LONG_WHIP_BBOX_HEIGHT;
	}
}

