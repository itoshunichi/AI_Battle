#ifndef CHARACTER_H_
#define CHARACTER_H_

#include"../Default/entity.h"
#include"direction.h"
#include"square.h"

class Character :public Entity
{
public:
	//Ží—Þ
	enum Type
	{
		LAND,//—¤
		SKY,//‹ó
	};

	//ó‘Ô
	enum Mode
	{
		APPEARANCE,//“oê
		MOVE,//ˆÚ“®
		ATTACK,//UŒ‚
		ARRIVAL,//“ž’…
		DEAD,//Ž€–S
	};

	//UŒ‚•û–@
	enum AttackType
	{
		NONE,//–³‚µ
		PROXIMITY,//‹ßÚ
		LONG_DISTANCE,//‰“‹——£

	};
	//ƒXƒe[ƒ^ƒX
	struct States
	{
		int hp;//‘Ì—Í
		int attackPower;//UŒ‚—Í
		float attackTime;//UŒ‚‘¬“x
		float moveSpeed;//ˆÚ“®‘¬“x
		float attackRange;//UŒ‚”ÍˆÍ

	};
protected:
	//Ží—Þ
	Type type;
	//UŒ‚•û–@
	AttackType attackType;
	//ƒXƒe[ƒ^ƒX
	States states;
	//Œ»Ý‚Ìƒ}ƒX
	SQUARE currentSquare;
	//Œ»Ý‚ÌŒü‚«
	Direction direction;
	//Œ»Ý‚Ìó‘Ô
	Mode mode;
	//ƒvƒŒƒCƒ„[”Ô†
	int playerNum;
	//Ž©•ª‚Ì“X
	Entity myShop;
	//‘ŠŽè‚Ì“X
	Entity otherShop;

protected:
	void setPosition();
	//Šp“x‚ÌÝ’è
	void setAngle();
	//“oê
	void appearance();
	//ˆÚ“®ˆ—
	void move(float frameTime);
	//Œü‚«•ÏX
	void changeDirection();
public:
	Character();
	~Character();
	//‰Šú‰»
	virtual void initialize() = 0;
	//XV
	virtual void update(float frameTime) = 0;
	//•`‰æ
	virtual void draw() = 0;
	//‘ŠŽè“X‚Æ‚ÌÕ“Ë”»’è
	virtual void otherShopCollision(Entity &entity,int &customerCount);
	//Ž©•ª“X‚Æ‚ÌÕ“Ë”»’è
	virtual void myShopColiision(Entity &entity, int &customerCout);
	void setPosition(Vector2 position){ this->position = position; }
	SQUARE getCurrentSquare(){ return currentSquare; }
	

private:
	
	
};

#endif