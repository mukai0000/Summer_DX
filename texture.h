#pragma once


#include "renderer.h"

#include "string"

//================================
//テクスチャー管理
//武藤海人		2023/06/28
//================================

typedef struct {
	unsigned int texCord;
	uint8_t wide;
	uint8_t hight;
	uint8_t maxAnim;
}TEXTURE_DATA;



int LoadTexture(char* fileName);
void UninitTexture(void);

ID3D11ShaderResourceView** GetTexture(int index);

TEXTURE_DATA SetTexture(std::string fileName, uint8_t w, uint8_t h, uint8_t a);