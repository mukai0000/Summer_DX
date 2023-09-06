#include "UI.h"
#include "sprite.h"


UI::UI(string texName, int w, int h, int a, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, bool act, float num)
{
	m_Data.tex = SetTexture(texName, w, h, a);
	m_Data.active = act;
	m_Data.pos = pos;
	m_Data.col = col;
	m_Data.size = size;
	m_Data.num = num;
}



void UI_Manager::SetSwitchInventoryFlag()
{
	m_IsInventory = !m_IsInventory;
}

GageBar::GageBar(string texName, int w, int h, int a, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, bool act, float num, FILL_VEC vec) :UI(texName, w, h, a, pos, size, col, act, num)
{
	m_Data = SetUI_DATA(texName, w, h, a, pos, size, col, act, num);
	m_Fill = vec;
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
	D3DXVECTOR2 p = m_Data.pos;
	D3DXVECTOR2 s = m_Data.size;
	D3DXVECTOR4 uv = { 0.0f,0.0f, 1.0f,1.0f };
	if (m_Data.active)
	{
		switch (m_Fill) {
		case FILL_VEC::FILL_DOWN:

			break;

		case FILL_VEC::FILL_UP:
			uv.y = 1 - m_Data.num;
			uv.w = m_Data.num;
			p.y += s.y * uv.y;
			s.y *= m_Data.num;

			DrawSprite_LT(&m_Data.tex, &p, &s, &uv);
			break;

		case FILL_VEC::FILL_LEFT:

			break;

		case FILL_VEC::FILL_RIGHT:
			uv.z = m_Data.num;
			s.x *= m_Data.num;

			DrawSprite_LT(&m_Data.tex, &p, &s, &uv);
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
	else {

	}
}

UI_DATA SetUI_DATA(string texName, int w, int h, int a, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, bool act, float num)
{
	UI_DATA ret;
	ret.tex = SetTexture(texName, w, h, a);
	ret.pos = pos;
	ret.size = size;
	ret.col = col;
	ret.active = act;
	ret.num = num;
	return ret;
}
