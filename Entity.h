//================================
// Entity.h		Entity(プレイヤーや敵、遠距離攻撃
// 武藤　海人	2023/08/08
//================================

#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "main.h"
#include <stdint.h>

#include "Inventory.h"		//インベントリー
#include "Buff.h"			//バフデバフ、自動回復や毒、睡眠まひなど


//===========================================
//			マクロ定義
//===========================================


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

class Status {
public:
	Status();
	~Status() {};

	//ゲッター
	ENTITY_POTENTIAL_STATUS*	GetBathStatus			()				{ return &m_BathStatus; }
	ENTITY_STATUS*				GetNowStatus			()				{ return &m_NowStatus; }
	ENTITY_STATUS*				GetStandardStatus		()				{ return &m_StandardStatus; }
	int*						GetStatusPoint			()				{ return &m_StatusPoint; }

	bool						GetIsDead				()				{ return (m_NowStatus.hp <= 0) ? true : false; }	//死亡したかどうかを取得

	//セッター

	//呼び出し			
	//強化回り
	void	AddLevel				();
	void	AddPow					();
	void	AddVit					();
	void	AddMgc					();
	//増減　ダメージにも使う
	void	AddHp					(int add);			//実数を足したり引いたりしたいに使う
	void	AddMp					(int add);
	void	AddAtk					(int add);
	void	AddMat					(int add);
	void	AddDef					(int add);
	//更新回り
	void	RisetNowStatus			()				{ m_NowStatus = m_StandardStatus; }
	void	UpdateStandardStatus	();	
	void	UpdateStandardStatus	(ENTITY_STATUS *addStatus);		//装備によるステータスの上昇値を引数で受け取る

private:
	ENTITY_POTENTIAL_STATUS m_BathStatus;			//レベルやモンスターの種類によって変動するステータスの基礎値

	ENTITY_STATUS			m_StandardStatus;		//基準になるステータス	HPMPは最大値　レベルや装備での上昇量を加算したもの
	ENTITY_STATUS			m_NowStatus;			//バフなどで上昇した数値　結果値　実際に使う値

	int m_StatusPoint;								//基礎ステータスに触れるポイント

	Buff* m_Buff;				
};

class Entity {			//基底クラス
public:
	Entity();
	~Entity() {};

	bool	GetHitTrigger	(Entity* target ,COLLIDER_MODE mode);
	int		GetDamage		(int index);								//ダメージ量を取得するための関数、引数で攻撃の種類を取得ｓｓ
	void	SetDamage		(int damage);
protected:
	float					m_CollisionSize;	//円判定用の半径
	ENTITY_TRANSFORM		m_Transform;		//現在地、1フレーム前の場所、大きさ、


	Status*					m_Status;						//ステータス管理クラス
	//Inventory*				m_Inventory;					//インベントリ回り
	Buff*					m_Buff[BUFF_MAX];				//状態異常　バフデバフ
};


#endif // !ENTITY_H

