#pragma once
//===========================================
// マップ管理	MapManager.h
//	武藤海人		2023/06/29
//===========================================

#ifndef MAIN_H
#define MAIN_H
#include "main.h"
#include "texture.h"
#include "UI.h"
#endif // !MAIN_H

#define MAP_SIZE 50

typedef struct {
	float pos;
	float wide;
}WIDE_POS;

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 vel;
	bool isActive;
}BULLET;

typedef enum {
	MODE_MOVE,
	MODE_SHOT,
	MODE_PLAY
}MODE;

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 draw;
	float drawWide;
	float hp;
	float maxHp;
	float energy;
	float maxEnergy;
	int shotTime;
	int coolTime;
}PLAYER_DATA;

typedef enum {
	LOOK_DOWN,
	LOOK_LEFT,
	LOOK_RIGHT,
	LOOK_UP,
	LOOK_MAX
}LOOK_VEC;

typedef enum {
	ANIM_1,
	ANIM_2,
	ANIM_IDOL = 1,
	ANIM_3,
	ANIM_MAX
}PLAYER_ANIM;

typedef struct {
	bool isLive;

}ENEMY_DATA;

class Map
{
public:
	Map();
	~Map() {};


	//基礎
	void Init(D3DXVECTOR2* playerPos);
	void Uninit();
	void Update();
	void Update_Move();
	void Draw();


	bool GetCollider(const D3DXVECTOR2& move);
	bool GetCollider(const D3DXVECTOR2& pos, const D3DXVECTOR2& move);

	//補助
	WIDE_POS	GetDrawWidePos(const D3DXVECTOR2 pos);
	float		GetDrawHight(const float y);
	float		GetDrawHight(const int y);
	float		GetDrawAngle(const float y);


	//弾発射

	void		SetEnemyShot(D3DXVECTOR2 pos);

private:
	void		InitiarizeMap();

	//Player
	void		InitializePlayer();
	void		Player_Update();
	void		SetPlayerShot(const D3DXVECTOR2& vel);
	void		Player_Draw();
	void		PlayerDrawPosUpdate();
private:
	WIDE_POS	GetMapDrawPos(int y);
	WIDE_POS	GetMapDrawPos(float y);

	D3DXVECTOR2* m_PlayerPos;			//プレイヤーの場所を取得するために必要なもの

	D3DXVECTOR2 m_CameraCentor;

	D3DXVECTOR2 mouse;

	char m_Map[MAP_SIZE][MAP_SIZE];
	float subX, subY;
	
	//画像
	unsigned int m_MouseTex;

	unsigned int m_BGTex;

	TEXTURE_DATA m_MapTex;

	//画像

	//プレイヤー回り
	TEXTURE_DATA m_PlayerTex;
	const int PLAYER_BULLET = 10;
	const int ENEMY_BULLET = 20;
	BULLET* m_PlayerBullet;
	BULLET* m_EnemyBullet;

	bool m_IsMoveUP;

	PLAYER_DATA m_PlayerData;
	LOOK_VEC	m_PlayerLook;

	const int USE_ENERGY = 30;

	int m_PlayerAnimFlame;
	const int m_PlayerAnimTime = 20;

	GageBar* m_HpBar = nullptr;
	GageBar* m_MpBar = nullptr;

	//プレイヤー回り

	const int MAX_TIME = 1800;
	int m_Time;

	MODE m_Mode;

	int m_Score;

	//定数
	
};