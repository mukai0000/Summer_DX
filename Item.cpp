#include "Item.h"

void Item::SetItemIcon(string filename, int w, int h, int a)
{
	m_ItemTex.texCord = LoadTexture((char*)filename.c_str());
	m_ItemTex.wide = w;
	m_ItemTex.hight = h;
	m_ItemTex.maxAnim = a;
}

Potion::Potion()
{
	SetItemName("�|�[�V����");

}

ItemDataBath::ItemDataBath()
{
	//������͖����BItem�^�̃|�C���^��Item�^�̎q�N���X�͐錾�ł��邯��
	//	Item�^��new�����Ⴄ��Item�^�ɌŒ肳��Ă��܂��Ė���
	//Item* m_ItemDataList;
	//m_ItemDataList = new Item[ITEM_ID_MAX];
	//m_ItemDataList[ITEM_ID_POTION] = new Potion();

	m_ItemDataList[ITEM_ID_POTION] = new Potion();
}
