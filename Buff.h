#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include "main.h"
#include <stdint.h>			//uint8_t　用

//===========================================
//			列挙体
//===========================================

typedef enum {			//バフの種類
	BUFF_REGENE,
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
	//仮想関数
	bool virtual GetActiv() { return (m_Buff.lv > 0) ? true : false; };	//Buffアイコン表示用に使うかも 時間でアクティブをとるんじゃなくて、バフレベルでアクティブをとる　0=なし　１以上あり
	void virtual SetActiv(BUFF_DATA bd) { m_Buff = bd; }
	void virtual SetActiv(uint8_t lv, uint8_t time) { m_Buff = { lv,time }; }

	void virtual Start() = 0;		//終了処理 を記入	
	void virtual Update() = 0;		//効果を反映するのはここでやる予定
	void virtual End() = 0;			//時間の経過処理

	//関数
	bool GetFlag() { return m_IsFlag; }	//Updateより後に呼び出す		エフェクト用かなぁ

protected:
	BUFF_DATA		m_Buff;

	bool m_IsFlag;	//UpdateでOnにしてStartでOffにする
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
6任に　2人
教科書道理に出来ているか確認
お手伝いさん

低学年
　スクラッチ　Unity Iphone

	昇給　試験の結果次第
	
	C++ 

	技術テストの後正式採用
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
