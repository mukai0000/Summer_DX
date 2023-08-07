#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include "main.h"
#include <stdint.h>			//uint8_t　用

//===========================================
//			列挙体
//===========================================

typedef enum {			//バフの種類
	BUFF_HEAL,
	BUFF_POISON,
	BUFF_SLEEP,
	BUFF_STUN,
	BUFF_MAX
}STATUS_BUFF;

//===========================================
//			構造体
//===========================================

typedef struct {
	uint8_t			lv;
	uint16_t		time;
}BUFF_DATA;

class Buff
{
public:
	bool virtual GetActiv() { return (m_Buff.lv > 0) ? true : false; };	//Buffアイコン表示用に使うかも 時間でアクティブをとるんじゃなくて、バフレベルでアクティブをとる　0=なし　１以上あり

	void virtual Start() = 0;		//終了処理 を記入	
	void virtual Update() = 0;		//効果を反映するのはここでやる予定
	void virtual End() = 0;			//時間の経過処理

protected:
	BUFF_DATA		m_Buff;
};

class Heal :public Buff {
public:
	Heal(BUFF_DATA bd) { m_Buff = bd; }
	Heal(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void Start()override { if (m_Buff.time <= 0)m_Buff.lv = 0; };
	void Update()override;
	void End()override { if (m_Buff.lv > 0)m_Buff.time--; };


};

class Poison :public Buff {
public:
	Poison(BUFF_DATA bd) { m_Buff = bd; }
	Poison(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void Start()override { if (m_Buff.time <= 0)m_Buff.lv = 0; };
	void Update()override;
	void End()override { if (m_Buff.lv > 0)m_Buff.time--; };


};

class Sleep :public Buff {
public:
	Sleep(BUFF_DATA bd) { m_Buff = bd; }
	Sleep(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void Start()override { if (m_Buff.time <= 0)m_Buff.lv = 0; };
	void Update()override;
	void End()override { if (m_Buff.lv > 0)m_Buff.time--; };


};

class Stun :public Buff {
public:
	Stun(BUFF_DATA bd) { m_Buff = bd; }
	Stun(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void Start()override { if (m_Buff.time <= 0)m_Buff.lv = 0; };
	void Update()override;
	void End()override { if (m_Buff.lv > 0)m_Buff.time--; };


};


#endif
