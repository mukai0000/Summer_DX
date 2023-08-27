#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "main.h"
#include "Item.h"

//============================
//			列挙
//============================

//============================
//			構造体
//============================

typedef struct {
	uint8_t	itemID;
	uint8_t	itemNum;
}INVENTORY_DATA;

//============================
//			クラス
//============================

//インベントリ
/*
必要なもの
バッファー		マウスで移動させるときに使うやつ

インベントリ用の容量、
アイテムスロットの容量

アイテムスロットの選択対象
アイテムスロットのマウスコロコロ
アイテムスロットのナンバー選択

お金もいるかも
*/

class Inventory
{
public:
	Inventory() {};
	~Inventory() {};

	//////////////
	// ゲッター //
	//////////////

	uint8_t	GetUseItemID();			//アイテム使用するボタン押したらこれを呼び出す

	uint8_t GetSarchSlotNum(uint8_t targetID) {};	//引数のIDのアイテムがどこにあるかを取得する
	uint8_t GetSarchItemId(uint8_t targetPos) {};	//引数のスロット番号のアイテムIDを取得する		UI表示に使う
	
	//////////////
	// セッター //
	//////////////
	void SetNewItem(INVENTORY_DATA id);		//アイテムを拾ったり買ったらこれ呼び出す、

	void SetAddSlotVal(int addVal);
	void SetSlotNum(int num);
	
	//void Start();
	//void Update();
	void End();

private:

	const uint8_t		INV_MAX = 20;
	const uint8_t		SLOT_MAX = 4;
	const uint8_t		SOUBI_MAX = 4;		//装備　頭胴足武　の4つ

	INVENTORY_DATA*		m_InvItem = new INVENTORY_DATA[INV_MAX];
	INVENTORY_DATA*		m_SlotItem=new INVENTORY_DATA[SLOT_MAX];
	INVENTORY_DATA*		m_SoubiItem=new INVENTORY_DATA[SOUBI_MAX];

	uint8_t				m_Select = 1;
};

#endif

