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
	void SetAddXMove(float x) { move.x += x; }			//����͕`��ɕK�v�Ȃ��
	void SetAddYMove(float y) { move.y += y; }


private:

	D3DXVECTOR2* m_PlayerPos;			//�v���C���[�̏ꏊ���擾���邽�߂ɕK�v�Ȃ���

	D3DXVECTOR2 sumple;

	D3DXVECTOR2 move;					//���������̍��W�����̂܂܎g���Ɣ��]�����Ⴄ����@�������ꍇ�ƕ`��̏ꍇ��؂藣��

	D3DXVECTOR2 mouse;

	char m_Map[MAP_SIZE][MAP_SIZE];
	float subX, subY;
	
	unsigned int m_MouseTex;

	unsigned int m_BGTex;

	bool isMouse;
};

