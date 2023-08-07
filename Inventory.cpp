#include "Inventory.h"

uint8_t Inventory::GetUseItemID()
{
	if (m_SlotItem[m_Select].itemID > 0) {
		m_SlotItem[m_Select].itemID--;
		return m_SlotItem[m_Select].itemID;
	}
}

void Inventory::SetNewItem(INVENTORY_DATA id)
{
	int target = -1;
	for (int i = 0; i < SLOT_MAX; i++) {
		if (m_SlotItem[i].itemID == id.itemID) {		//�擾�����A�C�e���Ɠ������̂������Ă�����
			target = i;
		}
	}
	for (int i = 0; i < INV_MAX; i++) {

	}
}

void Inventory::SetAddSlotVal(int addVal)
{
	m_Select += addVal;
	if (m_Select < 0)m_Select += SLOT_MAX;				//�����߂�����
	else if (m_Select >= SLOT_MAX)m_Select -= SLOT_MAX;	//�傫��������
}

void Inventory::SetSlotNum(int num)
{
	if (num >= 1 && num <= SLOT_MAX)m_Select = num - 1;	//num��1�`5�̊Ԃ�������num-1����������Select�ɓ����
}

void Inventory::End()
{
	for (int i = 0; i < INV_MAX; i++) {
		if (m_InvItem[i].itemNum <= 0)m_InvItem[i].itemID = 0;
	}
	for (int i = 0; i < SLOT_MAX; i++) {
		if (m_SlotItem[i].itemNum <= 0)m_SlotItem[i].itemID = 0;
	}
}
