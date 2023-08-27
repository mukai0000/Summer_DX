#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "main.h"
#include "Item.h"

//============================
//			��
//============================

//============================
//			�\����
//============================

typedef struct {
	uint8_t	itemID;
	uint8_t	itemNum;
}INVENTORY_DATA;

//============================
//			�N���X
//============================

//�C���x���g��
/*
�K�v�Ȃ���
�o�b�t�@�[		�}�E�X�ňړ�������Ƃ��Ɏg�����

�C���x���g���p�̗e�ʁA
�A�C�e���X���b�g�̗e��

�A�C�e���X���b�g�̑I��Ώ�
�A�C�e���X���b�g�̃}�E�X�R���R��
�A�C�e���X���b�g�̃i���o�[�I��

���������邩��
*/

class Inventory
{
public:
	Inventory() {};
	~Inventory() {};

	//////////////
	// �Q�b�^�[ //
	//////////////

	uint8_t	GetUseItemID();			//�A�C�e���g�p����{�^���������炱����Ăяo��

	uint8_t GetSarchSlotNum(uint8_t targetID) {};	//������ID�̃A�C�e�����ǂ��ɂ��邩���擾����
	uint8_t GetSarchItemId(uint8_t targetPos) {};	//�����̃X���b�g�ԍ��̃A�C�e��ID���擾����		UI�\���Ɏg��
	
	//////////////
	// �Z�b�^�[ //
	//////////////
	void SetNewItem(INVENTORY_DATA id);		//�A�C�e�����E�����蔃�����炱��Ăяo���A

	void SetAddSlotVal(int addVal);
	void SetSlotNum(int num);
	
	//void Start();
	//void Update();
	void End();

private:

	const uint8_t		INV_MAX = 20;
	const uint8_t		SLOT_MAX = 4;
	const uint8_t		SOUBI_MAX = 4;		//�����@���������@��4��

	INVENTORY_DATA*		m_InvItem = new INVENTORY_DATA[INV_MAX];
	INVENTORY_DATA*		m_SlotItem=new INVENTORY_DATA[SLOT_MAX];
	INVENTORY_DATA*		m_SoubiItem=new INVENTORY_DATA[SOUBI_MAX];

	uint8_t				m_Select = 1;
};

#endif

