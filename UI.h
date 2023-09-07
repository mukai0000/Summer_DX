//=======================================
//UI管理　		UI.h
//武藤海人		2023/09/05
//=======================================

#pragma once

#ifndef UI_H
#define UI_H

#include "main.h"
#include "input.h"
#include "Object.h"
#include "texture.h"

//インベントリ
/*
必要なもの
バッファー		マウスで移動させるときに使うやつ



*/

//列挙体
typedef enum {
	FILL_UP,
	FILL_DOWN,
	FILL_LEFT,		//1<-0
	FILL_RIGHT		//0->1
}FILL_VEC;


//構造体
typedef struct {
	TEXTURE_DATA	tex;
	D3DXVECTOR2		pos;		//描画場所の原点
	D3DXVECTOR2		size;		//描画サイズ、最大サイズ
	D3DXCOLOR		col;
	bool			active;		//表示するかどうか
	float			num;		//描画に関係する情報、
}UI_DATA;

//関数
UI_DATA SetUI_DATA(string texName, int w, int h, int a, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, bool act, float num);

class UI {
public:
	UI(string texName, int w, int h, int a, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, bool act, float num);
	UI(UI_DATA uiData) :m_Data(uiData) {};
	~UI() {};

	void virtual Update() {};

	void SetActive(bool b) { m_Data.active = b; }
	bool GetActive() { return m_Data.active; }
	void SwitchActive() { m_Data.active = !m_Data.active; }

	void virtual SetNumber(float n) { m_Data.num = n; }

	void virtual Draw() = 0;

protected:
	UI_DATA m_Data;
};

class GageBar : public UI {
public:
	GageBar(string texName, int w, int h, int a, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, bool act, float num, FILL_VEC vec);
	GageBar(UI_DATA uiData, FILL_VEC vec) :UI(uiData), m_Fill(vec) {};
	~GageBar() {};

	void SetNumber(float n) override;

	void Update()override;

	void Draw()override;

private:
	FILL_VEC m_Fill;

	D3DXVECTOR2 m_Sub;
	bool m_IsUpdate;			//セットナンバーで受け取ったデータがさっきと違ったら、描画に必要なデータの更新をする
};

class Button :public UI {
public:
	Button(string texName, int w, int h, int a, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col, bool act) :UI(texName, w, h, a, pos, size, col, act, 0), m_IsHit(false) {};
	Button(UI_DATA uiData) :UI(uiData), m_IsHit(false) {};
	~Button() {};

	void Update()override;

	bool GetClick() { return (m_Data.active && m_IsHit && IsMouseLeftTriggered()) ? true : false; };

	void Draw()override;
private:
	bool m_IsHit;
};



class UI_Manager
{
public:
	UI_Manager(ENTITY_POTENTIAL_STATUS* eps_P, ENTITY_STATUS* es_P);
	~UI_Manager();

	void SetPlayerStatus_P(ENTITY_POTENTIAL_STATUS* eps_P);
	void SetPlayerRealStatus_P(ENTITY_STATUS* es_P);

	void SetSwitchInventoryFlag();											//インベントリを表示するかどうか切り替えるやつ


	void Start();
	void Update();
	void End();

	void DrawUI();

private:
	bool m_IsInventory;		//UIを表示するかどうか

	ENTITY_POTENTIAL_STATUS* m_PlayerStatus;		//powとかvit
	ENTITY_STATUS* m_PlayerRealStatus;				//装備とかを装備した結果

};


#endif // !UI_H