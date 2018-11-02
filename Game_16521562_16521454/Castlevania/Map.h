#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"
#include "Cell.h"
#include "Game.h"
#include <vector>
using namespace std;

class CMap
{
protected:
	int scene;

	float width;
	float height;

	CCells *cells;

	CTextures *textures;
	CSprites *sprites;
	CAnimations *animations;
	
	LPDIRECT3DTEXTURE9 texture_map;
public:
	CMap();
	CMap(float width, float height);
	~CMap();

	void GetSize(float &width, float &height) { width = this->width; height = this->height; }
	void SetSize(float width, float height) { this->width = width; this->height = height; }

	int GetSence() { return scene; }
	void SetSence(int scene) { this->scene = scene; }
	
	vector<LPGAMEOBJECT> GetUpdateObjects();
	virtual void LoadMap();
	//void Update(DWORD dt);
	virtual void Render();
};

