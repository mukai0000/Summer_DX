//=============================================================================
//
// プレイヤー処理 [sprite.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitSprite();
void UninitSprite();

void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, float r, float g, float b, float a);
void DrawSpriteColorRotate(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, float r, float g, float b, float a, float Rot);
void DrawSpriteColorRotateAxis(int texNo, float X, float Y, float Width, float Height, float CX, float CY, float U, float V, float UW, float VH, float r, float g, float b, float a, float Rot);

//======================================
//			自作
//======================================

void DrawBoxColor(D3DXVECTOR2* pos, D3DXVECTOR2* size, D3DXCOLOR color);
void DrawBoxColor_LTRB(D3DXVECTOR2* lt, D3DXVECTOR2* rb, D3DXCOLOR color);
void DrawBoxColor_TB_FOUR(float* top, float* bottom, float* lt, float* rt, float* lb, float* rb, D3DXCOLOR* color);

void DrawSprite(TEXTURE_DATA* tex, D3DXVECTOR2* pos, float* radius);
void DrawSprite(TEXTURE_DATA* tex, D3DXVECTOR2* pos, D3DXVECTOR2* size);
void DrawSprite_LT(TEXTURE_DATA* tex, D3DXVECTOR2* pos, D3DXVECTOR2* size,D3DXVECTOR4 *uv);
void DrawSprite_TB_FOUR(TEXTURE_DATA* tex,float* top, float* bottom, float* lt, float* rt, float* lb, float* rb);

void DrawBox_LTRB(D3DXVECTOR2* lt, D3DXVECTOR2* rb, D3DXCOLOR* color);
void DrawBox_LTRB(D3DXVECTOR2 lt, D3DXVECTOR2 rb, D3DXCOLOR color);

void DrawNumberSumple(D3DXVECTOR2 pos, D3DXVECTOR2 size, int target);
//void DrawAnimation(TEXTURE_DATA *tex, D3DXVECTOR2 *pos, D3DXVECTOR2 *size, int *target);
//void DrawAnimation(TEXTURE_DATA *tex, D3DXVECTOR2 *pos, D3DXVECTOR2 *size, D3DXCOLOR col,int *target);
//void DrawAnimation_LT(TEXTURE_DATA *tex, D3DXVECTOR2 *pos, D3DXVECTOR2 *size, int *target);
void DrawAnimation_LT(TEXTURE_DATA *tex, D3DXVECTOR2 *pos, D3DXVECTOR2 *size, D3DXCOLOR col,int target);
//void DrawAnimation_LT(TEXTURE_DATA *tex, D3DXVECTOR2 *pos1, D3DXVECTOR2 *pos2, D3DXVECTOR2 *pos3, D3DXVECTOR2 *pos4, D3DXCOLOR col,int target);


