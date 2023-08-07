//=======================================
//アイテム管理　Item.h
//武藤海人		2023/06/28
//=======================================


#pragma once

#ifndef STRING_INCLUDE
#define STRING_INCLUDE
#include <string>
#endif // !STRING_INCLUDE

#ifndef TEXTURE_H
#define TEXTURE_H
#include "texture.h"
#endif // !TEXTURE_H

using namespace std;

//
//アイテムに必要なものを宣言
//

typedef enum {		//アイテムの種類
	ITEM_USE,		//使用すると減るアイテム
	ITEM_WEAPONE,	//武器
	ITEM_HELM,		//頭装備
	ITEM_BODY,		//胴装備
	ITEM_LEG,		//足装備
	ITEM_COLLECT,	//取集品？
	ITEM_MAX		//最大数　
}ITEM_KIND;

typedef enum {
	ITEM_ID_NONE,
	ITEM_ID_POTION,
	ITEM_ID_MPPOTION,
	ITEM_ID_SWORD_WOOD,
	ITEM_ID_HELM_LEATHER,
	ITEM_ID_ARMER_LEATHER,
	ITEM_ID_LEGARMER_LEATHER,

	ITEM_ID_MAX
}ITEM_ID;


class Item		//アイテムの基底クラス
{
public:
	Item(uint8_t stackMax):m_ItemStackMax(stackMax){}
	~Item(){}

	virtual void	ItemUse			()	{};							//アイテムを使用した時の挙動を管理する関数

	string			GetItemName		()	{ return m_ItemName; }		//アイテムの名前を取得する
	string*			GetItemName_P	()	{ return &m_ItemName; }		//アイテムの名前のポインタ
	ITEM_KIND		GetItemKind		()	{ return m_ItemKind; }		//アイテムの種類を取得
	ITEM_KIND*		GetItemKind_P	()	{ return &m_ItemKind; }		//アイテムの種類のポインタ
	TEXTURE_DATA	GetItemIcon		()	{ return m_ItemTex; }
	TEXTURE_DATA*	GetItemIcon_P	()	{ return &m_ItemTex; }

	uint8_t			GetItemMax		()	{ return m_ItemStackMax; }

protected:
	void			SetItemName		(string name)		{ m_ItemName = name; }
		
	void			SetItemKind		(ITEM_KIND kind)	{ m_ItemKind = kind; }

	void			SetItemIcon		(string filename, int w, int h, int a);

	string			m_ItemName;		//アイテムの表示名
	
	ITEM_KIND		m_ItemKind;		//アイテムの種類	これによって使用した時の挙動を変えるつもり

	TEXTURE_DATA	m_ItemTex;		//アイテムの画像

	const uint8_t	m_ItemStackMax;
};

class ItemDataBath {
public:

	ItemDataBath();
	~ItemDataBath() {};

	Item* GetItemDataList_P() { return *m_ItemDataList; }
	
	//↓これで動くかまだ分からない
	void UseItemData(int index) { return m_ItemDataList[index]->ItemUse(); }

	TEXTURE_DATA* GetItemIconData(int index) { return m_ItemDataList[index]->GetItemIcon_P(); }

	ITEM_KIND* GetItemIconKind(int index) { return m_ItemDataList[index]->GetItemKind_P(); }

private:
	Item* m_ItemDataList[ITEM_ID_MAX];

};

class Potion :public Item {
public:
	Potion();
	~Potion() {};

public:
	void ItemUse()override {};
};

class MpPotion :public Item {
public:
	MpPotion() :Item(10){}
	~MpPotion() {};

public:
	void ItemUse()override {};
};
