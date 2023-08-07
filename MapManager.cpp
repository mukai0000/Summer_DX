#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"

#include "myString.h"

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
		BLOCK_SIZE * MAP_SIZE * 0.5f,
		BLOCK_SIZE * MAP_SIZE * 0.5f
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

	if (GetKeyboardTrigger(DIK_W) && GetKeyboardPress(DIK_LSHIFT)) {
		sumple.y -= speed;
		move.y += speed;
	}
	else if (GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_LSHIFT)) {
		sumple.y -= speed;
		//if (sumple.y > 450)		
		move.y += speed;
	}

	if (GetKeyboardTrigger(DIK_S) && GetKeyboardPress(DIK_LSHIFT)) {
		sumple.y += speed;
		move.y -= speed;
	}
	else if (GetKeyboardPress(DIK_S) && !GetKeyboardPress(DIK_LSHIFT)) {
		sumple.y += speed;
		move.y -= speed;
	}

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
	int sy = (int)sumple.y / 50;							//プレイヤーの今いる簡易Y座標
	float subY = (float)((int)move.y % 50) / 50.0f;			//プレイヤーのY座標の差分	子の差分のぶんだけマップの座標の描画をずらして移動しているように見せる　これに

	float hrizon = SCREEN_HEIGHT * 0.2f;					//マップ描画の地平線　
	float under = SCREEN_HEIGHT - hrizon;					//地平線からプレイヤー側の画面外までの差分


	//地平線がビコビコするのはここで小数点以下切り捨てにしてしまってる部分を拾ってないから

	//プレイヤーのいるX座標を簡易変換
	int sx = (int)sumple.x / 50;
	float subX = (float)((int)sumple.x % 50) / 50.0f;		//プレイヤーのX座標の差分


	int numY = 0;			//地平線から何個目のやつかのYバージョン
	float hWideT, hWideB, lineT, lineB, subAngle, topAngle, bottomAngle;

	TEXTURE_DATA box = SetTexture("data/TEXTURE/box.png", 1, 1, 1);
	int startY = sy - HORIZON_TO_PLAYER;
	int endY = sy + PLAYER_TO_UNDER;

	for (int y = startY; y < endY; y++) {		//描画する数を制限

		subAngle = HULF_PI * DRAW_ANGLE_Y * subY;								//プレイヤーの移動によって発生した角度の端数？

		topAngle = HULF_PI * DRAW_ANGLE_Y * numY + subAngle;					//描画のチップのうえ座標の角度
		bottomAngle = HULF_PI * DRAW_ANGLE_Y * (numY + 1) + subAngle;			//描画のチップの下の座標の角度

		hWideT = 1 - cosf(topAngle);
		hWideB = 1 - cosf(bottomAngle);

		lineT = hrizon + under * hWideT;
		lineB = hrizon + under * hWideB;

		int numX = -TOP_LEFT_RIGHT * 0.5f;				//プレイヤーから何個ずれたやつか

		float wideT, wideB;								//□の上と下の辺の長さ
		float lt, rt, lb, rb;							///左上右上左下右下のX座標

		int startX = sx - TOP_LEFT_RIGHT * 0.5f;
		int endX = sx + TOP_LEFT_RIGHT * 0.5f;

		for (int x = startX; x < endX; x++) {
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

			if (topAngle < 0)topAngle = 0;

			wideT = WIDE_WIDE + WIDE_WIDE * (sinf(topAngle));		//この数字をかける
			wideB = WIDE_WIDE + WIDE_WIDE * (sinf(bottomAngle));

			lt = SCREEN_WIDTH * 0.5f + wideT * numX;
			rt = SCREEN_WIDTH * 0.5f + wideT * (numX + 1);
			lb = SCREEN_WIDTH * 0.5f + wideB * numX;
			rb = SCREEN_WIDTH * 0.5f + wideB * (numX + 1);
			
			if (numY == 0) {
				//DrawBoxColor_TB_FOUR(&hrizon, &lineB, &lt, &rt, &lb, &rb, &col);
				//DrawSprite_TB_FOUR(&box, &hrizon, &lineT, &lb, &rb, &lt, &rt);
				DrawSprite_TB_FOUR(&box, &hrizon, &lineT, &lb, &rb, &lb, &rb);
			}

			//DrawBoxColor_TB_FOUR(&lineT, &lineB, &lt, &rt, &lb, &rb, &col);

			DrawSprite_TB_FOUR(&box, &lineT, &lineB, &lt, &rt, &lb, &rb);
			if (numY == 0) {

				//DrawNumberSumple(D3DXVECTOR2(0, 200), D3DXVECTOR2(50, 50), lt - rt);
				/*DrawNumberSumple(D3DXVECTOR2(300, 200), D3DXVECTOR2(50, 50), lineT);
				DrawNumberSumple(D3DXVECTOR2(500, 200), D3DXVECTOR2(50, 50), hrizon);*/
				//DrawNumberSumple(D3DXVECTOR2(300, 100), D3DXVECTOR2(50, 50), numX);
			}


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



	/*MyString* ms = new MyString("World Wide Pokemon Project");

	D3DXVECTOR2 sp = { 0,0, };
	D3DXVECTOR2 ss = { 50,50, };
	D3DXCOLOR sc = { 1,1,1,1 };

	ms->DrawString(sp,ss,sc);

	delete ms;*/
}
