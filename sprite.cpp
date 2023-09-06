//=============================================================================
//
// �X�v���C�g���� [sprite.cpp]
// Author : 
//
//=============================================================================
#include "sprite.h"
#include "renderer.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BOX_VERTEX_NUM 4	//�K�v�Ȓ��_�̐�


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;	// ���_���

unsigned int g_NumberSumple;


//=============================================================================
// ����������
//=============================================================================
void InitSprite(void)
{
	g_NumberSumple = LoadTexture((char*)"data/TEXTURE/number.png");

	ID3D11Device* pDevice = GetDevice();

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * BOX_VERTEX_NUM;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);
}

//=============================================================================
// �I������
//=============================================================================
void UninitSprite(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̍���j
//Y		: Y���W�i�X�v���C�g�̍���j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}


//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	D3DXCOLOR Color(r, g, b, a);
	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = Color;
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = Color;
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = Color;
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = Color;
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}


//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
void DrawSpriteColorRotate(int texNo, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	// ���W�ϊ�
	vertex[0].Position.x = (-hw) * cosf(Rot) - (-hh) * sinf(Rot) + X;
	vertex[0].Position.y = (-hw) * sinf(Rot) + (-hh) * cosf(Rot) + Y;

	vertex[1].Position.x = (hw)*cosf(Rot) - (-hh) * sinf(Rot) + X;
	vertex[1].Position.y = (hw)*sinf(Rot) + (-hh) * cosf(Rot) + Y;

	vertex[2].Position.x = (-hw) * cosf(Rot) - (hh)*sinf(Rot) + X;
	vertex[2].Position.y = (-hw) * sinf(Rot) + (hh)*cosf(Rot) + Y;
	vertex[3].Position.x = (hw)*cosf(Rot) - (hh)*sinf(Rot) + X;
	vertex[3].Position.y = (hw)*sinf(Rot) + (hh)*cosf(Rot) + Y;

	D3DXCOLOR Color(r, g, b, a);
	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//CX	: ��]�����WX
//CY	: ��]�����WY
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
void DrawSpriteColorRotateAxis(int texNo, float X, float Y, float Width, float Height, float CX, float CY,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	//��CX,CY����]���ƍl����
	//��]����(0,0)�̌��_�Ɉړ����邽�߁A��]���̍��W�̕�������`�S�̂̍��W���}�C�i�X���A���̏�Ԃŉ�]���s��

	// ���W�ϊ�
	vertex[0].Position.x = (-CX - hw) * cosf(Rot) - (-CY - hh) * sinf(Rot);
	vertex[0].Position.y = (-CX - hw) * sinf(Rot) + (-CY - hh) * cosf(Rot);
	vertex[1].Position.x = (-CX + hw) * cosf(Rot) - (-CY - hh) * sinf(Rot);
	vertex[1].Position.y = (-CX + hw) * sinf(Rot) + (-CY - hh) * cosf(Rot);
	vertex[2].Position.x = (-CX - hw) * cosf(Rot) - (-CY + hh) * sinf(Rot);
	vertex[2].Position.y = (-CX - hw) * sinf(Rot) + (-CY + hh) * cosf(Rot);
	vertex[3].Position.x = (-CX + hw) * cosf(Rot) - (-CY + hh) * sinf(Rot);
	vertex[3].Position.y = (-CX + hw) * sinf(Rot) + (-CY + hh) * cosf(Rot);

	//��]�̕ϊ����I�������Ԃŉ�]���̍��W���v���X���A���_�ɖ߂��B����ɕ\�����W�iX,Y�j�܂ňړ�������
	vertex[0].Position.x += CX + X;
	vertex[0].Position.y += CY + Y;
	vertex[1].Position.x += CX + X;
	vertex[1].Position.y += CY + Y;
	vertex[2].Position.x += CX + X;
	vertex[2].Position.y += CY + Y;
	vertex[3].Position.x += CX + X;
	vertex[3].Position.y += CY + Y;

	D3DXCOLOR Color(r, g, b, a);
	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawBoxColor(D3DXVECTOR2* pos, D3DXVECTOR2* size, D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw = size->x * 0.5f;
	float hh = size->y * 0.5f;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(pos->x - hw, pos->y - hh, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(pos->x + hw, pos->y - hh, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(pos->x - hw, pos->y + hh, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(0, 1);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(pos->x + hw, pos->y + hh, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(1, 1);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�e�N�X�`���̎w��
	unsigned wite = LoadTexture((char*)"data/TEXTURE/White.png");

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(wite));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawBoxColor_LTRB(D3DXVECTOR2* lt, D3DXVECTOR2* rb, D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;


	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(lt->x, lt->y, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(rb->x, lt->y, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(lt->x, rb->y, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(0, 1);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(rb->x, rb->y, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(1, 1);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�e�N�X�`���̎w��
	unsigned wite = LoadTexture((char*)"data/TEXTURE/White.png");

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(wite));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawBoxColor_TB_FOUR(float* top, float* bottom, float* lt, float* rt, float* lb, float* rb, D3DXCOLOR* color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;


	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(*lt, *top, 0.0f);
	vertex[0].Diffuse = *color;
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(*rt, *top, 0.0f);
	vertex[1].Diffuse = *color;
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(*lb, *bottom, 0.0f);
	vertex[2].Diffuse = *color;
	vertex[2].TexCoord = D3DXVECTOR2(0, 1);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(*rb, *bottom, 0.0f);
	vertex[3].Diffuse = *color;
	vertex[3].TexCoord = D3DXVECTOR2(1, 1);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�e�N�X�`���̎w��
	unsigned wite = LoadTexture((char*)"data/TEXTURE/White.png");

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(wite));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawSprite(TEXTURE_DATA* tex, D3DXVECTOR2* pos, float* radius)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(pos->x - *radius, pos->y - *radius, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(pos->x + *radius, pos->y - *radius, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(pos->x - *radius, pos->y + *radius, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0, 1);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(pos->x + *radius, pos->y + *radius, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1, 1);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex->texCord));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawSprite(TEXTURE_DATA* tex, D3DXVECTOR2* pos, D3DXVECTOR2* size)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw = size->x * 0.5f;
	float hh = size->y * 0.5f;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(pos->x - hw, pos->y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(pos->x + hw, pos->y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(pos->x - hw, pos->y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0, 1);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(pos->x + hw, pos->y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1, 1);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex->texCord));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawSprite_LT(TEXTURE_DATA* tex, D3DXVECTOR2* pos, D3DXVECTOR2* size, D3DXCOLOR* col,D3DXVECTOR4* uv) {
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(pos->x, pos->y, 0.0f);
	vertex[0].Diffuse = *col;
	vertex[0].TexCoord = D3DXVECTOR2(uv->x, uv->y);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(pos->x + size->x, pos->y, 0.0f);
	vertex[1].Diffuse = *col;
	vertex[1].TexCoord = D3DXVECTOR2(uv->x + uv->z, uv->y);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(pos->x, pos->y + size->y, 0.0f);
	vertex[2].Diffuse = *col;
	vertex[2].TexCoord = D3DXVECTOR2(uv->x, uv->y + uv->w);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(pos->x + size->x, pos->y + size->y, 0.0f);
	vertex[3].Diffuse = *col;
	vertex[3].TexCoord = D3DXVECTOR2(uv->x + uv->z, uv->y + uv->w);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex->texCord));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawSprite_TB_FOUR(TEXTURE_DATA* tex, float* top, float* bottom, float* lt, float* rt, float* lb, float* rb)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	D3DXCOLOR col = { 1, 1, 1, 1 };
	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(*lt, *top, 0.0f);
	vertex[0].Diffuse = col;
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(*rt, *top, 0.0f);
	vertex[1].Diffuse = col;
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(*lb, *bottom, 0.0f);
	vertex[2].Diffuse = col;
	vertex[2].TexCoord = D3DXVECTOR2(0, 1);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(*rb, *bottom, 0.0f);
	vertex[3].Diffuse = col;
	vertex[3].TexCoord = D3DXVECTOR2(1, 1);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex->texCord));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawBox_LTRB(D3DXVECTOR2* lt, D3DXVECTOR2* rb, D3DXCOLOR* color)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;


	vertex[0].Position = D3DXVECTOR3(lt->x, lt->y, 0.0f);
	vertex[1].Position = D3DXVECTOR3(rb->x, lt->y, 0.0f);
	vertex[2].Position = D3DXVECTOR3(lt->x, rb->y, 0.0f);
	vertex[3].Position = D3DXVECTOR3(rb->x, rb->y, 0.0f);

	//�`�悵�������̕������J��Ԃ�
	for (int i = 0; i < BOX_VERTEX_NUM; i++)
	{
		vertex[i].Diffuse = *color;

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);

		// �|���S���`��
		GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
	}
}

void DrawBox_LTRB(D3DXVECTOR2 lt, D3DXVECTOR2 rb, D3DXCOLOR color)
{
	//// ���_�o�b�t�@�ݒ�
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	//// �v���~�e�B�u�g�|���W�ݒ�
	//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;


	vertex[0].Position = D3DXVECTOR3(lt.x, lt.y, 0.0f);
	vertex[1].Position = D3DXVECTOR3(rb.x, lt.y, 0.0f);
	vertex[2].Position = D3DXVECTOR3(lt.x, rb.y, 0.0f);
	vertex[3].Position = D3DXVECTOR3(rb.x, rb.y, 0.0f);

	//�`�悵�������̕������J��Ԃ�
	for (int i = 0; i < BOX_VERTEX_NUM; i++)
	{
		vertex[i].Diffuse = color;
	}

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

void DrawNumberSumple(D3DXVECTOR2 pos, D3DXVECTOR2 size, int target)
{
	//1000�̈�
	int num = target / 1000;
	DrawSprite(g_NumberSumple, pos.x, pos.y, size.x * 0.7f, size.y, 0.1f * num, 0, 0.1f, 1);
	num = target / 100 % 10;
	DrawSprite(g_NumberSumple, pos.x + size.x * 0.7f, pos.y, size.x * 0.7f, size.y, 0.1f * num, 0, 0.1f, 1);
	num = target / 10 % 10;
	DrawSprite(g_NumberSumple, pos.x + size.x * 1.4f, pos.y, size.x * 0.7f, size.y, 0.1f * num, 0, 0.1f, 1);
	num = target % 10;
	DrawSprite(g_NumberSumple, pos.x + size.x * 2.1f, pos.y, size.x * 0.7f, size.y, 0.1f * num, 0, 0.1f, 1);
}


void DrawAnimation_LT(TEXTURE_DATA* tex, D3DXVECTOR2* pos, D3DXVECTOR2* size, D3DXCOLOR col, int target)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float uw = 1.0f / (int)tex->wide;
	float vh = 1.0f / (int)tex->hight;

	int u = target % (int)tex->wide;
	int v = target / (int)tex->wide;
	

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(pos->x, pos->y, 0.0f);
	vertex[0].Diffuse = col;
	vertex[0].TexCoord = D3DXVECTOR2(u * uw, v * vh);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(pos->x + size->x, pos->y, 0.0f);
	vertex[1].Diffuse = col;
	vertex[1].TexCoord = D3DXVECTOR2(u * uw + uw, v * vh);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(pos->x, pos->y + size->y, 0.0f);
	vertex[2].Diffuse = col;
	vertex[2].TexCoord = D3DXVECTOR2(u * uw, v * vh + vh);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(pos->x + size->x, pos->y + size->y, 0.0f);
	vertex[3].Diffuse = col;
	vertex[3].TexCoord = D3DXVECTOR2(u * uw + uw, v * vh + vh);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex->texCord));

	// �|���S���`��
	GetDeviceContext()->Draw(BOX_VERTEX_NUM, 0);
}

