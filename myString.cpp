//====================================
//	myString.cpp	���앶���R�[�h�H
//	�����C�l		2023/07/17
//====================================

#include "myString.h"


#include "sprite.h"
#include <Windows.h>

TEXTURE_DATA MyString::m_StringTex = { NULL,0,0,0 };


string MyString::m_Hira = "�����������������������������������ĂƂȂɂʂ˂̂͂Ђӂւق܂݂ނ߂�������������񂪂����������������������Âłǂ΂тԂׂڂς҂Ղ؂ۂ�����";				//������
string MyString::m_Kata = "�A�C�E�G�I�J�L�N�P�R�T�V�X�Z�\�^�`�c�e�g�i�j�k�l�m�n�q�t�w�z�}�~�����������������������������K�M�O�Q�S�U�W�Y�[�]�_�a�d�f�h�o�r�u�x�{�p�s�v�y�|�b������";				//�J�^�J�i
string MyString::m_Kigo = "�@�I�h���������f�i�j���{�A�|�B�^�O�P�Q�R�S�T�U�V�W�X�F�G�������H��";				//�S�p�L��
string MyString::m_Eng = "";



MyString::MyString(string text)
{
	//�e�N�X�`�����ǂݍ��܂�ĂȂ�������
	if(m_StringTex.texCord == NULL){
		m_StringTex = SetTexture("data/TEXTURE/hira.png", 16, 16, 256);
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
		DrawAnimation_LT(&m_StringTex, &pp, &size, col, m_Text[i]);
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

	m_Text = new uint8_t[m_Size];	//������

	int st, i;		//st �^�[�Q�b�g�̃X�g�����O�̏ꏊ�@i �J��Ԃ���
	st = i = 0;
	bool isMulti;
	//�ϊ�
	//for (int i = 1; i < m_Size; i += 2) {
	while (i < m_Size) {
		isMulti = IsDBCSLeadByte(text[st]);		//�}���`�o�C�g���V���O���o�C�g�����擾

		uint8_t buffer = 0;

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

uint8_t MyString::GetMultiKigo_129(uint8_t index)
{
	//�@�U�S�`�P�T�P



	return 0;
}

uint8_t MyString::GetJAPHira_130(uint8_t index)
{
	//�S�p����
	if (index >= 79 && index <= 88) {	
		uint8_t num = index - 79;
		return num + STRING_ZERO;
	}

	int count = 0;

	//������
	for (int i = 1; i < m_Hira.length(); i += 2) {
		if ((uint8_t)m_Hira[i] == index) {
			return STRING_HIRA_A + count;
		}
		count++;
	}

	return STRING_QUESTION;
}

uint8_t MyString::GetJAPKata_131(uint8_t index)
{
	int count = 0;
	for (int i = 1; i < m_Kata.length(); i += 2) {
		if ((uint8_t)m_Kata[i] == index) {
			return STRING_KANA_A + count;
		}
		count++;
	}

	return STRING_QUESTION;
}

uint8_t MyString::GetENG_Single(uint8_t index)
{
	if (index >= 48) {
		return index - 48 + STRING_ZERO;
	}
	return 0;
}

