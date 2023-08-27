#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include "main.h"
#include <stdint.h>			//uint8_t�@�p

//===========================================
//			�񋓑�
//===========================================

typedef enum {			//�o�t�̎��
	BUFF_REGENE,
	BUFF_POISON,
	BUFF_SLEEP,
	BUFF_STUN,
	BUFF_MAX
}STATUS_BUFF;

//===========================================
//			�\����
//===========================================

typedef struct {
	uint8_t			lv;
	uint16_t		time;
}BUFF_DATA;

class Buff
{
public:
	//���z�֐�
	bool virtual GetActiv() { return (m_Buff.lv > 0) ? true : false; };	//Buff�A�C�R���\���p�Ɏg������ ���ԂŃA�N�e�B�u���Ƃ�񂶂�Ȃ��āA�o�t���x���ŃA�N�e�B�u���Ƃ�@0=�Ȃ��@�P�ȏ゠��
	void virtual SetActiv(BUFF_DATA bd) { m_Buff = bd; }
	void virtual SetActiv(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void virtual Start() = 0;		//�I������ ���L��	
	void virtual Update() = 0;		//���ʂ𔽉f����̂͂����ł��\��
	void virtual End() = 0;			//���Ԃ̌o�ߏ���

	//�֐�
	bool GetFlag() { return m_IsFlag; }	//Update����ɌĂяo��		�G�t�F�N�g�p���Ȃ�

protected:
	BUFF_DATA		m_Buff;

	bool m_IsFlag;	//Update��On�ɂ���Start��Off�ɂ���
};

class Regene :public Buff {
public:
	Regene() {};
	Regene(BUFF_DATA bd) { m_Buff = bd; }
	Regene(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void Start()override { if (m_Buff.time <= 0)m_Buff.lv = 0; };
	void Update()override {};
	void End()override { if (m_Buff.lv > 0)m_Buff.time--; };


};

class Poison :public Buff {
public:
	Poison() {}
	Poison(BUFF_DATA bd) { m_Buff = bd; }
	Poison(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void Start()override { if (m_Buff.time <= 0)m_Buff.lv = 0; };
	void Update()override {};
	void End()override { if (m_Buff.lv > 0)m_Buff.time--; };


};

/*
6�C�Ɂ@2�l
���ȏ������ɏo���Ă��邩�m�F
����`������

��w�N
�@�X�N���b�`�@Unity Iphone

	�����@�����̌��ʎ���
	
	C++ 

	�Z�p�e�X�g�̌㐳���̗p
	*/

class SLEEP :public Buff {
public:
	SLEEP() {};
	SLEEP(BUFF_DATA bd) { m_Buff = bd; }
	SLEEP(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void Start()override { if (m_Buff.time <= 0)m_Buff.lv = 0; };
	void Update()override {};
	void End()override { if (m_Buff.lv > 0)m_Buff.time--; };


};

class Stun :public Buff {
public:
	Stun() { }
	Stun(BUFF_DATA bd) { m_Buff = bd; }
	Stun(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void Start()override { if (m_Buff.time <= 0)m_Buff.lv = 0; };
	void Update()override {};
	void End()override { if (m_Buff.lv > 0)m_Buff.time--; };


};


#endif
