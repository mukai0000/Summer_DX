#include "game.h"
#include "sprite.h"

#include "MapManager.h"
#include "UI.h"
#include "Title.h"

Map* mm = nullptr;

Title* title = nullptr;

FADE g_Fade = FADE_NONE;
D3DXVECTOR2 g_Target = { 500,500 };
int g_Time = 0;
SCENE g_NowScene;
SCENE g_NextScene;

TEXTURE_DATA g_FadeTex;



void InitGame()
{
	g_FadeTex = SetTexture("data/TEXTURE/FADE/CircleFade.png", 1, 1, 1);


	UI_DATA ud = SetUI_DATA("data/TEXTURE/Button.png", 1, 1, 1, D3DXVECTOR2(100, 100), D3DXVECTOR2(192, 192), D3DXCOLOR(1, 1, 1, 1), true, 1.0f);


	switch (g_NowScene) {
	case SCENE_TITLE:
		title = new Title();
		break;

	case SCENE_GAME:
		mm = new Map;
		break;

	}
}

void UninitGame()
{
	switch (g_NowScene) {
	case SCENE_TITLE:
			delete title;
		break;

	case SCENE_GAME:
			delete mm;
		break;

	}
}


void UpdateGame()
{

	switch (g_NowScene) {
	case SCENE_TITLE:
		if (title != nullptr) {
			title->Update();
		}
		break;

	case SCENE_GAME:
		if (mm != nullptr) {
			mm->Update();
		}
		break;

	}

	UpdateFade();
}

void DrawGame()
{/*
	mm->DrawMapManager();*/

	switch (g_NowScene) {
	case SCENE_TITLE:
		if (title != nullptr) {
			title->Draw();
		}
		break;

	case SCENE_GAME:
		if (mm != nullptr) {
			mm->Draw();
		}
		break;
	}

	DrawFade();

	int m_MouseTex = LoadTexture((char*)"data/TEXTURE/MousePoint.png");
	DrawSpriteLeftTop(m_MouseTex, GetMousePosition().x, GetMousePosition().y, 30, 30, 0, 0, 1, 1);
	//ShowCursor(true);
	ShowCursor(false);

}

void SetFade(SCENE next, D3DXVECTOR2 target)
{
	if (g_Fade == FADE_NONE) {
		g_Fade = FADE_OUT;
		g_Target = target;
		g_Time = 60;
		g_NextScene = next;
	}
}

void UpdateFade()
{
	switch (g_Fade)
	{
	case FADE_NONE:

		break;
	case FADE_OUT:
		if (g_Time < 0) {
			ChangeScene(g_NextScene);
			g_Fade = FADE_STAY;
			g_Time = 60;

			ChangeScene(g_NextScene);
		}
		else {
			g_Time--;
		}
		break;
	case FADE_IN:
		if (g_Time <= 0) {
			g_Fade = FADE_NONE;
			g_Time = 60;
		}
		else {
			g_Time--;
		}
		break;
	case FADE_STAY:
		if (g_Time <= 0) {
			g_Fade = FADE_IN;
			g_Time = 60;
			ChangeScene(g_NextScene);
		}
		else {
			g_Time--;
		}
		break;
	}
}

void DrawFade()
{
	if (g_Fade != FADE_NONE) {
		TEXTURE_DATA box = SetTexture("data/TEXTURE/BOX.png", 1, 1, 1);
		D3DXCOLOR col = { 0,0,0,1 };
		D3DXVECTOR4 uv = { 0,0,1,1 };
		D3DXVECTOR2 size = { 4000 ,4000 };
		D3DXVECTOR2 zero = { 0 ,0 };

		if (g_Fade != FADE_STAY) {

			switch (g_Fade)
			{
			case FADE_OUT:
				size.x *= ((float)g_Time) / 60.0f;
				size.y *= ((float)g_Time) / 60.0f;
				break;
			case FADE_IN:
				size.x *= 1.0f - ((float)g_Time) / 60.0f;
				size.y *= 1.0f - ((float)g_Time) / 60.0f;
				break;
			}
			DrawSprite(&g_FadeTex, &g_Target, &size);

			D3DXVECTOR2 pos[4];

			size.x *= 0.5f;
			size.y *= 0.5f;

			pos[0] = { 0,0 };
			pos[1] = { g_Target.x + size.x,0 };
			pos[2] = { 0,g_Target.y - size.y };
			pos[3] = { g_Target.x - size.x,g_Target.y + size.y };

			D3DXVECTOR2 size0 = { g_Target.x + size.x,g_Target.y - size.y };
			D3DXVECTOR2 size1 = { SCREEN_WIDTH - pos[1].x,g_Target.y + size.y };
			D3DXVECTOR2 size2 = { g_Target.x - size.x,SCREEN_HEIGHT - size0.y };
			D3DXVECTOR2 size3 = { SCREEN_WIDTH - pos[3].x,SCREEN_HEIGHT - g_Target.y - size.y };

			DrawSprite_LT(&box, &pos[0], &size0, &col, &uv);
			DrawSprite_LT(&box, &pos[1], &size1, &col, &uv);
			DrawSprite_LT(&box, &pos[2], &size2, &col, &uv);
			DrawSprite_LT(&box, &pos[3], &size3, &col, &uv);
		}
		else {
			DrawSprite_LT(&box, &zero, &size, &col, &uv);
		}
		
	}
}


void SetTarget(D3DXVECTOR2 target)
{
	g_Target = target;
}

void ChangeScene(SCENE next)
{
	UninitGame();

	g_NowScene = next;

	switch (g_NowScene) {
	case SCENE_TITLE:
		title = new Title();
		break;

	case SCENE_GAME:
		mm = new Map;
		break;

	}
}
