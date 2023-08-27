#pragma once
//===========================================
// マップ管理	MapManager.h
//	武藤海人		2023/06/29
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

class Map
{
public:
	Map();
	~Map();


	//基礎
	void InitMapManager(D3DXVECTOR2* playerPos);
	void UninitMapManager();
	void UpdateMapManager();
	void DrawMapManager();

	bool GetCollider(D3DXVECTOR2* move);
	bool GetCollider(D3DXVECTOR2* pos, D3DXVECTOR2* move);

	//補助
	WIDE_POS	GetDrawWidePos(D3DXVECTOR2 pos);
	float		GetDrawHight(float y);
	float		GetDrawHight(int y);
	float		GetDrawAngle(float y);


private:

	D3DXVECTOR2* m_PlayerPos;			//プレイヤーの場所を取得するために必要なもの

	D3DXVECTOR2 m_CameraCentor;

	D3DXVECTOR2 mouse;

	char m_Map[MAP_SIZE][MAP_SIZE];
	float subX, subY;
	
	unsigned int m_MouseTex;

	unsigned int m_BGTex;

	bool isMouse;
};

