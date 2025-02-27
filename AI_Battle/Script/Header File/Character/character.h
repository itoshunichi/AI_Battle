#ifndef CHARACTER_H_
#define CHARACTER_H_

#include"../Default/entity.h"
#include"direction.h"
#include"square.h"
#include"../Otherwise/timer.h"
#include"Status\status.h"
#include"playerNum.h"

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
		TRANSPORT,//運ぶ
		DEAD,//死亡
	};

	//攻撃方法
	enum AttackType
	{
		NONE,//無し
		PROXIMITY,//近接
		LONG_DISTANCE,//遠距離

	};
protected:
	//種類
	Type type;
	//攻撃方法
	AttackType attackType;
	//ステータス
	Status* status;
	//現在のマス
	SQUARE currentSquare;
	//現在の向き
	Direction direction;
	//現在の状態
	Mode mode;
	//プレイヤー番号
	PlayerNum playerNum;
	//現在の列
	int currentRow;
	//現在のHP
	int currentHp;
	//攻撃の対象
	Character* attackTargetCharacter;
protected:
	
	//角度の設定
	void setAngle();
	//登場
	void appearance();
	//移動処理
	void move(float frameTime);
	//攻撃処理
	//void attack(float frameTime);
	void dead();
	//右向きかどうか
	bool isDirectionRight(){ return direction == Direction::RIGHT; }
	//左向きかどうか
	bool isDirectionLeft(){ return direction == Direction::LEFT; }
	//1Pかどうか
	bool isPlayer1(){ return playerNum == PlayerNum::PLAYER1; }
	//2Pか
	bool isPlayer2(){ return playerNum == PlayerNum::PLAYER2; }
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
	virtual void setPosition(float pointPositionX, int pointRow) = 0;
	//相手店との衝突判定
	virtual void otherShopCollision(Entity &entity,int &customerCount);
	//自分店との衝突判定
	virtual void myShopColiision(Entity &entity, int &customerCout);
	//攻撃開始
	virtual void startAttack(Character* characters) = 0;
	//攻撃処理
	virtual void attack(float frameTime) = 0;
	SQUARE getCurrentSquare(){ return currentSquare; }
	void damage(float damage);
	//状態の変更
	void changeMode(Mode mode){ this->mode = mode;}
	//体力取得
	int getHp(){ return currentHp; }
	//現在の列を取得
	int getCurrentRow(){ return currentRow; }
	//状態の取得
	Mode getMode(){ return mode; }
	//コストの取得
	int getCost(){ return status->cost; }
	Type getType(){ return type; }
};

#endif