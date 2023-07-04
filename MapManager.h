#pragma once
//===========================================
// マップ管理	MapManager.h
//	武藤海人		2023/06/29
//===========================================

#ifndef MAIN_H
#define MAIN_H
#include "main.h"
#endif // !MAIN_H

#define MAP_SIZE (100)

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

	//補助
	void SetAddXMove(float x) { m_x += x; }
	void SetAddYMove(float y) { m_y += y; }

private:

	float m_x, m_y;						//どれだけずらして表示するかを記憶する部分

	D3DXVECTOR2* m_PlayerPos;			//プレイヤーの場所を取得するために必要なもの

	D3DXVECTOR2 sumple;

	int m_Map[MAP_SIZE][MAP_SIZE];
	float subX, subY;
		
};

