#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"

#include <windows.h>

#define BLOCK_SIZE					50
#define HULF_PI						1.5703f

#define HOLIZON_TO_UNDER			12								//プレイヤーから地平線までの数 4で割れる数字にしたい
#define HORIZON_TO_PLAYER			(HOLIZON_TO_UNDER*0.75f)		//水平線からプレイヤーまでの描画数
#define PLAYER_TO_UNDER				(HOLIZON_TO_UNDER*0.25f)		//プレイヤーから画面が今での描画数
#define DRAW_ANGLE_Y				(1.0f/HOLIZON_TO_UNDER)			//角度倍率

#define UNDER_LEFT_TO_RIGHT			16								//プレイヤーのいる高さは左右に8つずつ描画するから
#define TOP_LEFT_RIGHT				(UNDER_LEFT_TO_RIGHT*1.5)
#define WIDE_WIDE					SCREEN_WIDTH/TOP_LEFT_RIGHT		//これが基準になる幅

Map::Map()
{
	sumple = { 
		BLOCK_SIZE * MAP_SIZE * 0.2f,
		BLOCK_SIZE * MAP_SIZE * 0.2f 
	};
	mouse = { 
		SCREEN_WIDTH * 0.2f,
		SCREEN_HEIGHT * 0.2f 
	};
	move = {
		(BLOCK_SIZE * MAP_SIZE) - sumple.x,
		(BLOCK_SIZE * MAP_SIZE) - sumple.y
	};

	m_MouseTex = LoadTexture((char*)"data/TEXTURE/MousePoint.png");
	m_BGTex = LoadTexture((char*)"data/TEXTURE/sky.png");

	isMouse = !true;
}

void Map::InitMapManager(D3DXVECTOR2* playerPos)
{
}

void Map::UninitMapManager()
{
}

void Map::UpdateMapManager()
{
	int speed = 1;
	if (GetKeyboardPress(DIK_A)) {
		sumple.x -= speed;
		move.x += speed;
	}
	if (GetKeyboardPress(DIK_D)) {
		sumple.x += speed;
		move.x -= speed;
	}
	if (GetKeyboardPress(DIK_W)) {
		sumple.y -= speed;
		//if (sumple.y > 450)		
			move.y += speed;
	}
	if (GetKeyboardPress(DIK_S)) {
		sumple.y += speed;
		move.y -= speed;
	}/*
	if (GetKeyboardTrigger(DIK_W)) {
		sumple.y -= speed;
		move.y += speed;
	}
	if (GetKeyboardTrigger(DIK_S)) {
		sumple.y += speed;
		move.y -= speed;
	}*/

	if (GetKeyboardTrigger(DIK_TAB)) {
		isMouse = !isMouse;
	}

	if (isMouse) {
		SetCursorPos(800, 500);
	}
}

void Map::DrawMapManager()
{
	//ソラ
	DrawSpriteLeftTop(m_BGTex, 0, -500, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);


	//プレイヤーのいるY座標を簡易変換？
	int sy = sumple.y / 50;									//プレイヤーの今いる簡易Y座標
	float subY = (float)((int)move.y % 50) / 50.0f;			//プレイヤーのY座標の差分	子の差分のぶんだけマップの座標の描画をずらして移動しているように見せる　これに
	
	float hrizon = SCREEN_HEIGHT * 0.2f;					//マップ描画の地平線　
	float under = SCREEN_HEIGHT - hrizon;					//地平線からプレイヤー側の画面外までの差分


	//プレイヤーのいるX座標を簡易変換
	int sx = sumple.x / 50;
	float subX = (float)((int)sumple.x % 50) / 50.0f;		//プレイヤーのX座標の差分



	int numY = 0;			//地平線から何個目のやつかのYバージョン
	float hWideT, hWideB, lineT, lineB, subAngle;



	for (int y = sy - HORIZON_TO_PLAYER; y < sy + PLAYER_TO_UNDER; y++) {		//描画する数を制限
		
		subAngle = HULF_PI * DRAW_ANGLE_Y * subY;
		hWideT = 1 - cosf(HULF_PI * DRAW_ANGLE_Y * numY + subAngle);
		hWideB = 1 - cosf(HULF_PI * DRAW_ANGLE_Y * (numY + 1) + subAngle);

		lineT = hrizon + under * hWideT;
		lineB = hrizon + under * hWideB;

		int numX = -TOP_LEFT_RIGHT *0.5f;				//プレイヤーから何個ずれたやつか

		float wideT, wideB;								//□の上と下の辺の長さ
		float lt, rt, lb, rb;							///左上右上左下右下のX座標

		for (int x = sx - TOP_LEFT_RIGHT * 0.5f; x < sx + TOP_LEFT_RIGHT * 0.5f; x++) {
			//水平線が２　プレイヤーのとこより下が３にする予定

			D3DXCOLOR col = { //緑をだんだんこく
				1.0f - 0.05f * x,
				1.0f - 0.05f * x,
				1.0f - 0.05f * x,
				/*1.0f - 0.05f * y,
				1.0f - 0.05f * y,
				1.0f - 0.05f * y,*/
				1.0f
			};

			
			wideT = WIDE_WIDE+ WIDE_WIDE*(sinf(HULF_PI * DRAW_ANGLE_Y * numY + subAngle));		//この数字をかける
			wideB = WIDE_WIDE+ WIDE_WIDE*(sinf( HULF_PI * DRAW_ANGLE_Y * (numY+1) + subAngle));
			

			/*lt = 0;
			rt = SCREEN_WIDTH;
			lb = 0;
			rb = SCREEN_WIDTH;*/

			lt = SCREEN_WIDTH * 0.5f + wideT * numX;
			rt = SCREEN_WIDTH * 0.5f + wideT * (numX + 1);
			lb = SCREEN_WIDTH * 0.5f + wideB * numX;
			rb = SCREEN_WIDTH * 0.5f + wideB * (numX + 1);

			//地平線がビコビコなるのを修正 これなくしたい
			if (numY == 0) {
				DrawBoxColor_TB_FOUR(&hrizon, &lineB, &lt, &rt, &lb, &rb, &col);
			}

			DrawBoxColor_TB_FOUR(&lineT, &lineB, &lt, &rt, &lb, &rb, &col);

			numX++;
		}
		if (numY <= y)numY++;
	}


	//プレイヤーの描画場所は基本固定
	D3DXVECTOR2 pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.7f };
	D3DXVECTOR2 siz = { 100,100 };
	D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f };
	DrawBoxColor(&pos, &siz, col);

	mouse.x += GetMouseX();
	mouse.y += GetMouseY();

	//DrawSpriteLeftTop(m_MouseTex, mouse.x, mouse.y, 30, 30, 0, 0, 1, 1);
	DrawSpriteLeftTop(m_MouseTex, GetMousePosition().x, GetMousePosition().y, 30, 30, 0, 0, 1, 1);
	//ShowCursor(true);
	ShowCursor(false);

	HCURSOR hcu;
	
	
	DrawNumberSumple(D3DXVECTOR2(100, 100), D3DXVECTOR2(50, 50), sumple.y);
}
