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
//�A�C�e���Ǘ��@Item.h
//�����C�l		2023/06/28
//=======================================


//
//�A�C�e���ɕK�v�Ȃ��̂�錾
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

	virtual void ItemUse() {};								//�A�C�e�����g�p�������̋������Ǘ�����֐�

	string GetItemName() { return m_ItemName; }			//�A�C�e���̖��O���擾����
	string* GetItemName_P() { return &m_ItemName; }			//�A�C�e���̖��O�̃|�C���^
	ITEM_KIND GetItemKind() { return m_ItemKind; }		//�A�C�e���̎�ނ��擾
	ITEM_KIND* GetItemKind_P() { return &m_ItemKind; }		//�A�C�e���̎�ނ̃|�C���^
	TEXTURE_DATA GetItemIcon() { return m_ItemTex; }
	TEXTURE_DATA* GetItemIcon_P() { return &m_ItemTex; }

protected:
	void SetItemName(string name) { m_ItemName = name; }
	
	void SetItemKind(ITEM_KIND kind) { m_ItemKind = kind; }

	void SetItemIcon(string filename, int w, int h, int a);

private:
	string m_ItemName;			//�A�C�e���̕\����
	
	ITEM_KIND m_ItemKind;		//�A�C�e���̎��	����ɂ���Ďg�p�������̋�����ς������

	TEXTURE_DATA m_ItemTex;		//�A�C�e���̉摜
};

class ItemDataBath {
public:
	ItemDataBath();
	~ItemDataBath() {};

	Item* GetItemDataList_P() { return *m_ItemDataList; }
	
	//������œ������܂�������Ȃ�
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
