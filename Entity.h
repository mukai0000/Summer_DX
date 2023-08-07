//================================
// Entity.h		Entity(�v���C���[��G�A�������U��
// �����@�C�l	2023/08/07
//================================

#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "main.h"
#include <stdint.h>

#include "Inventory.h"		//�C���x���g���[
#include "Buff.h"			//�o�t�f�o�t�A�����񕜂�ŁA�����܂ЂȂ�

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

class Entity {			//���N���X
public:
	Entity();
	~Entity();

	bool GetHitTrigger(Entity* target);

private:
	float					m_CollisionSize;	//�~����p�̔��a
	ENTITY_TRANSFORM		m_Transform;		//���ݒn�A1�t���[���O�̏ꏊ�A�傫���A

	ENTITY_POTENTIAL_STATUS m_BathStatus;		//���x���⃂���X�^�[�̎�ނɂ���ĕϓ�����X�e�[�^�X�̊�b�l
	ENTITY_STATUS			m_MainStatus;		//���ۂɍs����X�e�[�^�X�ɔ��f�����ŏI�l�i����)
	ENTITY_STATUS			m_SubStatus;		//�����Ȃǂɂ���ĕς�鐔�l�A��������Ȃ�

	Inventory*				m_Inventory;		//�C���x���g�����
	Buff*					m_Buff;				//��Ԉُ�@�o�t�f�o�t
};


#endif // !ENTITY_H

