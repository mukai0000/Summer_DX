/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_POLYGON 100	//表示するポリゴンの数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
struct POLYGON{
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2     size;	//大きさ
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
	float			rot;
};

static POLYGON g_Player;
static POLYGON g_Polygon[NUM_POLYGON];

static int g_TexNo = 0;
static float g_U = 0.0f;
static float g_V = 0.0f;
static int g_AnimePattern = 0;
static int g_AnimeSkipFrame = 0;



//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャの読み込み
	g_TexNo = LoadTexture((char*)"data/TEXTURE/airou.png");

	//初期化
	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = SCREEN_HEIGHT / 2;
	g_Player.size = D3DXVECTOR2(400.0f, 400.0f);
	g_Player.vel.x = 0.0f;
	g_Player.vel.y = 0.0f;
	g_Player.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.rot = 0.0f;

	for (int i = 0; i < NUM_POLYGON; i++)
	{
		g_Polygon[i].pos.x = frand() * SCREEN_WIDTH;
		g_Polygon[i].pos.y = frand() * SCREEN_HEIGHT;

		g_Polygon[i].vel.x = 0.0f;
		g_Polygon[i].vel.y = 0.0f;

		g_Polygon[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		g_Polygon[i].rot = frand()*(D3DX_PI * 2);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
	for (int i = 0; i < NUM_POLYGON; i++)
	{
		g_Polygon[i].rot += 0.01f;
	}

	//キーボード
	if (GetKeyboardPress(DIK_UP))
	{
		g_Player.pos.y -= 5.0f;
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		g_Player.pos.y += 5.0f;
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		g_Player.pos.x -= 5.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_Player.pos.x += 5.0f;
	}

	if (GetKeyboardPress(DIK_D)) {
		g_Player.size.x += 5.0f;
	}
	if (GetKeyboardPress(DIK_A)) {
		g_Player.size.x -= 5.0f;
	}
	if (GetKeyboardPress(DIK_S)) {
		g_Player.size.y += 5.0f;
	}
	if (GetKeyboardPress(DIK_W)) {
		g_Player.size.y -= 5.0f;
	}

	if (GetKeyboardPress(DIK_Q)) {
		g_Player.rot -= 0.05f;
	}
	if (GetKeyboardPress(DIK_E)) {
		g_Player.rot += 0.05f;
	}



	//ゲームパッド
	if (IsButtonPressed(0, BUTTON_A) || GetKeyboardPress(DIK_SPACE))
	{
		//座標のリセット
		g_Player.pos.x = SCREEN_WIDTH / 2;
		g_Player.pos.y = SCREEN_HEIGHT / 2;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	for (int i = 0; i < NUM_POLYGON; i++)
	{
		DrawSpriteColorRotate(g_TexNo,
			g_Polygon[i].pos.x, g_Polygon[i].pos.y,
			300.0f, 300.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			g_Polygon[i].color.r, g_Polygon[i].color.g, g_Polygon[i].color.b, g_Polygon[i].color.a,
			g_Polygon[i].rot);
	}

	//プレイヤーの描画
	DrawSpriteColorRotate(g_TexNo,
		g_Player.pos.x, g_Player.pos.y,
		g_Player.size.x, g_Player.size.y,
		0.0f, 0.0f,
		1.0f, 1.0f,
		g_Player.color.r, g_Player.color.g, g_Player.color.b, g_Player.color.a,
		g_Player.rot);
}
