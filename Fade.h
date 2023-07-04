#pragma once

#ifndef MAIN_H
#define MAIN_H
#include "main.h"
#endif // !MAIN_H

#ifndef TEXTURE_H
#define TEXTURE_H
#include "texture.h"
#endif // !TEXTURE_H

typedef enum	//�ǂ̃��[�h���@�t�F�[�h�A�E�g�����Ȃ̂��A�C�������Ȃ̂��A�����Ȃ̂�
{
	FADE_OUT_IN,
	FADE_OUT_ONLY,
	FADE_IN_ONLY,
	FADE_MODE_MAX
}FADE_MODE;

typedef enum	//���݂ǂ̃t�F�[�h���[�h�����s���Ă��邩
{
	FADE_NONE,
	FADE_OUT,
	FADE_IN,
	FADE_STATE_MAX
}FADE_STATE;

class  Fade {
public:
	//��b
	Fade() {};					//Init�̑���
	~Fade() {};					//Uninit�̑���

	virtual void Update() {};
	virtual void Draw() {};

	virtual void SetFade(FADE_MODE fMode){}

protected:

	virtual void FadeIN() {};
	virtual void FadeOUT() {};


	TEXTURE_DATA m_TexData;		//�e�N�X�`���̃f�[�^

	FADE_STATE m_FState;		//�����s���̃t�F�[�h�̃��[�h

};

class CircleFade:public Fade
{
public:
	//��b
	CircleFade(D3DXVECTOR2* player);				//Init�̑���
	~CircleFade() {};									//Uninit�̑���

	void Update()override {};
	void Draw()override;

	void SetFade(FADE_MODE fMode)override {}

private:


	void FadeIN() override{};
	void FadeOUT() override{};



	//==========================
	//			�ϐ�
	//==========================

	D3DXVECTOR2 *m_TargetP;

	D3DXVECTOR2 m_LeftTop;
	D3DXVECTOR2 m_RightBottom;

	float m_Radius;

};

class WallFade {




};

