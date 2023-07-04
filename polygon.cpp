/*==============================================================================

   ���_�Ǘ� [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_POLYGON 100	//�\������|���S���̐�


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
struct POLYGON{
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2     size;	//�傫��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	D3DXCOLOR		color;	//���_�J���[
	float			rot;
};

static POLYGON g_Player;
static POLYGON g_Polygon[NUM_POLYGON];

static int g_TexNo = 0;
static float g_U = 0.0f;
static float g_V = 0.0f;
static int g_AnimePattern = 0;
static int g_AnimeSkipFrame = 0;



//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	g_TexNo = LoadTexture((char*)"data/TEXTURE/airou.png");

	//������
	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = SCREEN_HEIGHT / 2;
	g_Player.size = D3DXVECTOR2(400.0f, 400.0f);
	g_Player.vel.x = 0.0f;
	g_Player.vel.y = 0.0f;
	g_Player.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.rot = 0.0f;

	for (int i = 0; i < NUM_POLYGON; i++)
	{
		g_Polygon[i].pos.x = frand() * SCREEN_WIDTH;
		g_Polygon[i].pos.y = frand() * SCREEN_HEIGHT;

		g_Polygon[i].vel.x = 0.0f;
		g_Polygon[i].vel.y = 0.0f;

		g_Polygon[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		g_Polygon[i].rot = frand()*(D3DX_PI * 2);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
	for (int i = 0; i < NUM_POLYGON; i++)
	{
		g_Polygon[i].rot += 0.01f;
	}

	//�L�[�{�[�h
	if (GetKeyboardPress(DIK_UP))
	{
		g_Player.pos.y -= 5.0f;
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		g_Player.pos.y += 5.0f;
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		g_Player.pos.x -= 5.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_Player.pos.x += 5.0f;
	}

	if (GetKeyboardPress(DIK_D)) {
		g_Player.size.x += 5.0f;
	}
	if (GetKeyboardPress(DIK_A)) {
		g_Player.size.x -= 5.0f;
	}
	if (GetKeyboardPress(DIK_S)) {
		g_Player.size.y += 5.0f;
	}
	if (GetKeyboardPress(DIK_W)) {
		g_Player.size.y -= 5.0f;
	}

	if (GetKeyboardPress(DIK_Q)) {
		g_Player.rot -= 0.05f;
	}
	if (GetKeyboardPress(DIK_E)) {
		g_Player.rot += 0.05f;
	}



	//�Q�[���p�b�h
	if (IsButtonPressed(0, BUTTON_A) || GetKeyboardPress(DIK_SPACE))
	{
		//���W�̃��Z�b�g
		g_Player.pos.x = SCREEN_WIDTH / 2;
		g_Player.pos.y = SCREEN_HEIGHT / 2;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	for (int i = 0; i < NUM_POLYGON; i++)
	{
		DrawSpriteColorRotate(g_TexNo,
			g_Polygon[i].pos.x, g_Polygon[i].pos.y,
			300.0f, 300.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			g_Polygon[i].color.r, g_Polygon[i].color.g, g_Polygon[i].color.b, g_Polygon[i].color.a,
			g_Polygon[i].rot);
	}

	//�v���C���[�̕`��
	DrawSpriteColorRotate(g_TexNo,
		g_Player.pos.x, g_Player.pos.y,
		g_Player.size.x, g_Player.size.y,
		0.0f, 0.0f,
		1.0f, 1.0f,
		g_Player.color.r, g_Player.color.g, g_Player.color.b, g_Player.color.a,
		g_Player.rot);
}
