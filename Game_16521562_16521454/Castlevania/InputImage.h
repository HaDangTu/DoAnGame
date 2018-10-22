#pragma once
#include "Textures.h"
#include "Sprites.h"
#include <fstream>

class CInputImage
{
public:
	static void LoadDataFromFile(ifstream &in,
		int &id,
		int &left, int &top,
		int &right, int &bottom);
	static void AddAnimation(ifstream &in, CSprites *sprites,
		LPANIMATION &ani, LPDIRECT3DTEXTURE9 texture,
		int n);
};

