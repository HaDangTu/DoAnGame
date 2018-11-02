#pragma once
#include <vector>
#include "Game.h"
#include "GameObject.h"
using namespace std;

class CCell
{
	vector<LPGAMEOBJECT> objects;
	float width;
	float height;
public:
	void GetSize(float width, float height) { width = this->width; height = this->height; }
	void SetObjects(LPGAMEOBJECT object);
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
	void Update(DWORD dt);
	void Render();
	CCell();
	~CCell();
};
typedef CCell *LPCELL;

class CCells
{
	int row;
	int column;

	LPCELL *cells;
public:
	CCells();
	CCells(int row, int column);
	~CCells();

	void InitCells(LPGAMEOBJECT object, int x, int y);
	void GetListOfObjects(vector<LPGAMEOBJECT> *list_object, float cam_x, float cam_y);
	void Update(DWORD dt, float cam_x, float cam_y);
	void Render(float cam_x, float cam_y);
	CCell GetCell(int x, int y);
};