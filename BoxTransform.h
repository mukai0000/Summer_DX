#pragma once

#include "main.h"

#define pi (3.15f)
#define RAD(x) x/180*pi

//=================== MEMO =================
/*
自作ゲームを作るときのための下準備

例えば巨大化する敵がいたとして、その場合scale変数をいじる必要があるわけだけど、そうなった場合どうするか考えてる
毎フレームスケールに関係する処理をするのは効率が悪いから、EditScale関数みたいなのを作って初期化時以外はそれを経由しないとscaleはいじれないようにするのが無難な気がする

OldPositionにOldRotationも追加するか悩み中

*/

class BoxTransform
{
	//======================
	//コンストラクタ
	//======================
	BoxTransform();
	BoxTransform(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot);



	//======================
	//		変数
	//======================
private:
	D3DXVECTOR2 position;		//原点座標
	D3DXVECTOR2 oldPosition;	//1フレーム前の原点座標
	D3DXVECTOR2 scale;			//幅と高さ
	D3DXVECTOR2 velocity;		//移動方向？ 常にノーマライズした値を記録するようにしたい	directionのほうがいいのか？
	float rotation;				//回転角
	float radian;				//ラジアン角　作るべきか悩んでる　毎度計算するより変数で確保しておいたほうがいいって聞いた
	float speed;				//移動距離を設定しておく、単位ベクトルのvelocityに乗算して実際の移動距離にする予定

	float range;				//中心点から四つ角までの距離　どのタイミングで更新するか悩む

	D3DXVECTOR2 no1Position;	//ポリゴンの生成に使う四つ角
	D3DXVECTOR2 no2Position;
	D3DXVECTOR2 no3Position;
	D3DXVECTOR2 no4Position;




	//イニシャライザー
	//コンストラクタなどで受け取ったデータを使って、受け取ってないデータに格納する
	void VertexPositionInitialize();


	//======================
	//セッター
	//======================
	void	SetPosition(D3DXVECTOR2 pos) { position = pos; }
	void	SetPosition(float x, float y) { position = D3DXVECTOR2(x, y); }

	void	SetScale(D3DXVECTOR2 size) { scale = size; }
	void	SetScale(float x, float y) { scale = D3DXVECTOR2(x, y); }

	void	SetRotation(float rot) { rotation = rot; radian = RAD(rotation);}		//下の更新処理部で回転の処理を内包してる関数を作るからあまりこれはいらないかも

	void	SetSpeed(float spd) { speed = spd; }

	//======================
	//ゲッター
	//======================

	//メンバ変数のゲッター
	D3DXVECTOR2		GetPosition() { return position; }								//原点の取得
	D3DXVECTOR2		GetScale() { return scale; }									//幅、高さのゲッター
	float			GetRotation() { return rotation;						 }		//回転角度のゲッター
	float			GetRadius() { return (scale.x + scale.y) * 0.5f; }				//四角いテクスチャを張ることを前提にしてるからBoxTransformだけど当たり判定でBCをとる時に半径が必要になるから、正方形ではない場合に幅と高さの中間を取得できるようにしておく、ただ極端に細長いやつのことは考えてない

	float			GetRadian() { return radian; }									//回転に使うラジアン角の取得


	//方向のゲッター
	D3DXVECTOR2		GetFront();														//LT,RTの中間地点のある方向を取得する関数、Unityのパクリ
	D3DXVECTOR2		GetBack();														//LB,RBの中間地点のある方向を取得する関数、Unityのパクリ
	D3DXVECTOR2		GetLeft();														//LT,LBの中間地点のある方向を取得する関数、Unityのパクリ
	D3DXVECTOR2		GetRight();														//RT,RBの中間地点のある方向を取得する関数、Unityのパクリ

	//4辺の座標を取得
	float			GetTopY();														//一番小さいY
	float			GetBottomY();													//一番大きいY
	float			GetLeftX();														//一番小さいX
	float			GetRightX();													//一番大きいX

	//4頂点の取得		マップチップの当たり判定をとるときに必須、
	D3DXVECTOR2		GetLeftTopPosition();											//左上の座標のゲッター	回転してた時は最も小さいX、YをD3DXVECTOR2変数に格納して返却
	D3DXVECTOR2		GetRightTopPosition();											//右上の座標のゲッター
	D3DXVECTOR2		GetLeftBottomPosition();										//左下の座標のゲッター
	D3DXVECTOR2		GetRightBottomPosition();										//右下の座標のゲッター

	//カリング依存の4頂点の取得　Zの書き順になるように中身を考える
	//1----2
	//   ／
	// ／ 
	//3----4
	//ポリゴン描画時に毎度毎度計算して出力するの効率悪いからメンバ変数に追加するか悩んでる
	//メンバ変数に追加したらメモリを食うし、追加しなかったら処理が遅くなるし
	D3DXVECTOR2		GetNo1Position() { return no1Position; }
	D3DXVECTOR2		GetNo2Position() { return no2Position; }
	D3DXVECTOR2		GetNo3Position() { return no3Position; }
	D3DXVECTOR2		GetNo4Position() { return no4Position; }

	//原点から頂点までの距離
	float			GetVertex_CentorRange(){ return sqrtf(pow(scale.x * 0.5,2) + pow(scale.y * 0.5,2)); }

	//このトランスフォームの原点と引数（ターゲットの）差分から角度を取得する関数
	float			GetTarget_CentorRadian(D3DXVECTOR2 target);

	//======================
	//更新処理
	//======================

	//中心を原点にして回転する場合と、4頂点を原点にして回転する場合とで別の関数を用意しておきたい
	//ただセッターにRotationのセッターがあるからそれとの兼ね合いはまだ考えてない

	//中心回転の更新処理
	//void UPDataRotation_C();							//現在の角度を指定した角度に変更したい場合、回転角のセッターと併用して使用する?
	void UPDataRotation_C(float rotate);				//現在の角度を引数の値にする
	void UPDataAddRotation_C(float rotate);				//現在の角度に加算して回転させたい場合呼び出す

	void UPDataRotation_LT(float rotate);				//左上（1の座標）を原点に回転させる場合に呼ぶ
	void UPDataRotation_RT(float rotate);				//右上（2の座標）を原点に回転させる場合に呼ぶ
	void UPDataRotation_LB(float rotate);				//左下（3の座標）を原点に回転させる場合に呼ぶ
	void UPDataRotation_RB(float rotate);				//右下（4の座標）を原点に回転させる場合に呼ぶ

	//void UPDataAddRotation_LT(float rotate);			//左上（1の座標）を原点に加算回転させる場合に呼ぶ
	//void UPDataAddRotation_RT(float rotate);			//右上（2の座標）を原点に加算回転させる場合に呼ぶ
	//void UPDataAddRotation_LB(float rotate);			//左下（3の座標）を原点に加算回転させる場合に呼ぶ
	//void UPDataAddRotation_RB(float rotate);			//右下（4の座標）を原点に加算回転させる場合に呼ぶ


	void UPDataMovePosition();							//ベロシティとスピードを実際の移動速度としてポジションに反映

	void UPDataNumberPosition();						//ポリゴンに使う四つ角の座標を現在の回転角から更新する関数

	void UPDataOldData();								//オールドポジションを更新する関数、回転角も記憶しないといけない気がする

};

