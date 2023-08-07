//===========================================
// Object�Ǘ�		Object.h
//	�����C�l		2023/07/19
//===========================================

#pragma once
#ifndef OBJECT_H		//�C���N���[�h�K�[�h
#define OBJECT_H

#include <string>
#include "main.h"


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

//===========================================
//			�\����
//===========================================
typedef struct {				//�@�I�u�W�F�N�g�̏ꏊ�傫�����
	D3DXVECTOR2 pos;
	D3DXVECTOR2 oldPos;
	D3DXVECTOR2 size;
}ENTITY_TRANSFORM;

typedef struct {				//�@�X�e�[�^�X�@255������ɂ������Z
	uint8_t			pow;
	uint8_t			vit;
	uint8_t			mgc;
}ENTITY_POTENTIAL_STATUS;

typedef struct{					//�@�����X�e�[�^�X
	uint8_t			lv;			//	���x���@	�\���̂ɂ��Ȃ��Ă���������
	int				hp;			//	hp			vit�⑕���ɂ���ĕω�
	int				mp;			//�@mp			mgc�⑕���ɂ���ĕω�
	int				atk;		//�@�ߐڍU����	�ߐڍU����
	int				mat;		//�@���@�U����	�g��Ȃ�����
	int				def;		//	�h��́@�@�@�����ɂ���Ă̂ݕω��@�������X�^�[�Ƃ̃��x�����ł�����
}ENTITY_STATUS;

using namespace std;

class Object		//���N���X		Object�}�l�[�W���[�N���X������Ĕz��ŊǗ�����B
{
public:
	Object();
	~Object();

	D3DXVECTOR2*	GetPosition		()							{ return &m_Trans.pos; }
	D3DXVECTOR2*	GetSize			()							{ return &m_Trans.size; }
	
	//�R�c�`�悷�邽�߂Ƀv���C���[����̋����A�x������Ƃ�����
	float* GetPositionY() { return &GetPosition()->y; }


	void			SetPosition(D3DXVECTOR2 pos) { m_Trans.pos = pos; }
	void			SetSize(D3DXVECTOR2 size) { m_Trans.size = size; }

protected:
	OBJECT_KIND_TAG m_ObjTag;

	ENTITY_TRANSFORM m_Trans;
};

class FieldObj :public Object{
public:
	FieldObj();
	~FieldObj();

};

class Entity :public Object {
public:
	Entity();
	~Entity();

	bool GetHitTrigger(Entity* target);

private:

	float m_CollisionSize;

};

#endif // !



