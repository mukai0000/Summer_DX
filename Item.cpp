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
	SetItemName("ポーション");

}

ItemDataBath::ItemDataBath()
{
	//↓これは無理。Item型のポインタにItem型の子クラスは宣言できるけど
	//	Item型でnewしちゃうとItem型に固定されてしまって無理
	//Item* m_ItemDataList;
	//m_ItemDataList = new Item[ITEM_ID_MAX];
	//m_ItemDataList[ITEM_ID_POTION] = new Potion();

	m_ItemDataList[ITEM_ID_POTION] = new Potion();
}
