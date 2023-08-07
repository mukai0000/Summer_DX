//=======================================
//UI管理　		UI.h
//武藤海人		2023/06/28
//=======================================

#pragma once

#ifndef UI_H
#define UI_H

#include "main.h"
#include "input.h"
#include "Object.h"

//インベントリ
/*
必要なもの
バッファー		マウスで移動させるときに使うやつ



*/

class UI
{
public:
	UI(ENTITY_POTENTIAL_STATUS* eps_P, ENTITY_STATUS* es_P);
	~UI();

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