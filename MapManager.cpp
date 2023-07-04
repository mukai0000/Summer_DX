#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"

#define BLOCK_SIZE			50
#define HULF_PI				1.5703f

#define DRAW_NUM			12					//プレイヤーから地平線までの数 4で割れる数字にしたい
#define HORIZONTAL_NUM		DRAW_NUM*0.75f
#define UNDER_NUM			DRAW_NUM*0.25f
#define DRAW_ANGLE			1.0f/DRAW_NUM		//倍率

#define DRAW_WIDETH			20

Map::Map()
{
	sumple = { 
		BLOCK_SIZE * MAP_SIZE * 0.5f,
		BLOCK_SIZE * MAP_SIZE * 0.5f 
	};

	m_MouseTex = LoadTexture((char*)"data/TEXTURE/MousePoint.png");

}

void Map::InitMapManager(D3DXVECTOR2* playerPos)
{
}

void Map::UninitMapManager()
{
}

void Map::UpdateMapManager()
{
	/*if (GetKeyboardPress(DIK_A)) {
		sumple.x -= 5;
	}
	if (GetKeyboardPress(DIK_D)) {
		sumple.x += 5;
	}*/
	if (GetKeyboardPress(DIK_W)) {
		sumple.y -= 5;
	}
	if (GetKeyboardPress(DIK_S)) {
		sumple.y += 5;
	}
}

void Map::DrawMapManager()
{
	//プレイヤーのいるY座標を簡易変換？
	int sy = sumple.y / 50;									//プレイヤーの今いる簡易Y座標
	float subY = (float)((int)sumple.y % 50) / 50.0f;		//プレイヤーのY座標の差分	子の差分のぶんだけマップの座標の描画をずらして移動しているように見せる　これに
	
	float hrizon = SCREEN_HEIGHT * 0.2f;	//マップ描画の地平線　
	float under = SCREEN_HEIGHT * 0.8f;		//地平線からプレイヤー側の画面外までの差分


	//プレイヤーのいるX座標を簡易変換
	int sx = sumple.x / 50;
	float subX = (float)((int)sumple.x % 50) / 50.0f;		//プレイヤーのX座標の差分





	int num = 0;			//地平線から何個目のやつか

	for (int y = sy - HORIZONTAL_NUM; y < sy + UNDER_NUM; y++) {		//描画する数を制限
		float subAngle = HULF_PI * DRAW_ANGLE * subY;
		float wideT = 1 - cosf(HULF_PI * DRAW_ANGLE * num + subAngle);	
		num++;															//numの更新ここはダメだと思うけど　めんどくさいから一時的に
		float wideB = 1 - cosf(HULF_PI * DRAW_ANGLE * num + subAngle);

		float lineT = hrizon + under * wideT;
		float lineB = hrizon + under * wideB;

		D3DXCOLOR col = { //緑をだんだんこく
			1.0f - 0.02f * y,
			1.0f - 0.02f * y,
			1.0f - 0.02f * y,
			1.0f 
		};

		//for (int x = 0;x < MAP_SIZE; x++) {								//xはまだいじらない
		float lt = 0;
		float rt = SCREEN_WIDTH;
		float lb = 0;
		float rb = SCREEN_WIDTH;
		DrawBoxColor_TB_FOUR(&lineT, &lineB, &lt, &rt, &lb, &rb, &col);
		//}
	}


	//プレイヤーの描画場所は固定
	D3DXVECTOR2 pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.7f };
	D3DXVECTOR2 siz = { 100,100 };
	D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f };
	DrawBoxColor(&pos, &siz, col);

	//DrawSpriteLeftTop(m_MouseTex, mouse.x, mouse.y, 30, 30, 0, 0, 1, 1);
	DrawSpriteLeftTop(m_MouseTex, GetMousePosition().x, GetMousePosition().y, 30, 30, 0, 0, 1, 1);
	//ShowCursor(true);
	ShowCursor(false);
	
}
