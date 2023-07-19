//====================================
//	myString.cpp	自作文字コード？
//	武藤海人		2023/07/17
//====================================

#include "myString.h"


#include "sprite.h"
#include <Windows.h>

TEXTURE_DATA MyString::m_StringTex = { NULL,0,0,0 };


string MyString::m_Hira = "あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをんがぎぐげござじずぜぞだぢづでどばびぶべぼぱぴぷぺぽっゃゅょ";				//平仮名
string MyString::m_Kata = "アイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨラリルレロワヲンガギグゲゴザジズゼゾダヂヅデドバビブベボパピプペポッャュョ";				//カタカナ
string MyString::m_Kigo = "　！”＃＄％＆’（）＊＋、－。／０１２３４５６７８９：；＜＝＞？＠";				//全角記号
string MyString::m_Eng = "";



MyString::MyString(string text)
{
	//テクスチャが読み込まれてなかったら
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
	int num, count;		//文字数　何文字目を見てるか
	num = count = 0;
	while (true) {
		if (count > text.size())break;	//文字数よりカウントのほうが多くなったら終わり
		
		bool isMulti = IsDBCSLeadByte(text[count]);		//今見てるところかがマルチバイトの先行バイトだったらtrue

		if (isMulti)count+=2;							//マルチバイトだったら1個追加で進める

		else count++;
		num++;			//文字数を増やす
	}

	m_Size = num;		//大きさを記憶
}

void MyString::ChangeCode(string text)
{
	//テキストの大きさ取得
	GetStringLength(text);

	m_Text = new uint8_t[m_Size];	//文字列

	int st, i;		//st ターゲットのストリングの場所　i 繰り返す回数
	st = i = 0;
	bool isMulti;
	//変換
	//for (int i = 1; i < m_Size; i += 2) {
	while (i < m_Size) {
		isMulti = IsDBCSLeadByte(text[st]);		//マルチバイトかシングルバイトかを取得

		uint8_t buffer = 0;

		if (isMulti)			//マルチバイト文字の先行バイトだったら
		{
			//uint8_t code = (uint8_t)text[st - 1];
			st++;
			if ((uint8_t)text[st - 1] == 129)			//先行バイトが129だったら日本語記号
			{
				buffer = GetMultiKigo_129((uint8_t)text[st]);
			}
			else if ((uint8_t)text[st - 1] == 130)		//先行バイトが130だったら平仮名
			{
				buffer = GetJAPHira_130((uint8_t)text[st]);
			}
			else if ((uint8_t)text[st - 1] == 131)		//先行バイトが131だったら片仮名
			{
				buffer = GetJAPKata_131((uint8_t)text[st]);
			}
		}
		else {									//先行バイトではなかったら
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

		//変換したコードを代入
		m_Text[i] = buffer;
		//m_Text[i] = i;
		i++;
		st++;
	}

	//終了演算子
	m_Text[m_Size] = '\0';
}

uint8_t MyString::GetMultiKigo_129(uint8_t index)
{
	//　６４～１５１



	return 0;
}

uint8_t MyString::GetJAPHira_130(uint8_t index)
{
	//全角数字
	if (index >= 79 && index <= 88) {	
		uint8_t num = index - 79;
		return num + STRING_ZERO;
	}

	int count = 0;

	//平仮名
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

