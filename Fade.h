#pragma once

#ifndef MAIN_H
#define MAIN_H
#include "main.h"
#endif // !MAIN_H

#ifndef TEXTURE_H
#define TEXTURE_H
#include "texture.h"
#endif // !TEXTURE_H

typedef enum	//どのモードか　フェードアウトだけなのか、インだけなのか、両方なのか
{
	FADE_OUT_IN,
	FADE_OUT_ONLY,
	FADE_IN_ONLY,
	FADE_MODE_MAX
}FADE_MODE;

typedef enum	//現在どのフェードモードを実行しているか
{
	FADE_NONE,
	FADE_OUT,
	FADE_IN,
	FADE_STATE_MAX
}FADE_STATE;

class  Fade {
public:
	//基礎
	Fade() {};					//Initの代わり
	~Fade() {};					//Uninitの代わり

	virtual void Update() {};
	virtual void Draw() {};

	virtual void SetFade(FADE_MODE fMode){}

protected:

	virtual void FadeIN() {};
	virtual void FadeOUT() {};


	TEXTURE_DATA m_TexData;		//テクスチャのデータ

	FADE_STATE m_FState;		//今実行中のフェードのモード

};

class CircleFade:public Fade
{
public:
	//基礎
	CircleFade(D3DXVECTOR2* player);				//Initの代わり
	~CircleFade() {};									//Uninitの代わり

	void Update()override {};
	void Draw()override;

	void SetFade(FADE_MODE fMode)override {}

private:


	void FadeIN() override{};
	void FadeOUT() override{};



	//==========================
	//			変数
	//==========================

	D3DXVECTOR2 *m_TargetP;

	D3DXVECTOR2 m_LeftTop;
	D3DXVECTOR2 m_RightBottom;

	float m_Radius;

};

class WallFade {




};

