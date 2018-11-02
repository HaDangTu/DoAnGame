#pragma once
#include <fstream>
#include "Map.h"
#include "Textures.h"
#include "Candle.h"
#include "InputImage.h"
#include "HidenObject.h"

using namespace std;
#define LEVEL_1_MAP_PATH L"castlevania_texture\\Background\\Level 1 Entrance.png"
#define CANDLE_TEXTURE_PATH L"castlevania_texture\\Weapon\\Candle.png"

#define SCENE_1		1
#define SCENE_2		2
#define SCENE_3		3
#define SCENE_4		4

#define ID_MAP_LEVEL_1	0
#define ID_CANDLE	1
class CEntranceLevel :
	public CMap
{
public:
	void LoadMap();
	void Render();
	CEntranceLevel();
	CEntranceLevel(float width, float height):CMap(width, height) {}
	~CEntranceLevel();
};

