/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <string>
#include <fstream>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include "Brick.h"
#include "Ghoul.h"
#include "Bat.h"
using namespace std;

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BRICK_TEXTURE_PATH L"brick.png"
#define SIMON_TEXTURE_PATH L"castlevania_texture\\Simon\\Simon.png"
#define BBOX_TEXTURE_PATH L"bbox.png"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_SIMON	0
#define ID_BRICK	1
#define ID_BBOX		2
#define ID_GHOUL    3
#define ID_BAT      4
CGame *game;
CSimon *simon;
CBrick *brick;
CGhoul *ghoul;
CBat *bat;
//bool flag = false;
vector<LPGAMEOBJECT> objects;
DWORD now;
DWORD FrameStart;
class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_D:
		if (!game->IsKeyDown(DIK_DOWN))
		simon->SetState(SIMON_STATE_JUMP);		
		break;
	case DIK_DOWN:
		float temp_x, temp_y;
		simon->GetPosition(temp_x, temp_y);
		simon->SetPosition(temp_x, temp_y + 9);
		break;
	case DIK_F:
		simon->SetState(SIMON_STATE_FIGHT);
		FrameStart = GetTickCount();
		//flag = true;
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		float temp_x, temp_y;		
		simon->GetPosition(temp_x, temp_y);
		simon->SetPosition(temp_x, temp_y - 9);
		simon->SetState(SIMON_STATE_IDLE);
		break;
	}
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	

	
		if (game->IsKeyDown(DIK_DOWN))
		{
			if (simon->GetState() == SIMON_STATE_FIGHT)
			{
				now = GetTickCount();
				if (now - FrameStart >= 300)
					simon->SetState(SIMON_STATE_KNEE);
				//flag == false;
			}
			else simon->SetState(SIMON_STATE_KNEE);
			//simon->SetState(SIMON_STATE_KNEE);
			if (game->IsKeyDown(DIK_LEFT)) simon->SetState(SIMON_STATE_WALKING_LEFT);
			else if (game->IsKeyDown(DIK_RIGHT)) simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
		else
		{
			if (game->IsKeyDown(DIK_LEFT)) simon->SetState(SIMON_STATE_WALKING_LEFT);
			else if (game->IsKeyDown(DIK_RIGHT)) simon->SetState(SIMON_STATE_WALKING_RIGHT);
			else if (simon->GetState() == SIMON_STATE_FIGHT)
			{
				now = GetTickCount();
				if (now - FrameStart >= 300)
					simon->SetState(SIMON_STATE_IDLE);
				//flag == false;
			}
			else simon->SetState(SIMON_STATE_IDLE);
		}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void AddAnimation(ifstream &in, CSprites *sprites,
	LPANIMATION &ani, LPDIRECT3DTEXTURE9 texture, 
	int n);
void LoadDataFromFile(ifstream &in,
	int &id,
	int &left, int &top,
	int &right, int &bottom);
void LoadResources()
{
	CTextures *texture = CTextures::GetInstance();
	texture->Add(ID_SIMON, SIMON_TEXTURE_PATH, D3DCOLOR_XRGB(0, 128, 128));
	texture->Add(ID_BRICK, BRICK_TEXTURE_PATH, D3DCOLOR_XRGB(255, 255, 255));
	texture->Add(ID_BBOX, BBOX_TEXTURE_PATH, D3DCOLOR_XRGB(237, 28, 36));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	
	LPDIRECT3DTEXTURE9 texsimon = texture->Get(ID_SIMON);

	LPANIMATION ani;
	ifstream in("Data\\Simon.txt");
	
	//int id, left, top, right, bottom;
	//int i;
	//ifstream in("Simon.txt");
	//ani = new CAnimation(100);
	//for (i = 0; i < 3; i++)				//walk left
	//{
	//	LoadDataFromFile(in, id, left, top, right, bottom);
	//	sprites->Add(id, left, top, right, bottom, texsimon);
	//	ani->Add(id);
	//}
	//animations->Add(101, ani);

	//ani = new CAnimation(100);
	//for (i = 0; i < 3; i++)				//walk right
	//{
	//	LoadDataFromFile(in, id, left, top, right, bottom);
	//	sprites->Add(id, left, top, right, bottom, texsimon);
	//	ani->Add(id);
	//}
	//animations->Add(102, ani);

	//ani = new CAnimation(100);
	//LoadDataFromFile(in, id, left, top, right, bottom);
	//sprites->Add(id, left, top, right, bottom, texsimon);
	//ani->Add(id);
	//animations->Add(201, ani);

	//ani = new CAnimation(100);
	//LoadDataFromFile(in, id, left, top, right, bottom);
	//sprites->Add(id, left, top, right, bottom, texsimon);
	//ani->Add(id);
	//animations->Add(202, ani);

	//ani = new CAnimation(100);
	//LoadDataFromFile(in, id, left, top, right, bottom);
	//sprites->Add(id, left, top, right, bottom, texsimon);
	//ani->Add(id);
	//animations->Add(301, ani);

	//ani = new CAnimation(100);
	//LoadDataFromFile(in, id, left, top, right, bottom, true);
	//sprites->Add(id, left, top, right, bottom, texsimon);
	//ani->Add(id);
	//animations->Add(302, ani);

	AddAnimation(in, sprites, ani, texsimon, 3);//walk left
	animations->Add(101, ani);
	AddAnimation(in, sprites, ani, texsimon, 3);//walk right
	animations->Add(102, ani);
	AddAnimation(in, sprites, ani, texsimon, 1);//idle left
	animations->Add(201, ani);
	AddAnimation(in, sprites, ani, texsimon, 1);//idle right
	animations->Add(202, ani);
	AddAnimation(in, sprites, ani, texsimon, 1);//jump left
	animations->Add(301, ani);
	AddAnimation(in, sprites, ani, texsimon, 1);//jump right
	animations->Add(302, ani);
	AddAnimation(in, sprites, ani, texsimon, 3); //fight left
	animations->Add(401, ani);
	AddAnimation(in, sprites, ani, texsimon, 3); //fight right
	animations->Add(402, ani);
	AddAnimation(in, sprites, ani, texsimon, 3);//knee fight left
	animations->Add(501, ani);
	AddAnimation(in, sprites, ani, texsimon, 3); //knee fight right
	animations->Add(502, ani);
	in.close();

	simon = new CSimon();
	simon->AddAnimation(101);
	simon->AddAnimation(102);
	simon->AddAnimation(201);
	simon->AddAnimation(202);
	simon->AddAnimation(301);
	simon->AddAnimation(302);
	simon->AddAnimation(401);
	simon->AddAnimation(402);
	simon->AddAnimation(501);
	simon->AddAnimation(502);
	simon->SetPosition(10.0f, 80.0f);
	//simon->SetState(SIMON_STATE_IDLE);
	objects.push_back(simon);

	LPDIRECT3DTEXTURE9 texbrick = texture->Get(ID_BRICK);
	
	sprites->Add(20011, 0, 0, 15, 15, texbrick);
	ani = new CAnimation(100);
	ani->Add(20011);
	animations->Add(601, ani);

	for (int i = 0; i < 30; i++)
	{
		brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(i * 15, 150.0f);
		objects.push_back(brick);
	}

	//texture->Add(ID_GHOST, L"Ghost.png", D3DCOLOR_XRGB(255, 0, 255));
	//texture->Add(ID_BAT, L"Bat.png", D3DCOLOR_XRGB(255, 0, 255));


	//LPDIRECT3DTEXTURE9 texghost = texture->Get(ID_GHOST);
	//sprites->Add(10001, 0, 0, 33, 64, texghost); //walk left
	//sprites->Add(10001, 0, 0, 33, 64, texghost);
	//sprites->Add(10003, 77, 0, 109, 63, texghost);//walk right
	//sprites->Add(10004, 113, 0, 145, 62, texghost);

	//LPDIRECT3DTEXTURE9 texbat = texture->Get(ID_BAT);
	//sprites->Add(20001, 31, 4, 64, 32, texbat); //fly left
	//sprites->Add(20002, 64, 8, 95, 28, texbat);
	//sprites->Add(20003, 96, 0, 128, 31, texbat);
	//sprites->Add(20004, 132, 2, 167, 31, texbat);// fly right
	//sprites->Add(20005, 167, 8, 199, 27, texbat);
	//sprites->Add(20006, 198, 5, 231, 31, texbat);

	//LPANIMATION ani;
	//ani = new CAnimation(100);
	//ani->Add(10001);
	//ani->Add(10002);
	//animations->Add(400, ani);

	//ani = new CAnimation(100);
	//ani->Add(10003);
	//ani->Add(10004);
	//animations->Add(401, ani);

	//ani = new CAnimation(100);
	//ani->Add(20001);
	//ani->Add(20002);
	//ani->Add(20003);
	//animations->Add(402, ani);

	//ani = new CAnimation(100);
	//ani->Add(20004);
	//ani->Add(20005);
	//ani->Add(20006);
	//animations->Add(403, ani);

	//ghost = new CGhost();
	//ghost->AddAnimation(401);
	//ghost->AddAnimation(400);
	//ghost->SetPosition(200, 135);
	//ghost->SetState(GHOST_ANI_RIGHT);
	//objects.push_back(ghost);
	//bat = new CBat();
	//bat->AddAnimation(403);
	//bat->AddAnimation(402);
	//bat->SetPosition(200, 30);
	//bat->SetState(BAT_ANI_LEFT);
	//bat->SetHeightFly(30);
	//objects.push_back(bat);
}

void AddAnimation(ifstream &in, CSprites * sprites, 
	LPANIMATION &ani, LPDIRECT3DTEXTURE9 texture, int n)
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

void LoadDataFromFile(ifstream &in,
	int &id,
	int &left, int &top,
	int &right, int &bottom)
{
	in >> id;
	in >> left;
	in >> top;
	in >> right;
	in >> bottom;

}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}
	
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}

