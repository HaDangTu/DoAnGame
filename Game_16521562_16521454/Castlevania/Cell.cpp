#include "Cell.h"
#include "debug.h"
#include "Candle.h"
void CCell::SetObjects(LPGAMEOBJECT object)
{
	objects.push_back(object);
}


void CCell::Update(DWORD dt)
{
	for (UINT i = 0; i < objects.size(); i++)
		objects[i]->Update(dt);
}

void CCell::Render()
{
	for (UINT i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

CCell::CCell()
{
	width = 80;
	height = 60;
	objects.clear();
}


CCell::~CCell()
{
}

CCells::CCells()
{
}

CCells::CCells(int row, int column)
{
	this->row = row;
	this->column = column;
	int i;
	cells = new CCell *[row];
	for (i = 0; i < row; i++)
		cells[i] = new CCell[column];
}

CCells::~CCells()
{
}

void CCells::InitCells(LPGAMEOBJECT object, int x, int y)
{
	cells[x][y].SetObjects(object);
}

void CCells::GetListOfObjects(vector<LPGAMEOBJECT>* list_object, float cam_x, float cam_y)
{
	int xs, ys;
	int xe, ye;
	int i, j, k;
	list_object->clear();
	xs = (int)cam_x / 80;
	ys = (int)cam_y / 60;

	xe = (int)(cam_x + 320.0f) / 80;
	ye = (int)(cam_y + 160.0f) / 60;

	for (i = ys; i <= ye; i++)
		for (j = xs; j <= xe; j++)
		{
			if (cells[i][j].GetObjects().size() != 0)
				for (k = 0; k < cells[i][j].GetObjects().size(); k++)
				{
					LPGAMEOBJECT e = cells[i][j].GetObjects()[k];
					if (dynamic_cast<CCandle *> (e))
					{
						if (e->state == CANDLE_STATE_DELETE)
						{
							CCandle *candle = dynamic_cast<CCandle *>(e);
							if(candle->GetItem()->GetState()!=ITEM_STATE_DELETE)
								list_object->push_back(candle->GetItem());
						}
						else
						{
							list_object->push_back(e);
						}
					}
					else 
						list_object->push_back(e);
				}
		}


}

void CCells::Update(DWORD dt, float cam_x, float cam_y)
{
	int xs, ys;
	int xe, ye;
	int i, j;

	xs = (int)cam_x / 80;
	ys = (int)cam_y / 60;

	xe = (int)(cam_x + 320.0f) / 80;
	ye = (int)(cam_y + 200.0f) / 60;

	for (i = xs; i < xe; i++)
		for (j = ys; j < ye; j++)
			cells[i][j].Update(dt);

}

void CCells::Render(float cam_x, float cam_y)
{
	int xs, ys;
	int xe, ye;
	int i, j;

	xs = (int)cam_x / 80;
	ys = (int)cam_y / 60;

	xe = (int)(cam_x + 240.0f) / 80;
	ye = (int)(cam_y + 200.0f) / 60;

	for (i = xs; i < xe; i++)
		for (j = ys; j < ye; j++)
			cells[i][j].Render();
}

CCell CCells::GetCell(int x, int y)
{
	return cells[x][y];
}