#pragma once
//===========================================
// �}�b�v�Ǘ�	MapManager.h
//	�����C�l		2023/06/29
//===========================================

#ifndef MAIN_H
#define MAIN_H
#include "main.h"
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
	float hp;
	float maxHp;
	float energy;
	float maxEnergy;
	int shotTime;
	int coolTime;
}PLAYER_DATA;

typedef struct {
	bool isLive;

}ENEMY_DATA;

class Map
{
public:
	Map();
	~Map() {};


	//��b
	void Init(D3DXVECTOR2* playerPos);
	void Uninit();
	void Update();
	void Update_Move();
	void Update_Shot();
	void Update_Play();
	void Draw();
	void Draw_Move();
	void Draw_Shot();
	void Draw_Play();

	bool GetCollider(D3DXVECTOR2* move);
	bool GetCollider(D3DXVECTOR2* pos, D3DXVECTOR2* move);

	//�⏕
	WIDE_POS	GetDrawWidePos(D3DXVECTOR2 pos);
	float		GetDrawHight(float y);
	float		GetDrawHight(int y);
	float		GetDrawAngle(float y);


	//�e����
	void		SetPlayerShot(D3DXVECTOR2 pos);

	void		SetEnemyShot(D3DXVECTOR2 pos);


private:
	WIDE_POS	GetMapDrawPos(int y);

	D3DXVECTOR2* m_PlayerPos;			//�v���C���[�̏ꏊ���擾���邽�߂ɕK�v�Ȃ���

	D3DXVECTOR2 m_CameraCentor;

	D3DXVECTOR2 mouse;

	char m_Map[MAP_SIZE][MAP_SIZE];
	float subX, subY;
	
	unsigned int m_MouseTex;

	unsigned int m_BGTex;

	const int PLAYER_BULLET = 10;
	const int ENEMY_BULLET = 20;
	BULLET* m_PlayerBullet;
	BULLET* m_EnemyBullet;

	PLAYER_DATA m_PlayerData;
	const int USE_ENERGY = 30;

	const int MAX_TIME = 1800;
	int m_Time;

	MODE m_Mode;

	int m_Score;

	//�萔
	
};