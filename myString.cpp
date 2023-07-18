//====================================
//	myString.cpp	���앶���R�[�h�H
//	�����C�l		2023/07/17
//====================================

#include "myString.h"

#include "texture.h"

#include "sprite.h"
#include <Windows.h>

static TEXTURE_DATA g_StringTex = { NULL,0,0,0 };


string MyString::m_Hira = "�����������������������������������ĂƂȂɂʂ˂̂͂Ђӂւق܂݂ނ߂�������������񂪂����������������������Âłǂ΂тԂׂڂς҂Ղ؂ۂ�����";				//������
string MyString::m_Kata = "�A�C�E�G�I�J�L�N�P�R�T�V�X�Z�\�^�`�c�e�g�i�j�k�l�m�n�q�t�w�z�}�~�����������������������������K�M�O�Q�S�U�W�Y�[�]�_�a�d�f�h�o�r�u�x�{�p�s�v�y�|�b������";				//�J�^�J�i
string MyString::m_Kigo = "�@�I�h���������f�i�j";				//�S�p�L��


MyString::MyString(string text)
{
	//�e�N�X�`�����ǂݍ��܂�ĂȂ�������
	if(g_StringTex.texCord == NULL){
		g_StringTex = SetTexture("data/TEXTURE/hira.png", 16, 16, 256);
	}


	ChangeCode(text);
}
MyString::~MyString()
{
}

void MyString::DrawString(D3DXVECTOR2 pos, D3DXVECTOR2 size,D3DXCOLOR col)
{
	D3DXVECTOR2 pp=pos;
	for (int i = 0; i < m_Size; i++) {
		pp.x = pos.x + size.x * i;
		DrawAnimation_LT(&g_StringTex, &pp, &size, col, m_Text[i]);
	}
}

void MyString::GetStringLength(string text)
{
	int num, count;		//�������@�������ڂ����Ă邩
	num = count = 0;
	while (true) {
		if (count > text.size())break;	//���������J�E���g�̂ق��������Ȃ�����I���
		
		bool isMulti = IsDBCSLeadByte(text[count]);		//�����Ă�Ƃ��납���}���`�o�C�g�̐�s�o�C�g��������true

		if (isMulti)count+=2;							//�}���`�o�C�g��������1�ǉ��Ői�߂�

		else count++;
		num++;			//�������𑝂₷
	}

	m_Size = num;		//�傫�����L��
}

void MyString::ChangeCode(string text)
{
	//�e�L�X�g�̑傫���擾
	GetStringLength(text);

	m_Text = new unsigned char[m_Size];	//������

	int st, i;		//st �^�[�Q�b�g�̃X�g�����O�̏ꏊ�@i �J��Ԃ���
	st = i = 0;
	bool isMulti;
	//�ϊ�
	//for (int i = 1; i < m_Size; i += 2) {
	while (i < m_Size) {
		isMulti = IsDBCSLeadByte(text[st]);		//�}���`�o�C�g���V���O���o�C�g�����擾

		unsigned char buffer = 0;

		if (isMulti)			//�}���`�o�C�g�����̐�s�o�C�g��������
		{
			//uint8_t code = (uint8_t)text[st - 1];
			st++;
			if ((uint8_t)text[st - 1] == 129)			//��s�o�C�g��129����������{��L��
			{
				buffer = GetMultiKigo_129((uint8_t)text[st]);
			}
			else if ((uint8_t)text[st - 1] == 130)		//��s�o�C�g��130�������畽����
			{
				buffer = GetJAPHira_130((uint8_t)text[st]);
			}
			else if ((uint8_t)text[st - 1] == 131)		//��s�o�C�g��131��������Љ���
			{
				buffer = GetJAPKata_131((uint8_t)text[st]);
			}
		}
		else {									//��s�o�C�g�ł͂Ȃ�������
			buffer = GetENG_Single(text[st]);
		}

		/*for (int j = 1; j < hira.size(); j += 2) {
			if (text[i] == hira[j]) {
				int d = STRING_HIRA_A + j / 2;
				m_Text[st] = d;
				st++;
				break;
			}
		}*/

		//�ϊ������R�[�h����
		m_Text[i] = buffer;
		//m_Text[i] = i;
		i++;
		st++;
	}

	//�I�����Z�q
	m_Text[m_Size] = '\0';
}

unsigned char MyString::GetMultiKigo_129(uint8_t index)
{
	//�@�U�S�`�P�T�P



	return 0;
}

unsigned char MyString::GetJAPHira_130(uint8_t index)
{
	int count = 0;

	//�S�p����
	if (index >= 79 && index <= 88) {	
		uint8_t num = index - 79;
		return num + STRING_ZERO;
	}

	//������
	for (int i = 1; i < m_Hira.length(); i += 2) {
		if ((uint8_t)m_Hira[i] == index) {
			return STRING_HIRA_A + count;
		}
		count++;
	}

	return STRING_QUESTION;
}

unsigned char MyString::GetJAPKata_131(uint8_t index)
{
	return 0;
}

unsigned char MyString::GetENG_Single(uint8_t index)
{
	return 0;
}

