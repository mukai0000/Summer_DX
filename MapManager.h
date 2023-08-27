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

	bool GetCollider(D3DXVECTOR2* move);
	bool GetCollider(D3DXVECTOR2* pos, D3DXVECTOR2* move);

	//�⏕
	WIDE_POS	GetDrawWidePos(D3DXVECTOR2 pos);
	float		GetDrawHight(float y);
	float		GetDrawHight(int y);
	float		GetDrawAngle(float y);


private:

	D3DXVECTOR2* m_PlayerPos;			//�v���C���[�̏ꏊ���擾���邽�߂ɕK�v�Ȃ���

	D3DXVECTOR2 m_CameraCentor;

	D3DXVECTOR2 mouse;

	char m_Map[MAP_SIZE][MAP_SIZE];
	float subX, subY;
	
	unsigned int m_MouseTex;

	unsigned int m_BGTex;

	bool isMouse;
};

