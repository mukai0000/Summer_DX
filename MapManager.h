#pragma once
//===========================================
// �}�b�v�Ǘ�	MapManager.h
//	�����C�l		2023/06/29
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
	//��b
	void InitMapManager(D3DXVECTOR2* playerPos);
	void UninitMapManager();
	void UpdateMapManager();
	void DrawMapManager();

	//�⏕
	void SetAddXMove(float x) { m_x += x; }
	void SetAddYMove(float y) { m_y += y; }

private:

	float m_x, m_y;						//�ǂꂾ�����炵�ĕ\�����邩���L�����镔��

	D3DXVECTOR2* m_PlayerPos;			//�v���C���[�̏ꏊ���擾���邽�߂ɕK�v�Ȃ���

	D3DXVECTOR2 sumple;

	int m_Map[MAP_SIZE][MAP_SIZE];
	float subX, subY;
		
};

