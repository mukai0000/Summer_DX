//=======================================
//UI�Ǘ��@		UI.h
//�����C�l		2023/06/28
//=======================================

#pragma once

#ifndef UI_H
#define UI_H

#include "main.h"
#include "input.h"
#include "Object.h"

//�C���x���g��
/*
�K�v�Ȃ���
�o�b�t�@�[		�}�E�X�ňړ�������Ƃ��Ɏg�����



*/

class UI
{
public:
	UI(ENTITY_POTENTIAL_STATUS* eps_P, ENTITY_STATUS* es_P);
	~UI();

	void SetPlayerStatus_P(ENTITY_POTENTIAL_STATUS* eps_P);
	void SetPlayerRealStatus_P(ENTITY_STATUS* es_P);

	void SetSwitchInventoryFlag();											//�C���x���g����\�����邩�ǂ����؂�ւ�����


	void Start();
	void Update();
	void End();

	void DrawUI();

private:
	bool m_IsInventory;		//UI��\�����邩�ǂ���

	ENTITY_POTENTIAL_STATUS* m_PlayerStatus;		//pow�Ƃ�vit
	ENTITY_STATUS* m_PlayerRealStatus;				//�����Ƃ��𑕔���������

};


#endif // !UI_H