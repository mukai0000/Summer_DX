//===========================================
// Object管理		Object.h
//	武藤海人		2023/07/19
//===========================================

#pragma once
#ifndef OBJECT_H		//インクルードガード
#define OBJECT_H

#include <string>
#include "main.h"


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

//===========================================
//			構造体
//===========================================
typedef struct {				//　オブジェクトの場所大きさ情報
	D3DXVECTOR2 pos;
	D3DXVECTOR2 oldPos;
	D3DXVECTOR2 size;
}ENTITY_TRANSFORM;

typedef struct {				//　ステータス　255を上限にしたい〇
	uint8_t			pow;
	uint8_t			vit;
	uint8_t			mgc;
}ENTITY_POTENTIAL_STATUS;

typedef struct{					//　実数ステータス
	uint8_t			lv;			//	レベル　	構造体にしなくてもいいかも
	int				hp;			//	hp			vitや装備によって変化
	int				mp;			//　mp			mgcや装備によって変化
	int				atk;		//　近接攻撃力	近接攻撃力
	int				mat;		//　魔法攻撃力	使わないかも
	int				def;		//	防御力　　　装備によってのみ変化　かモンスターとのレベル差でつけたい
}ENTITY_STATUS;

using namespace std;

class Object		//基底クラス		Objectマネージャークラスを作って配列で管理する。
{
public:
	Object();
	~Object();

	D3DXVECTOR2*	GetPosition		()							{ return &m_Trans.pos; }
	D3DXVECTOR2*	GetSize			()							{ return &m_Trans.size; }
	
	//３Ｄ描画するためにプレイヤーからの距離、Ｙをしゅとくする
	float* GetPositionY() { return &GetPosition()->y; }


	void			SetPosition(D3DXVECTOR2 pos) { m_Trans.pos = pos; }
	void			SetSize(D3DXVECTOR2 size) { m_Trans.size = size; }

protected:
	OBJECT_KIND_TAG m_ObjTag;

	ENTITY_TRANSFORM m_Trans;
};

class FieldObj :public Object{
public:
	FieldObj();
	~FieldObj();

};

class Entity :public Object {
public:
	Entity();
	~Entity();

	bool GetHitTrigger(Entity* target);

private:

	float m_CollisionSize;

};

#endif // !



