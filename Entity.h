//================================
// Entity.h		Entity(�v���C���[��G�A�������U��
// �����@�C�l	2023/08/08
//================================

#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "main.h"
#include <stdint.h>

#include "Inventory.h"		//�C���x���g���[
#include "Buff.h"			//�o�t�f�o�t�A�����񕜂�ŁA�����܂ЂȂ�


//===========================================
//			�}�N����`
//===========================================


//===========================================
//			�񋓑�
//===========================================
typedef enum {			//�I�u�W�F�N�g�̎��
	KIND_PLAYER,
	KIND_ENEMY,
	KIND_BOSS,
	KIND_ITEM,
	KIND_OBJECT
}OBJECT_KIND_TAG;

typedef enum {			//�����蔻��̃��[�h
	MODE_CIRCLE,
	MODE_BOX,
	MODE_MAX
}COLLIDER_MODE;

//===========================================
//			�\����
//===========================================
typedef struct {				//�@�I�u�W�F�N�g�̏ꏊ�傫�����
	D3DXVECTOR2 pos;
	D3DXVECTOR2 oldPos;
	D3DXVECTOR2 size;
}ENTITY_TRANSFORM;

typedef struct {				//�@�X�e�[�^�X�@255������ɂ������Z
	uint8_t			lv;			//	���x���@	�\���̂ɂ��Ȃ��Ă���������
	uint8_t			pow;
	uint8_t			vit;
	uint8_t			mgc;
}ENTITY_POTENTIAL_STATUS;

typedef struct {					//�@�����X�e�[�^�X
	int				hp;			//	hp			vit�⑕���ɂ���ĕω�
	int				mp;			//�@mp			mgc�⑕���ɂ���ĕω�
	int				atk;		//�@�ߐڍU����	�ߐڍU����
	int				mat;		//�@���@�U����	�g��Ȃ�����
	int				def;		//	�h��́@�@�@�����ɂ���Ă̂ݕω��@�������X�^�[�Ƃ̃��x�����ł�����
}ENTITY_STATUS;

//===========================================
//			�N���X
//===========================================

class Status {
public:
	Status();
	~Status() {};

	//�Q�b�^�[
	ENTITY_POTENTIAL_STATUS*	GetBathStatus			()				{ return &m_BathStatus; }
	ENTITY_STATUS*				GetNowStatus			()				{ return &m_NowStatus; }
	ENTITY_STATUS*				GetStandardStatus		()				{ return &m_StandardStatus; }
	int*						GetStatusPoint			()				{ return &m_StatusPoint; }

	bool						GetIsDead				()				{ return (m_NowStatus.hp <= 0) ? true : false; }	//���S�������ǂ������擾

	//�Z�b�^�[

	//�Ăяo��			
	//�������
	void	AddLevel				();
	void	AddPow					();
	void	AddVit					();
	void	AddMgc					();
	//�����@�_���[�W�ɂ��g��
	void	AddHp					(int add);			//�����𑫂�����������肵�����Ɏg��
	void	AddMp					(int add);
	void	AddAtk					(int add);
	void	AddMat					(int add);
	void	AddDef					(int add);
	//�X�V���
	void	RisetNowStatus			()				{ m_NowStatus = m_StandardStatus; }
	void	UpdateStandardStatus	();	
	void	UpdateStandardStatus	(ENTITY_STATUS *addStatus);		//�����ɂ��X�e�[�^�X�̏㏸�l�������Ŏ󂯎��

private:
	ENTITY_POTENTIAL_STATUS m_BathStatus;			//���x���⃂���X�^�[�̎�ނɂ���ĕϓ�����X�e�[�^�X�̊�b�l

	ENTITY_STATUS			m_StandardStatus;		//��ɂȂ�X�e�[�^�X	HPMP�͍ő�l�@���x���⑕���ł̏㏸�ʂ����Z��������
	ENTITY_STATUS			m_NowStatus;			//�o�t�Ȃǂŏ㏸�������l�@���ʒl�@���ۂɎg���l

	int m_StatusPoint;								//��b�X�e�[�^�X�ɐG���|�C���g

	Buff* m_Buff;				
};

class Entity {			//���N���X
public:
	Entity();
	~Entity() {};

	bool	GetHitTrigger	(Entity* target ,COLLIDER_MODE mode);
	int		GetDamage		(int index);								//�_���[�W�ʂ��擾���邽�߂̊֐��A�����ōU���̎�ނ��擾����
	void	SetDamage		(int damage);
protected:
	float					m_CollisionSize;	//�~����p�̔��a
	ENTITY_TRANSFORM		m_Transform;		//���ݒn�A1�t���[���O�̏ꏊ�A�傫���A


	Status*					m_Status;						//�X�e�[�^�X�Ǘ��N���X
	//Inventory*				m_Inventory;					//�C���x���g�����
	Buff*					m_Buff[BUFF_MAX];				//��Ԉُ�@�o�t�f�o�t
};


#endif // !ENTITY_H

