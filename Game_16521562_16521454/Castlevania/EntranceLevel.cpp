#include "EntranceLevel.h"



void CEntranceLevel::LoadMap()
{
	CMap::LoadMap();
	textures->Add(ID_MAP_LEVEL_1, LEVEL_1_MAP_PATH, D3DCOLOR_XRGB(255, 255, 255));
	texture_map = textures->Get(ID_MAP_LEVEL_1);
	switch (scene)
	{
	case SCENE_1:
		textures->Add(ID_CANDLE, CANDLE_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));		
		LPDIRECT3DTEXTURE9 texture_candle = textures->Get(ID_CANDLE);
		LPANIMATION ani = new CAnimation(100);
		ifstream in("Data\\Candle.txt");

		CInputImage::AddAnimation(in, sprites, ani, texture_candle, 2);
		animations->Add(100, ani);

		CCandle *candle = new CCandle(ITEM_STATE_WHIP_UPDATE);
		candle->AddAnimation(100);
		candle->SetPosition(85.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 1);

		candle = new CCandle(ITEM_STATE_HEART_SMALL);
		candle->AddAnimation(100);
		candle->SetPosition(222.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 2);

		candle = new CCandle(ITEM_STATE_HEART_SMALL);
		candle->AddAnimation(100);
		candle->SetPosition(343.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 4);
		
		candle = new CCandle(ITEM_STATE_WHIP_UPDATE);
		candle->AddAnimation(100);
		candle->SetPosition(475.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 6);

		candle = new CCandle(ITEM_STATE_HEART_SMALL);
		candle->AddAnimation(100);
		candle->SetPosition(600.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 7);

		for (int i = 0; i < 10; i++)
		{
			CHidenObject *hidenObj = new CHidenObject();
			hidenObj->SetSize(80.0f, 15.0f);
			hidenObj->SetPosition(i * 80.0f, 145.0f);
			cells->InitCells(hidenObj, 2, i);
		}
		break;
	}
}

void CEntranceLevel::Render()
{
	CGame *game = CGame::GetInstance();
	switch (scene)
	{
	case SCENE_1:
		game->Draw(0, 0, texture_map, 0, 0, 768, 185);
		break;
	}
}

CEntranceLevel::CEntranceLevel()
{
}


CEntranceLevel::~CEntranceLevel()
{
}
