#ifndef CHARACTER_H_
#define CHARACTER_H_

#include"../Default/entity.h"
#include"direction.h"
#include"square.h"

class Character :public Entity
{
	//種類
	enum Type
	{
		LAND,//陸
		SKY,//空
	};

	//攻撃方法
	enum AttackType
	{
		NONE,//無し
		PROXIMITY,//近接
		LONG_DISTANCE,//遠距離

	};
	//ステータス
	struct States
	{
		int hp;//体力
		int attackPower;//攻撃力
		float attackTime;//攻撃速度
		float moveSpeed;//移動速度
		float attackRange;//攻撃範囲

	};
protected:
	//種類
	Type type;
	//攻撃方法
	AttackType attackType;
	//ステータス
	States states;

	//現在のマス
	SQUARE currentSquare;
	//現在の向き
	Direction direction;
	//角度の設定
	void setAngle();
public:
	Character();
	~Character();
	//初期化
	virtual void initialize() = 0;
	//更新
	virtual void update(float frameTime) = 0;
	//描画
	virtual void draw() = 0;

	SQUARE getCurrentSquare(){ return currentSquare; }
};

#endif