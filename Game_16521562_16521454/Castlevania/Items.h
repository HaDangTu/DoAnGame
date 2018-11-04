#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"

#define ITEM_TEXTURE_PATH L"castlevania_texture\\Weapon\\Items.png"

#define ITEM_GRAVITY	0.01f
#define ID_ITEM 3

#define ITEM_STATE_DELETE 1
class CItems :
	public CGameObject
{
protected:
	CTextures *textures;
	CSprites *sprites;
	CAnimations *anims;

	LPDIRECT3DTEXTURE9 texitem;

public:
	CItems();
	~CItems();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void LoadData();
	virtual void Render() = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
};

#define DAGGER_BBOX_WIDTH	19
#define DAGGER_BBOX_HEIGHT	10

class CDagger : public CItems
{
	int damage;
public:
	CDagger() :CItems() { this->damage = 2; }

	int GetDamage() { return damage; }
	void SetDamage(int damage) { this->damage = damage; }

	void LoadData();
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

#define HEART_BIG		0
#define HEART_SMALL		1

#define HEART_BBOX_BIG_WIDTH	12
#define HEART_BBOX_BIG_HEIGHT	11

#define HEART_BBOX_SMALL_WIDTH	8
#define HEART_BBOX_SMALL_HEIGHT	9

class CHeart:public CItems
{
	int hearts;
	int size;
public:
	CHeart():CItems() { size = HEART_SMALL; }

	CHeart(int size) :CItems()
	{
		this->size = size;
		switch (size)
		{
		case HEART_BIG:
			hearts = 1;
			break;
		case HEART_SMALL:
			hearts = 2;
			break;
		}
	}

	void SetHearts(int hearts) { this->hearts = hearts; }
	int GetHearts() { return hearts; }

	void SetSize(int size) { this->size = size; }
	int GetSize() { return size; }

	void LoadData();
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};
