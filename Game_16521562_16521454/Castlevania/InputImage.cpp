#include "InputImage.h"

void CInputImage::LoadDataFromFile(ifstream & in, int & id, int & left, int & top, int & right, int & bottom)
{
	in >> id;
	in >> left;
	in >> top;
	in >> right;
	in >> bottom;
}

void CInputImage::AddAnimation(ifstream & in, CSprites * sprites, LPANIMATION & ani, LPDIRECT3DTEXTURE9 texture, int n)
{
	int id, left, top, right, bottom;
	int i;
	ani = new CAnimation(100);
	for (i = 0; i < n; i++)
	{
		LoadDataFromFile(in, id, left, top, right, bottom);
		sprites->Add(id, left, top, right, bottom, texture);
		ani->Add(id);
	}
}
