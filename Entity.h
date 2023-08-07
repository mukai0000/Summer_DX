//================================
// Entity.h		Entity(プレイヤーや敵、遠距離攻撃
// 武藤　海人	2023/08/07
//================================

#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "main.h"
#include <stdint.h>

#include "Inventory.h"		//インベントリー
#include "Buff.h"			//バフデバフ、自動回復や毒、睡眠まひなど

//===========================================
//			列挙体
//===========================================
typedef enum {			//オブジェクトの種類
	KIND_PLAYER,
	KIND_ENEMY,
	KIND_BOSS,
	KIND_ITEM,
	KIND_OBJECT
}OBJECT_KIND_TAG;

typedef enum {			//当たり判定のモード
	MODE_CIRCLE,
	MODE_BOX,
	MODE_MAX
}COLLIDER_MODE;

//===========================================
//			構造体
//===========================================
typedef struct {				//　オブジェクトの場所大きさ情報
	D3DXVECTOR2 pos;
	D3DXVECTOR2 oldPos;
	D3DXVECTOR2 size;
}ENTITY_TRANSFORM;

typedef struct {				//　ステータス　255を上限にしたい〇
	uint8_t			lv;			//	レベル　	構造体にしなくてもいいかも
	uint8_t			pow;
	uint8_t			vit;
	uint8_t			mgc;
}ENTITY_POTENTIAL_STATUS;

typedef struct {					//　実数ステータス
	int				hp;			//	hp			vitや装備によって変化
	int				mp;			//　mp			mgcや装備によって変化
	int				atk;		//　近接攻撃力	近接攻撃力
	int				mat;		//　魔法攻撃力	使わないかも
	int				def;		//	防御力　　　装備によってのみ変化　かモンスターとのレベル差でつけたい
}ENTITY_STATUS;

//===========================================
//			クラス
//===========================================

class Entity {			//基底クラス
public:
	Entity();
	~Entity();

	bool GetHitTrigger(Entity* target);

private:
	float					m_CollisionSize;	//円判定用の半径
	ENTITY_TRANSFORM		m_Transform;		//現在地、1フレーム前の場所、大きさ、

	ENTITY_POTENTIAL_STATUS m_BathStatus;		//レベルやモンスターの種類によって変動するステータスの基礎値
	ENTITY_STATUS			m_MainStatus;		//実際に行動やステータスに反映される最終値（実数)
	ENTITY_STATUS			m_SubStatus;		//装備などによって変わる数値、多分いらない

	Inventory*				m_Inventory;		//インベントリ回り
	Buff*					m_Buff;				//状態異常　バフデバフ
};


#endif // !ENTITY_H

