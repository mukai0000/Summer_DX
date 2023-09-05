#include "UI.h"


UI::UI(string texName, int w, int h, int a, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, bool act)
{
	m_Data.tex = SetTexture(texName, w, h, a);
	m_Data.active = act;
	m_Data.pos = pos;
	m_Data.col = col;
	m_Data.size = size;
}



void UI_Manager::SetSwitchInventoryFlag()
{
	m_IsInventory = !m_IsInventory; 
}

void GageBar::SetNumber(float n)
{
	m_IsUpdate = (n != m_Data.num);			//ˆø”‚ÅŽó‚¯Žæ‚Á‚½num‚ª‚à‚Æ‚à‚ÆŽ‚Á‚Ä‚¢‚½num‚Æˆá‚Á‚½‚çm_IsUpdate‚Ítrue@“¯‚¶‚¾‚Á‚½‚çfalse
	m_Data.num = n;
}

void GageBar::Update()
{
	if (m_IsUpdate)
	{
		switch (m_Fill) {
		case FILL_VEC::FILL_DOWN:

			break;

		case FILL_VEC::FILL_UP:
			m_Sub = m_Data.size * (1.0f - m_Data.num);
			break;

		case FILL_VEC::FILL_LEFT:

			break;

		case FILL_VEC::FILL_RIGHT:
			m_Sub = m_Data.size * m_Data.num;
			break;
		}
	}
}

void GageBar::Draw()
{
	if (m_IsUpdate)
	{
		switch (m_Fill) {
		case FILL_VEC::FILL_DOWN:

			break;

		case FILL_VEC::FILL_UP:
			m_Sub = m_Data.size * (1.0f - m_Data.num);
			break;

		case FILL_VEC::FILL_LEFT:

			break;

		case FILL_VEC::FILL_RIGHT:
			m_Sub = m_Data.size * m_Data.num;
			break;
		}
	}
}

void Button::Update()
{
	D3DXVECTOR2 mouse = GetMousePosition();

	//‚©[‚»‚é‚ª“–‚½‚Á‚Ä‚é‚©‚Ç‚¤‚©‚Ìî•ñ
	m_IsHit =
		(
		mouse.x >= m_Data.pos.x && mouse.x <= m_Data.pos.x + m_Data.size.x &&
		mouse.y >= m_Data.pos.y && mouse.y <= m_Data.pos.y + m_Data.size.y
		);
}

void Button::Draw()
{
	if (m_IsHit) {

	}
	else{

	}
}
