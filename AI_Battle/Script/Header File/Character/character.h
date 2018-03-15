#ifndef CHARACTER_H_
#define CHARACTER_H_

#include"../Default/entity.h"
#include"direction.h"
#include"square.h"
#include"../Otherwise/timer.h"

class Character :public Entity
{
public:
	//種類
	enum Type
	{
		LAND,//陸
		SKY,//空
	};

	//状態
	enum Mode
	{
		APPEARANCE,//登場
		MOVE,//移動
		ATTACK,//攻撃
		ARRIVAL,//到着
		DEAD,//死亡
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
	//現在の状態
	Mode mode;
	//プレイヤー番号
	int playerNum;
	//自分の店
	Entity myShop;
	//相手の店
	Entity otherShop;
	//現在の列
	int currentRow;
	Character* attackTargetCharacter;
protected:

	void setPosition();
	//角度の設定
	void setAngle();
	//登場
	void appearance();
	//移動処理
	void move(float frameTime);
	//攻撃処理
	void attack(float frameTime);
	void dead();
	//向き変更
	void changeDirection();
public:
	Character();
	~Character();
	//初期化
	virtual void initialize() = 0;
	//更新
	virtual void update(float frameTime) = 0;
	//描画
	virtual void draw() = 0;
	//相手店との衝突判定
	virtual void otherShopCollision(Entity &entity,int &customerCount);
	//自分店との衝突判定
	virtual void myShopColiision(Entity &entity, int &customerCout);
	//攻撃開始
	void startAttack(Character* characters);
	void setPosition(Vector2 position){ this->position = position; }
	SQUARE getCurrentSquare(){ return currentSquare; }
	void damage(float damage);
	
	//状態の変更
	void changeMode(Mode mode){ this->mode = mode;}
	int getHp(){ return states.hp; }
	int getCurrentRow(){ return currentRow; }
private:
	Timer attackTimer;
	
};

#endif