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
		if (m_SlotItem[i].itemID == id.itemID) {		//Žæ“¾‚µ‚½ƒAƒCƒeƒ€‚Æ“¯‚¶‚à‚Ì‚ª“ü‚Á‚Ä‚¢‚½‚ç
			target = i;
		}
	}
	for (int i = 0; i < INV_MAX; i++) {

	}
}

void Inventory::SetAddSlotVal(int addVal)
{
	m_Select += addVal;
	if (m_Select < 0)m_Select += SLOT_MAX;				//¬‚³‰ß‚¬‚½‚ç
	else if (m_Select >= SLOT_MAX)m_Select -= SLOT_MAX;	//‘å‚«‚·‚¬‚½‚ç
}

void Inventory::SetSlotNum(int num)
{
	if (num >= 1 && num <= SLOT_MAX)m_Select = num - 1;	//num‚ª1`5‚ÌŠÔ‚¾‚Á‚½‚çnum-1‚µ‚½”Žš‚ðSelect‚É“ü‚ê‚é
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
