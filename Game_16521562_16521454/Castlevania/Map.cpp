#include "Map.h"

CMap::CMap()
{
	
}

CMap::CMap(float width, float height)
{
	this->width = width;
	this->height = height;
}


CMap::~CMap()
{
}

vector<LPGAMEOBJECT> CMap::GetUpdateObjects()
{
	float cam_x, cam_y;
	CGame *game = CGame::GetInstance();
	game->GetCamera(cam_x, cam_y);
	vector<LPGAMEOBJECT> UpdateObjects;

	cells->GetListOfObjects(&UpdateObjects, cam_x, cam_y);
	return UpdateObjects;
}

void CMap::LoadMap()
{
	int column, row;
	column = (int)width / 64 + 1;
	row = (int)height / 56 + 1;

	cells = new CCells(row, column);

	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	animations = CAnimations::GetInstance();
}

//void CMap::Update(DWORD dt)
//{
//	float cam_x;
//	float cam_y;
//	CGame *game = CGame::GetInstance();
//	game->GetCamera(cam_x, cam_y);
//	
//	cells->Update(dt, cam_x, cam_y);
//}

void CMap::Render()
{
}

