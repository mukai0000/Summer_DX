#include "game.h"
#include "sprite.h"

#include "MapManager.h"
#include "UI.h"

Map* mm;

GageBar* g;
GageBar* g2;

float n = 0.0f;
bool up = true;

void InitGame()
{
	mm = new Map;
	UI_DATA ud = SetUI_DATA("data/exp_96x96.png", 1, 1, 1, D3DXVECTOR2(100, 100), D3DXVECTOR2(192, 192), D3DXCOLOR(1, 1, 1, 1), true,1.0f);
	g = new GageBar(ud, FILL_VEC::FILL_UP);

}

void UninitGame()
{
}

void UpdateGame()
{
	mm->UpdateMapManager();
	(up) ? n++ : n--;
	if (n <= 0 || n >= 100)up = !up;
	g->SetNumber(n / 100);
}

void DrawGame()
{
	mm->DrawMapManager();
	g->Draw();
}
