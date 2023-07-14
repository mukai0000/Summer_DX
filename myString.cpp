#include "myString.h"


#include "texture.h"

#include "sprite.h"

static TEXTURE_DATA g_StringTex = { NULL,0,0,0 };

static string hira= "あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをん";

MyString::MyString(string text)
{
	//テクスチャが読み込まれてなかったら
	if(g_StringTex.texCord == NULL){
		g_StringTex = SetTexture("data/TEXTURE/hiraaaaaaaaaa.png", 16, 16, 256);
	}

	ChangeCode(text);
}
MyString::~MyString()
{
}

void MyString::DrawString(D3DXVECTOR2 pos, D3DXVECTOR2 size,D3DXCOLOR col)
{
	D3DXVECTOR2 pp=pos;
	for (int i = 0; i < m_Size / 2; i++) {
		pp.x = pos.x + size.x * i;
		DrawAnimation_LT(&g_StringTex, &pp, &size, col, m_Text[i]);
	}
}


void MyString::ChangeCode(string text)
{
	//テキストの大きさ取得
	m_Size = text.size();

	m_Text = new unsigned char[m_Size / 2 + 1];

	int t = 0;
	//変換
	for (int i = 1; i < m_Size; i += 2) {

		for (int j = 1; j < hira.size(); j += 2) {
			if (text[i] == hira[j]) {
				int d = 94 + j / 2+1;
				m_Text[t] = d;
				t++;
				break;
			}
		}
	}

	//終了演算子
	m_Text[m_Size / 2] = '\0';
}
