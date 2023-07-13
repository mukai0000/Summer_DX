#include "game.h"
#include "sprite.h"

#include "MapManager.h"

Map* mm;

void InitGame()
{
	mm = new Map;
}

void UninitGame()
{
}

void UpdateGame()
{
	mm->UpdateMapManager();
}

void DrawGame()
{
	mm->DrawMapManager();
}
