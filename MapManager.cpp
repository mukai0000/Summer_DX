#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"

#include "myString.h"

#include <windows.h>

#define BLOCK_SIZE					50
#define HULF_PI						1.5703f

#define HORIZON_TO_UNDER			12								//プレイヤーから地平線までの数 4で割れる数字にしたい
#define HORIZON_TO_PLAYER			(HORIZON_TO_UNDER*0.75f)		//水平線からプレイヤーまでの描画数
#define PLAYER_TO_UNDER				(HORIZON_TO_UNDER*0.25f)		//プレイヤーから画面が今での描画数
#define DRAW_ANGLE_Y				(1.0f/HORIZON_TO_UNDER)			//角度倍率

#define UNDER_LEFT_TO_RIGHT			16								//プレイヤーのいる高さは左右に8つずつ描画するから
#define TOP_LEFT_RIGHT				(UNDER_LEFT_TO_RIGHT*1.5)
#define WIDE_WIDE					SCREEN_WIDTH/TOP_LEFT_RIGHT		//これが基準になる幅

#define HOLIZON_POS					(SCREEN_HEIGHT*0.2)
#define HOLIZON_TO_BOTTOM_WIDE		(SCREEN_HEIGHT-HOLIZON_POS)
#define HOLIZON_TO_TARGET_WIDE		(HOLIZON_TO_BOTTOM_WIDE*0.7)

#define DRAW_HIGHT					(BLOCK_SIZE*HORIZON_TO_PLAYER)
#define DRAW_UNDER					(BLOCK_SIZE*PLAYER_TO_UNDER)

Map::Map()
{

	m_CameraCentor = {			  
		BLOCK_SIZE * MAP_SIZE * 0.9f,
		BLOCK_SIZE * MAP_SIZE * 0.9f
	};
	mouse = {
		SCREEN_WIDTH * 0.2f,
		SCREEN_HEIGHT * 0.2f
	};

	m_MouseTex = LoadTexture((char*)"data/TEXTURE/MousePoint.png");
	m_BGTex = LoadTexture((char*)"data/TEXTURE/sky.png");

	isMouse = !true;
}

void Map::InitMapManager(D3DXVECTOR2* playerPos)
{
	m_PlayerPos = playerPos;
}

void Map::UninitMapManager()
{
}

void Map::UpdateMapManager()
{
	int speed = 1;
	if (GetKeyboardPress(DIK_A)) {
		m_CameraCentor.x -= speed;
	}
	if (GetKeyboardPress(DIK_D)) {
		m_CameraCentor.x += speed;
	}

	if (GetKeyboardTrigger(DIK_W) && GetKeyboardPress(DIK_LSHIFT)) {
		m_CameraCentor.y -= speed;
	}
	else if (GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_LSHIFT)) {
		m_CameraCentor.y -= speed;
		//if (sumple.y > 450)
	}

	if (GetKeyboardTrigger(DIK_S) && GetKeyboardPress(DIK_LSHIFT)) {
		m_CameraCentor.y += speed;
	}
	else if (GetKeyboardPress(DIK_S) && !GetKeyboardPress(DIK_LSHIFT)) {
		m_CameraCentor.y += speed;
	}

	//画面外に出ない用
	//X
	if (m_CameraCentor.x <= BLOCK_SIZE * 8) {
		m_CameraCentor.x = BLOCK_SIZE * 8;
	}
	else if (m_CameraCentor.x >= MAP_SIZE * BLOCK_SIZE - BLOCK_SIZE * 8) {
		m_CameraCentor.x = MAP_SIZE * BLOCK_SIZE - BLOCK_SIZE * 8;
	}
	//Y
	if (m_CameraCentor.y <= BLOCK_SIZE * 9) {
		m_CameraCentor.y = BLOCK_SIZE * 9;
	}
	else if (m_CameraCentor.y >= MAP_SIZE * BLOCK_SIZE - BLOCK_SIZE * 2) {
		m_CameraCentor.y = MAP_SIZE * BLOCK_SIZE - BLOCK_SIZE * 2;
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


	TEXTURE_DATA box = SetTexture("data/TEXTURE/box.png", 1, 1, 1);

	{
	// ひとまずコメントアウト
	//プレイヤーのいるY座標を簡易変換？
	//int sy = (int)m_CameraCentor.y / 50;							//プレイヤーの今いる簡易Y座標
	//float subY = (float)((int)m_CameraCentor.y % 50) / 50.0f;			//プレイヤーのY座標の差分	子の差分のぶんだけマップの座標の描画をずらして移動しているように見せる　これに

	//float hrizon = SCREEN_HEIGHT * 0.2f;					//マップ描画の地平線　
	//float under = SCREEN_HEIGHT - hrizon;					//地平線からプレイヤー側の画面外までの差分


	////地平線がビコビコするのはここで小数点以下切り捨てにしてしまってる部分を拾ってないから?

	////プレイヤーのいるX座標を簡易変換
	//int sx = (int)m_CameraCentor.x / 50;
	//float subX = (float)((int)m_CameraCentor.x % 50) / 50.0f;		//プレイヤーのX座標の差分


	//int numY = 0;			//地平線から何個目のやつかのYバージョン
	//float hWideT, hWideB, lineT, lineB, subAngle, topAngle, bottomAngle;

	//int startY = (int)(sy - HORIZON_TO_PLAYER);
	//int endY = (int)(sy + PLAYER_TO_UNDER);

	//for (int y = startY; y < endY; y++) {		//描画する数を制限

	//	subAngle = HULF_PI * DRAW_ANGLE_Y * subY;								//プレイヤーの移動によって発生した角度の端数？

	//	topAngle = HULF_PI * DRAW_ANGLE_Y * numY + subAngle;					//描画のチップのうえ座標の角度
	//	bottomAngle = HULF_PI * DRAW_ANGLE_Y * (numY + 1) + subAngle;			//描画のチップの下の座標の角度

	//	hWideT = 1 - cosf(topAngle);
	//	hWideB = 1 - cosf(bottomAngle);

	//	lineT = hrizon + under * hWideT;
	//	lineB = hrizon + under * hWideB;

	//	int numX = (int)(-TOP_LEFT_RIGHT * 0.5f);				//プレイヤーから何個ずれたやつか

	//	float wideT, wideB;								//□の上と下の辺の長さ
	//	float lt, rt, lb, rb;							///左上右上左下右下のX座標

	//	int startX = (int)(sx - TOP_LEFT_RIGHT * 0.5f);
	//	int endX = (int)(sx + TOP_LEFT_RIGHT * 0.5f);

	//	for (int x = startX; x < endX; x++) {
	//		//水平線が２　プレイヤーのとこより下が３にする予定

	//		D3DXCOLOR col = { //緑をだんだんこく
	//			1.0f - 0.05f * x,
	//			1.0f - 0.05f * x,
	//			1.0f - 0.05f * x,
	//			//1.0f - 0.05f * y,
	//			//1.0f - 0.05f * y,
	//			//1.0f - 0.05f * y,
	//			1.0f
	//		};

	//		if (topAngle < 0)topAngle = 0;

	//		wideT = (float)(WIDE_WIDE + WIDE_WIDE * (sinf(topAngle)));		//この数字をかける
	//		wideB = (float)(WIDE_WIDE + WIDE_WIDE * (sinf(bottomAngle)));

	//		lt = SCREEN_WIDTH * 0.5f + wideT * numX;
	//		rt = SCREEN_WIDTH * 0.5f + wideT * (numX + 1);
	//		lb = SCREEN_WIDTH * 0.5f + wideB * numX;
	//		rb = SCREEN_WIDTH * 0.5f + wideB * (numX + 1);
	//		
	//		if (numY == 0) {
	//			//DrawBoxColor_TB_FOUR(&hrizon, &lineB, &lt, &rt, &lb, &rb, &col);
	//			//DrawSprite_TB_FOUR(&box, &hrizon, &lineT, &lb, &rb, &lt, &rt);
	//			DrawSprite_TB_FOUR(&box, &hrizon, &lineT, &lb, &rb, &lb, &rb);
	//		}

	//		//DrawBoxColor_TB_FOUR(&lineT, &lineB, &lt, &rt, &lb, &rb, &col);

	//		else DrawSprite_TB_FOUR(&box, &lineT, &lineB, &lt, &rt, &lb, &rb);
	//		if (numY == 0) {

	//			//DrawNumberSumple(D3DXVECTOR2(0, 200), D3DXVECTOR2(50, 50), lt - rt);
	//			//DrawNumberSumple(D3DXVECTOR2(300, 200), D3DXVECTOR2(50, 50), lineT);
	//			//DrawNumberSumple(D3DXVECTOR2(500, 200), D3DXVECTOR2(50, 50), hrizon);
	//			//DrawNumberSumple(D3DXVECTOR2(300, 100), D3DXVECTOR2(50, 50), numX);
	//		}


	//		numX++;
	//	}
	//	if (numY <= y)numY++;
	//}
	}

	WIDE_POS t, b;
	float z = 0;
	float w = SCREEN_WIDTH * 0.5f;

	int startY = (m_CameraCentor.y - DRAW_HIGHT) * 0.02f;		//1ﾏｽ50だから0.02で割る
	int endY = ((m_CameraCentor.y + DRAW_UNDER) * 0.02f);		//1ﾏｽ50だから0.02で割る
	t = { HOLIZON_POS,WIDE_WIDE };
	b = GetMapDrawPos(startY + 1);
	//b = GetMapDrawPos(m_CameraCentor.y  * 0.02f);

	/*float T,B;
	T = 0;
	B = GetDrawHight(startY + 1);*/

	//横幅描画用
	int centorX = m_CameraCentor.x * 0.02f;
	int endX = centorX + TOP_LEFT_RIGHT * 0.5f;
	int startX = centorX - endX;
	float lt, rt, lb, rb, subX;
	subX = (int)(m_CameraCentor.x + 0.5f) % BLOCK_SIZE * 0.02f;

	for (int y = startY; y <= endY; y++) {

		/*if (T>=0 || B >= 0) {
			if (T < 0)T = 0.0f;
			float tp = HOLIZON_POS + (HOLIZON_TO_BOTTOM_WIDE * T);
			float bp = HOLIZON_POS + (HOLIZON_TO_BOTTOM_WIDE * B);
			float l, r;
			l = w;
			r = SCREEN_WIDTH;
			DrawSprite_TB_FOUR(&box, &tp, &bp, &l, &r, &l, &r);
		}*/

		for (int x = startX; x <= endX; x++)
		{
			
			lt = x * t.wide + SCREEN_WIDTH * 0.5 - (t.wide * subX);
			rt = x * t.wide + t.wide + SCREEN_WIDTH * 0.5 - (t.wide * subX);
			lb = x * b.wide + SCREEN_WIDTH * 0.5 - (b.wide * subX);
			rb = x * b.wide + b.wide + SCREEN_WIDTH * 0.5 - (b.wide * subX);
			if (y >= 0 && y <= MAP_SIZE && centorX + x >= 0 && centorX + x < MAP_SIZE) {
				DrawSprite_TB_FOUR(&box, &t.pos, &b.pos, &lt, &rt, &lb, &rb);
			}
		}

		t = b;
		b = GetMapDrawPos(y + 2);
		/*T = B;
		B = GetDrawHight(i+1);*/
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



	DrawNumberSumple(D3DXVECTOR2(100, 100), D3DXVECTOR2(50, 50), (int)(m_CameraCentor.y));



	/*MyString* ms = new MyString("World Wide Pokemon Project");

	D3DXVECTOR2 sp = { 0,0, };
	D3DXVECTOR2 ss = { 50,50, };
	D3DXCOLOR sc = { 1,1,1,1 };

	ms->DrawString(sp,ss,sc);

	delete ms;*/
}

bool Map::GetCollider(D3DXVECTOR2* move)
{
	int x, y;
	x = (int)((m_PlayerPos->x + move->x) / MAP_SIZE);
	y = (int)((m_PlayerPos->y + move->y) / MAP_SIZE);

	if (m_Map[y][x] == 0)return true;



	return false;
}

bool Map::GetCollider(D3DXVECTOR2* pos, D3DXVECTOR2* move)
{
	int x, y;
	x = (int)((pos->x + move->x) / MAP_SIZE);
	y = (int)((pos->y + move->y) / MAP_SIZE);

	if (m_Map[y][x] == 0)return true;



	return false;
}


WIDE_POS Map::GetDrawWidePos(D3DXVECTOR2 pos)
{
	WIDE_POS ret = { 0,0 };

	float angle = GetDrawAngle(pos.y);				//角度取得
	if (angle < 0 /*|| angle>HULF_PI*/)return ret;		//画面外だったら

	ret.wide = WIDE_WIDE * (1 + (sinf(angle) * 0.5f));

	float subX = pos.x - m_CameraCentor.x;
	subX = (int)(subX + 0.5f) * 0.02f;				//内部管理は50で1マスだから
	ret.pos = subX * ret.wide;

	return ret;
}

float Map::GetDrawHight(float y)	//Holizonに追加して使う　地平線から基準点までを1とした割合
{
	float angle = GetDrawAngle(y);		//角度を取得
	if (angle < 0)return -1 * (1.0f - cos(angle));			//範囲外だったら終了

	return 1.0f - cos(angle);
}

float Map::GetDrawHight(int y)
{
	float posY = y * BLOCK_SIZE;
	float angle = GetDrawAngle(posY);		//角度を取得
	if (angle < 0)return -1 * (1.0f - cos(angle));			//範囲外だったら終了

	return 1.0f - cos(angle);
}

float Map::GetDrawAngle(float y)
{
	//描画外だったら－1 これいらないかも
	//if (y< m_CameraCentor.y - DRAW_HIGHT || y>m_CameraCentor.y + DRAW_UNDER)return -1;

	//小数点以下を四捨五入
	int pos = (int)(y + 0.5f) - (m_CameraCentor.y - DRAW_HIGHT);

	//地平線から画面したまでの割合
	float ret = pos / (DRAW_HIGHT + DRAW_UNDER);


	return ret * HULF_PI;
}

WIDE_POS Map::GetMapDrawPos(int y)
{
	WIDE_POS ret;
	float pos = HOLIZON_POS + (GetDrawHight(y) * HOLIZON_TO_BOTTOM_WIDE);
	ret.pos = pos;
	ret.wide = GetDrawWidePos(D3DXVECTOR2(0, y * BLOCK_SIZE)).wide;

	return ret;
}
