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
	void SetAddXMove(float x) { move.x += x; }			//これは描画に必要なやつ
	void SetAddYMove(float y) { move.y += y; }


private:

	D3DXVECTOR2* m_PlayerPos;			//プレイヤーの場所を取得するために必要なもの

	D3DXVECTOR2 sumple;

	D3DXVECTOR2 move;					//動いた時の座標をそのまま使うと反転しちゃうから　動いた場合と描画の場合を切り離す

	D3DXVECTOR2 mouse;

	char m_Map[MAP_SIZE][MAP_SIZE];
	float subX, subY;
	
	unsigned int m_MouseTex;

	unsigned int m_BGTex;

	bool isMouse;
};

