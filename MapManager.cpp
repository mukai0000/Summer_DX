#include "MapManager.h"
#include "input.h"
#include "sprite.h"
#include "main.h"
#include "game.h"

#include "myString.h"

#include <windows.h>
#include <time.h>

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
	SetTarget(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7));

	InitiarizeMap();

	m_MapTex = SetTexture("data/TEXTURE/Tile.png", 16, 16, 256);

	/*m_CameraCentor = {			  
		BLOCK_SIZE * MAP_SIZE * 0.9f,
		BLOCK_SIZE * MAP_SIZE * 0.9f
	};*/
	mouse = {
		SCREEN_WIDTH * 0.2f,
		SCREEN_HEIGHT * 0.2f
	};

	m_MouseTex = LoadTexture((char*)"data/TEXTURE/MousePoint.png");
	m_BGTex = LoadTexture((char*)"data/TEXTURE/sky.png");


	m_Time = MAX_TIME;

	//プレイヤーの初期化
	InitializePlayer();
	//プレイヤーの初期化した値を受け取る　いらないっちゃいらないけど作ったから使う
	Init(&m_PlayerData.pos);

	m_CameraCentor = m_PlayerData.pos;

	m_Mode = MODE::MODE_MOVE;
	/*for (int i = 0; i < ENEMY_BULLET; i++) {
		m_EnemyBullet[i].isActive = false;
	}*/

	//UIUIUIUIUIUIUI
	UI_DATA=SetUI_DATA("",1,1,1)
	m_HpBar=new GageBar()


}

void Map::Init(D3DXVECTOR2* playerPos)
{
	m_PlayerPos = playerPos;
}

void Map::Uninit()
{
}

void Map::Update()
{

	/*int speed = 1;

	if (GetKeyboardPress(DIK_LSHIFT)) {
		speed = 10;
	}
	if (GetKeyboardPress(DIK_A)) {
		m_CameraCentor.x -= speed;
	}
	if (GetKeyboardPress(DIK_D)) {
		m_CameraCentor.x += speed;
	}
	if (GetKeyboardPress(DIK_W)) {
		m_CameraCentor.y -= speed;
	}
	if (GetKeyboardPress(DIK_S)) {
		m_CameraCentor.y += speed;
	}*/

	Player_Update();

	m_CameraCentor = m_PlayerData.pos;
	//m_CameraCentor = *m_PlayerPos;

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
	else if (m_CameraCentor.y >= MAP_SIZE * BLOCK_SIZE - BLOCK_SIZE * 3) {
		m_CameraCentor.y = MAP_SIZE * BLOCK_SIZE - BLOCK_SIZE * 3;
	}


}

void Map::Update_Move()
{
}

void Map::Draw()
{
	//ソラ
	DrawSpriteLeftTop(m_BGTex, 0, -500, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);


	TEXTURE_DATA box = SetTexture("data/TEXTURE/box.png", 1, 1, 1);


	WIDE_POS t, b;
	float z = 0;
	float w = SCREEN_WIDTH * 0.5f;

	int centorY= m_CameraCentor.y * 0.02f;
	int startY = (m_CameraCentor.y - DRAW_HIGHT) * 0.02f;		//1ﾏｽ50だから0.02でかける
	int endY = ((m_CameraCentor.y + DRAW_UNDER) * 0.02f);		//1ﾏｽ50だから0.02でかける
	t = { HOLIZON_POS,WIDE_WIDE };
	b = GetMapDrawPos(startY + 1);

	//横幅描画用
	int centorX = m_CameraCentor.x * 0.02f;
	int endX = centorX + TOP_LEFT_RIGHT * 0.5f;
	int startX = centorX - endX;
	float lt, rt, lb, rb, subX;
	subX = (int)(m_CameraCentor.x + 0.5f) % BLOCK_SIZE * 0.02f;

	for (int y = startY; y <= endY; y++) {
		for (int x = startX; x <= endX; x++) {

			lt = x * t.wide + SCREEN_WIDTH * 0.5f - (t.wide * subX);
			rt = x * t.wide + t.wide + SCREEN_WIDTH * 0.5f - (t.wide * subX);
			lb = x * b.wide + SCREEN_WIDTH * 0.5f - (b.wide * subX);
			rb = x * b.wide + b.wide + SCREEN_WIDTH * 0.5f - (b.wide * subX);

			if (y >= 0 && y <= MAP_SIZE && centorX + x >= 0 && centorX + x < MAP_SIZE) {
				int tile = m_Map[y][x + centorX];
				//DrawSprite_TB_FOUR(&box, &t.pos, &b.pos, &lt, &rt, &lb, &rb);
				if (m_Map[y][x + centorX] == 10) {
					DrawSprite_TB_FOUR(m_MapTex, t.pos, b.pos, lt, rt, lb, rb, 1 + 16);
				}
				else {
					DrawSprite_TB_FOUR(m_MapTex, t.pos, b.pos, lt, rt, lb, rb, tile);
				}
			}

		}

		t = b;
		b = GetMapDrawPos(y + 2);
	}

	Player_Draw();
	////プレイヤーの描画場所は基本固定
	//WIDE_POS wp = GetDrawWidePos(D3DXVECTOR2(1250,1250 + aaaa));
	//D3DXVECTOR2 pos = {(float)(wp.pos+ SCREEN_WIDTH * 0.5),GetMapDrawPos(1250.0f+aaaa).pos };
	//D3DXVECTOR2 siz = { wp.wide,wp.wide };
	//D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f };
	//int a = 1;
	////DrawBoxColor(&pos, &siz, col);
	//DrawAnimation_BottomCentor(SetTexture("data/TEXTURE/box.png", 1, 1, 1), pos, siz, col, a);

	mouse.x += GetMouseX();
	mouse.y += GetMouseY();

	//DrawSpriteLeftTop(m_MouseTex, GetMousePosition().x, GetMousePosition().y, 30, 30, 0, 0, 1, 1);
	////ShowCursor(true);
	//ShowCursor(false);


	//DrawNumberSumple(D3DXVECTOR2(100, 100), D3DXVECTOR2(50, 50), (int)(m_CameraCentor.x));
}

bool Map::GetCollider(const D3DXVECTOR2& move)
{
	int x, y;
	x = y = 0;
	x = (int)((m_PlayerPos->x + move.x) / MAP_SIZE);
	y = (int)((m_PlayerPos->y + move.y) / MAP_SIZE);

	if (x < 0 || y < 0 || y >= MAP_SIZE || x >= MAP_SIZE)return false;

	if (m_Map[y][x] != 10)return true;

	return false;
}
								 
bool Map::GetCollider(const D3DXVECTOR2& pos, const D3DXVECTOR2& move)
{
	int x, y;
	x = y = 0;
	x = (int)(pos.x + move.x);
	y = (int)(pos.y + move.y);

	x /= BLOCK_SIZE;
	y /= BLOCK_SIZE;

	if (x < 0 || y < 0|| y >= MAP_SIZE || x >= MAP_SIZE)return false;

	if (m_Map[y][x] != 10)return true;

	return false;
}


WIDE_POS Map::GetDrawWidePos(D3DXVECTOR2 pos)
{
	WIDE_POS ret = { 0,0 };	

	float angle = GetDrawAngle(pos.y);					//角度取得
	if (angle < 0 /*|| angle>HULF_PI*/)return ret;		//画面外だったら

	ret.wide = WIDE_WIDE * (1 + (sinf(angle) * 0.5f));	//1ブロックの幅ﾎﾟｲﾝｺﾞﾈ

	float subX = pos.x - m_CameraCentor.x;
	subX = (int)(subX + 0.5f) * 0.02f;					//内部管理は50で1マスだから
	ret.pos = subX * ret.wide;

	return ret;
}

float Map::GetDrawHight(float y)	//Holizonに追加して使う　地平線から基準点までを1とした割合
{
	float angle = GetDrawAngle(y);		//角度を取得
	if (angle < 0)return -1.0f * (float)(1.0f - cos(angle));		//範囲外だったら終了

	return 1.0f - (float)cos(angle);
}

float Map::GetDrawHight(int y)
{
	float posY = y * BLOCK_SIZE;
	float angle = GetDrawAngle(posY);		//角度を取得
	if (angle < 0)return -1.0f * (float)(1.0f - cos(angle));			//範囲外だったら終了

	return 1.0f - (float)cos(angle);
}

float Map::GetDrawAngle(float y)
{
	//描画外だったら－1 これいらないかも
	//if (y< m_CameraCentor.y - DRAW_HIGHT || y>m_CameraCentor.y + DRAW_UNDER)return -1;

	//小数点以下を四捨五入
	int pos = (int)((y + 0.5f) - (m_CameraCentor.y - DRAW_HIGHT));

	//地平線から画面したまでの割合
	float ret = pos / (DRAW_HIGHT + DRAW_UNDER);


	return ret * HULF_PI;
}

void Map::SetPlayerShot(const D3DXVECTOR2& vel)
{
	if (m_PlayerData.energy >= USE_ENERGY && m_PlayerData.shotTime <= 0) {
		for (int i = 0; i < PLAYER_BULLET; i++) {
			if (m_PlayerBullet[i].isActive) {
				m_PlayerBullet[i].isActive = true;
				m_PlayerBullet[i].pos = m_PlayerData.pos;
				m_PlayerBullet[i].vel = vel * 10;
				m_PlayerData.energy -= USE_ENERGY;
				m_PlayerData.shotTime = m_PlayerData.coolTime;				
				break;
			}
		}
	}
}

void Map::Player_Draw()
{
	WIDE_POS wp = GetDrawWidePos(m_PlayerData.pos);
	D3DXVECTOR2 pos = { (float)(wp.pos + SCREEN_WIDTH * 0.5),GetMapDrawPos(m_PlayerData.pos.y).pos};
	D3DXVECTOR2 siz = { wp.wide,wp.wide };
	D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f };
	//プレイヤーのアニメフレーム管理時間/アニメ切り替え時間％アニメの数　+テクスチャの横分割数＊向いてる方向
	int anim = (m_PlayerAnimFlame / m_PlayerAnimTime % ANIM_MAX) + m_PlayerTex.wide * m_PlayerLook;

	//DrawBoxColor(&pos, &siz, col);
	DrawAnimation_BottomCentor(m_PlayerTex, pos, siz, col, anim);
}

void Map::PlayerDrawPosUpdate()
{
	//アップデートフラグがTrueだったら
	if (m_IsMoveUP) {
		m_PlayerData.draw.y = GetDrawHight(m_PlayerData.pos.y);
		WIDE_POS wp=GetDrawWidePos(m_PlayerData.pos);
		m_PlayerData.draw.x = wp.pos;
		m_PlayerData.drawWide = wp.wide;
	}
}

void Map::InitiarizeMap()
{
	char mp[MAP_SIZE][MAP_SIZE]=
	{
		10,10,10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10,10,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,

		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,

		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,

		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1,10,
		10,10,10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10,10,10, 10,10,10,10,10,10,10,10,10,10,
	};
	srand(time(nullptr));
	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++) {
			if (mp[y][x] == 10)	m_Map[y][x] = 10;
			else if (mp[y][x] == 1) {
				int r = rand() % 100;
				if (r < 7)m_Map[y][x] = 3 + 16;
				else if (r < 20)m_Map[y][x] = 2 + 16;
				else m_Map[y][x] = 1 + 16;
			}
		}
	}
}

void Map::InitializePlayer()
{
	m_PlayerTex = SetTexture("data/TEXTURE/player_walk.png", 3, 4, 12);

	//下向き
	m_PlayerLook = LOOK_DOWN;
	//
	m_PlayerData.pos = {
		BLOCK_SIZE * MAP_SIZE * 0.5f,		
		BLOCK_SIZE * MAP_SIZE * 0.5f };
	m_PlayerData.maxEnergy = 100;
	m_PlayerData.energy = m_PlayerData.maxEnergy;
	m_PlayerData.maxHp = 200;
	m_PlayerData.hp = m_PlayerData.maxHp;
	m_PlayerData.shotTime = 0;
	m_PlayerData.coolTime = 30;

	m_PlayerBullet = new BULLET[PLAYER_BULLET];		//プレイヤーの玉の配列宣言
	//m_EnemyBullet = new BULLET[ENEMY_BULLET];
	for (int i = 0; i < PLAYER_BULLET; i++) {
		m_PlayerBullet[i].isActive = false;
		m_PlayerBullet[i].pos = { 0.0f,0.0f };
		m_PlayerBullet[i].vel = { 0.0f,0.0f };
	}
}

void Map::Player_Update()
{
	D3DXVECTOR2 vel = { 0.0f,0.0f };
	int spd = 2;

	if (GetKeyboardPress(DIK_LSHIFT))spd = 3;

	//同時押しされてないとき 同時押しの時は軸移動は停止
	if (GetKeyboardPress(DIK_D) && !GetKeyboardPress(DIK_A)) {
		m_PlayerLook = LOOK_RIGHT;
		vel.x = 1.0f;
	}
	else if (!GetKeyboardPress(DIK_D) && GetKeyboardPress(DIK_A)) {
		m_PlayerLook = LOOK_LEFT;
		vel.x = -1.0f;
	}
	
	if (GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_S)) {
		m_PlayerLook = LOOK_UP;
		vel.y = -1.0f;
	}
	else if (!GetKeyboardPress(DIK_W) && GetKeyboardPress(DIK_S)) {
		m_PlayerLook = LOOK_DOWN;
		vel.y = 1.0f;
	}

	//アニメーション用
	if (!GetKeyboardPress(DIK_D) && !GetKeyboardPress(DIK_A) &&
		!GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_S)) {
		m_PlayerAnimFlame = m_PlayerAnimTime * ANIM_IDOL;
	}
	else {
		m_PlayerAnimFlame++;
	}
	//アニメーション用

	//単位塩化
	D3DXVec2Normalize(&vel, &vel);

	//玉の発射
	//velの数値がいじられる前に球の発射
	if (GetKeyboardPress(DIK_SPACE)) {
		SetPlayerShot(vel);
	}

	//実際の移動速度
	vel *= spd;

	//移動先が移動不可だったらその軸の移動は０
	if(!GetCollider(m_PlayerData.pos,D3DXVECTOR2(vel.x,0)))
	{
		vel.x = 0.0f;
	}
	if(!GetCollider(m_PlayerData.pos,D3DXVECTOR2(0, vel.y)))
	{
		vel.y = 0.0f;
	}

	m_PlayerData.pos += vel;
}

WIDE_POS Map::GetMapDrawPos(int y)
{
	WIDE_POS ret;
	float pos = HOLIZON_POS + (GetDrawHight(y) * HOLIZON_TO_BOTTOM_WIDE);
	ret.pos = pos;
	ret.wide = GetDrawWidePos(D3DXVECTOR2(0, y * BLOCK_SIZE)).wide;

	return ret;
}

WIDE_POS Map::GetMapDrawPos(float y)
{
	WIDE_POS ret;
	float pos = HOLIZON_POS + (GetDrawHight(y) * HOLIZON_TO_BOTTOM_WIDE);
	ret.pos = pos;
	ret.wide = GetDrawWidePos(D3DXVECTOR2(0, y)).wide;

	return ret;
}
