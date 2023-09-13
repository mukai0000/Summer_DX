#include "Title.h"
#include "sprite.h"
#include "game.h"

Title::Title()
{
	UI_DATA ud = SetUI_DATA("data/TEXTURE/Button.png", 1, 1, 1,
		D3DXVECTOR2(SCREEN_WIDTH * 0.375f, SCREEN_HEIGHT * 0.6f), D3DXVECTOR2(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.2f)
		, D3DXCOLOR(1, 1, 1, 1), true, 1);
	m_Button = new Button(ud);
	m_String = new MyString("Tuch");

	m_BG = SetTexture("data/Title.png", 1, 1, 1);
}

void Title::Update()
{
	m_Button->Update();

	if (m_Button->GetClick())SetFade(SCENE_GAME, GetMousePosition());
}

void Title::Draw()
{
	DrawSpriteLeftTop(m_BG.texCord, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);
	m_Button->Draw();
	m_String->DrawString(D3DXVECTOR2(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.65f),
		D3DXVECTOR2(100, 100),
		D3DXCOLOR(0.5f, 0.5f, 0.5f, 1));
}
