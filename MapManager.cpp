#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"

#define BLOCK_SIZE (50)
#define HULF_PI (1.5703f)

#define DRAW_NUM (12)					//プレイヤーから地平線までの数 4で割れる数字にしたい
#define HORIZONTAL_NUM DRAW_NUM*0.75f
#define UNDER_NUM DRAW_NUM*0.25f
#define DRAW_ANGLE 1.0f/DRAW_NUM	//倍率

Map::Map()
{
	sumple = { 
		BLOCK_SIZE * MAP_SIZE * 0.5f,
		BLOCK_SIZE * MAP_SIZE * 0.5f 
	};

	//初期化
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			m_Map[i][j] = 0;
		}
	}
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
	//y
	int sy = sumple.y /50;									//プレイヤーの今いる場所
	int num = 0;

	float hrizon = SCREEN_HEIGHT * 0.2f;
	float under = SCREEN_HEIGHT * 0.8f;

	for (int y = sy - HORIZONTAL_NUM; y < sy + UNDER_NUM; y++) {		//描画する数を制限

		float wideT = 1-cosf(HULF_PI * DRAW_ANGLE * num);
		float wideB = 1-cosf(HULF_PI * DRAW_ANGLE * (num + 1.0f));

		float lineT = hrizon + under * wideT;
		float lineB = hrizon + under * wideB;

		//for(int x;)
		D3DXCOLOR col = { //緑をだんだんこく
			1.0f - 0.08f * y,
			1.0f - 0.08f * y,
			1.0f - 0.08f * y,
			1.0f 
		};
		for (int x = 0;x < MAP_SIZE; x++) {								//xはまだいじらない
		float lt = 0;
		float rt = SCREEN_WIDTH;
		float lb = 0;
		float rb = SCREEN_WIDTH;
		DrawBoxColor_TB_FOUR(&lineT, &lineB, &lt, &rt, &lb, &rb, &col);
		}
		num++;
	}


	//プレイヤーの描画場所は固定
	D3DXVECTOR2 pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.7f };
	D3DXVECTOR2 siz = { 100,100 };
	D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f };
	DrawBoxColor(&pos, &siz, col);
}
