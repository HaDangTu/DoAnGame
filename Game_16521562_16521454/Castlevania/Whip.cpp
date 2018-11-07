#include "Whip.h"
#include "Candle.h"
#include "InputImage.h"
#include <vector>
#include "Simon.h"
#include "debug.h"
#define WHIP_TEXTURE_PATH L"castlevania_texture\\Weapon\\Whip.png"
#define ID_WHIP	6
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
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3,100);
	animations->Add(2000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 100);
	animations->Add(2001, ani);

	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 100);
	animations->Add(2002, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 100);
	animations->Add(2003, ani);

	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 100);
	animations->Add(2004, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 100);
	animations->Add(2005, ani);

	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 100);
	animations->Add(2006, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 100);
	animations->Add(2007, ani);
	in.close();
}

CWhip::CWhip()
{
	fight = false;
	LoadAnimaion();
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	if (fight == true)
	{
		coEventsResult.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		

			for (UINT i = 0; i < coEvents.size(); i++)
			{
				LPCOLLISIONEVENT c = coEvents[i];
				if (c->t == 0)
					coEventsResult.push_back(coEvents[i]);
			}
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CCandle *> (e->obj))
				{
					CCandle *candle = dynamic_cast<CCandle *>(e->obj);
				
					if (candle->state != CANDLE_STATE_DELETE)
					{
						candle->SetState(CANDLE_STATE_DISAPPEAR);
					}
				}
			}
	}
}
void CWhip::Render()
{
	int ani=2 * state + state_whip;
		if (state_whip==WHIP_STATE_LEFT)
		{
			//DebugOut(L"curent= %d\n", animations[ani]->GetCureentFrame());
			////RenderBoundingBox(200);
			//if (animations[ani]->GetCureentFrame() == -1)
			//	animations[ani]->Render(x + 46, y + 1, 255);
			//else if (animations[ani]->GetCureentFrame() == 0)
			//	animations[ani]->Render(x + 46, y + 1, 255);
			//else if (animations[ani]->GetCureentFrame() == 1)
			//	animations[ani]->Render( x + 38, y - 1, 255);
			//else
			//{
			//	fight = true;
			//	animations[ani]->Render(x, y, 255);
			//}
			animations[ani]->RenderWhip(fight, x +46, y + 1, x +38, y - 1, x, y, 255);

		}
		else 
		{
			DebugOut(L"curent= %d\n", animations[ani]->GetCureentFrame());
			//RenderBoundingBox(200);
			animations[ani]->RenderWhip(fight, x - 29, y + 2, x - 38, y - 1, x, y, 255);
		}
	
}


void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == WHITE_WHIP)
	{
		right = x + WHITE_WHIP_BBOX_WIDTH;
		bottom = y + WHITE_WHIP_BBOX_HEIGHT;
	}
	else if(state==BLUE_WHIP)
	{
		right = x + BLUE_WHIP_BBOX_WIDTH;
		bottom = y + BLUE_WHIP_BBOX_HEIGHT;
	}
	else if (state == YELLOW_WHIP)
	{
		right = x + YELLOW_WHIP_BBOX_WIDTH;
		bottom = y + YELLOW_WHIP_BBOX_HEIGHT;
	}
	else if (state == RED_WHIP)
	{
		right = x + RED_WHIP_BBOX_WIDTH;
		bottom = y + RED_WHIP_BBOX_HEIGHT;
	}
}

void CWhip::SetState(int state)
{
	CGameObject::SetState(state);
}

