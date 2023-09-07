#pragma once
#include "main.h"


typedef enum {
	SCENE_TITLE,
	SCENE_GAME
}SCENE;

typedef enum {
	FADE_NONE,
	FADE_OUT,
	FADE_IN,
	FADE_STAY
}FADE;

void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();

void SetFade(SCENE next, D3DXVECTOR2 target);
void UpdateFade();
void DrawFade();
void SetTarget(D3DXVECTOR2 target);

void ChangeScene(SCENE next);