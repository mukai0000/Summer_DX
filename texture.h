#pragma once


#include "renderer.h"

#include "string"

//================================
//テクスチャー管理
//武藤海人		2023/06/28
//================================

typedef struct {
	unsigned int texCord;
	int wide;
	int hight;
	int maxAnim;
}TEXTURE_DATA;



int LoadTexture(char* fileName);
void UninitTexture(void);

ID3D11ShaderResourceView** GetTexture(int index);

TEXTURE_DATA SetTexture(std::string fileName, int w, int h, int a);