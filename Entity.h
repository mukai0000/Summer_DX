//===========================================
// Entity�Ǘ�		Entity.h
//	�����C�l		2023/07/19
//===========================================

#pragma once
#ifndef ENTITY_H		//�C���N���[�h�K�[�h
#define ENTITY_H

#include <string>

typedef enum {
	ENTITY_NORMAL,
	ENTITY_DAMAGE
}ENTITY_STATE;

typedef struct {			//255������ɂ������Z
	uint8_t			pow;
	uint8_t			vit;
	uint8_t			mgc;
}ENTITY_POTENTIAL_STATUS;

typedef struct{
	uint8_t			lv;			//	���x���@	�\���̂ɂ��Ȃ��Ă���������
	int				hp;			//	hp			vit�⑕���ɂ���ĕω�
	int				mp;			//�@mp			mgc�⑕���ɂ���ĕω�
	int				atk;		//�@�ߐڍU����	�ߐڍU����
	int				mat;		//�@���@�U����	�g��Ȃ�����
	int				def;		//	�h��́@�@�@�����ɂ���Ă̂ݕω��@�������X�^�[�Ƃ̃��x�����ł�����
}ENTITY_STATUS;


using namespace std;
class Entity
{
public:
	Entity();
	~Entity();



private:
};

#endif // !



