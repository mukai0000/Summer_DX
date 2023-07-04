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
//=======================================
//アイテム管理　Item.h
//武藤海人		2023/06/28
//=======================================


//
//アイテムに必要なものを宣言
//

typedef enum {
	ITEM_USE,
	ITEM_HELM,
	ITEM_BODY,
	ITEM_LEG,
	ITEM_COLLECT,
	ITEM_MAX
}ITEM_KIND;

typedef enum {
	ITEM_ID_NONE,
	ITEM_ID_POTION,
	ITEM_ID_MPPOTION,
	ITEM_ID_SWORD,
	ITEM_ID_HELM,
	ITEM_ID_ARMER,
	ITEM_ID_LEGARMER,

	ITEM_ID_MAX
}ITEM_ID;


class Item
{
public:
	Item(){}
	~Item(){}

	virtual void ItemUse() {};								//アイテムを使用した時の挙動を管理する関数

	string GetItemName() { return m_ItemName; }			//アイテムの名前を取得する
	string* GetItemName_P() { return &m_ItemName; }			//アイテムの名前のポインタ
	ITEM_KIND GetItemKind() { return m_ItemKind; }		//アイテムの種類を取得
	ITEM_KIND* GetItemKind_P() { return &m_ItemKind; }		//アイテムの種類のポインタ
	TEXTURE_DATA GetItemIcon() { return m_ItemTex; }
	TEXTURE_DATA* GetItemIcon_P() { return &m_ItemTex; }

protected:
	void SetItemName(string name) { m_ItemName = name; }
	
	void SetItemKind(ITEM_KIND kind) { m_ItemKind = kind; }

	void SetItemIcon(string filename, int w, int h, int a);

private:
	string m_ItemName;			//アイテムの表示名
	
	ITEM_KIND m_ItemKind;		//アイテムの種類	これによって使用した時の挙動を変えるつもり

	TEXTURE_DATA m_ItemTex;		//アイテムの画像
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
	MpPotion() {};
	~MpPotion() {};

public:
	void ItemUse()override {};
};
