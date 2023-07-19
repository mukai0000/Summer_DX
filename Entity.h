//===========================================
// Entity管理		Entity.h
//	武藤海人		2023/07/19
//===========================================

#pragma once
#ifndef ENTITY_H		//インクルードガード
#define ENTITY_H

#include <string>

typedef enum {
	ENTITY_NORMAL,
	ENTITY_DAMAGE
}ENTITY_STATE;

typedef struct {			//255を上限にしたい〇
	uint8_t			pow;
	uint8_t			vit;
	uint8_t			mgc;
}ENTITY_POTENTIAL_STATUS;

typedef struct{
	uint8_t			lv;			//	レベル　	構造体にしなくてもいいかも
	int				hp;			//	hp			vitや装備によって変化
	int				mp;			//　mp			mgcや装備によって変化
	int				atk;		//　近接攻撃力	近接攻撃力
	int				mat;		//　魔法攻撃力	使わないかも
	int				def;		//	防御力　　　装備によってのみ変化　かモンスターとのレベル差でつけたい
}ENTITY_STATUS;


using namespace std;
class Entity
{
public:
	Entity();
	~Entity();



private:
};

#endif // !



