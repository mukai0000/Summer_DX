//=============================================================================
//
// �v���C���[���� [sprite.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSprite();
void UninitSprite();

void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, float r, float g, float b, float a);
void DrawSpriteColorRotate(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, float r, float g, float b, float a, float Rot);
void DrawSpriteColorRotateAxis(int texNo, float X, float Y, float Width, float Height, float CX, float CY, float U, float V, float UW, float VH, float r, float g, float b, float a, float Rot);

//======================================
//			����
//======================================

void DrawBoxColor(D3DXVECTOR2* pos, D3DXVECTOR2* size, D3DXCOLOR color);
void DrawBoxColor_LTRB(D3DXVECTOR2* lt, D3DXVECTOR2* rb, D3DXCOLOR color);
void DrawBoxColor_TB_FOUR(float* top, float* bottom, float* lt, float* rt, float* lb, float* rb, D3DXCOLOR* color);

void DrawSprite(TEXTURE_DATA* tex, D3DXVECTOR2* pos, float* radius);
void DrawSprite(TEXTURE_DATA* tex, D3DXVECTOR2* pos, D3DXVECTOR2* size);

void DrawBox_LTRB(D3DXVECTOR2* lt, D3DXVECTOR2* rb, D3DXCOLOR* color);
void DrawBox_LTRB(D3DXVECTOR2 lt, D3DXVECTOR2 rb, D3DXCOLOR color);
