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
		TRANSPORT,//‰^‚Ô
		DEAD,//Ž€–S
	};

	//UŒ‚•û–@
	enum AttackType
	{
		NONE,//–³‚µ
		PROXIMITY,//‹ßÚ
		LONG_DISTANCE,//‰“‹——£

	};
protected:
	//Ží—Þ
	Type type;
	//UŒ‚•û–@
	AttackType attackType;
	//ƒXƒe[ƒ^ƒX
	Status* status;
	//Œ»Ý‚Ìƒ}ƒX
	SQUARE currentSquare;
	//Œ»Ý‚ÌŒü‚«
	Direction direction;
	//Œ»Ý‚Ìó‘Ô
	Mode mode;
	//ƒvƒŒƒCƒ„[”Ô†
	PlayerNum playerNum;
	//Œ»Ý‚Ì—ñ
	int currentRow;
	//Œ»Ý‚ÌHP
	int currentHp;
	//UŒ‚‚Ì‘ÎÛ
	Character* attackTargetCharacter;
protected:
	
	//Šp“x‚ÌÝ’è
	void setAngle();
	//“oê
	void appearance();
	//ˆÚ“®ˆ—
	void move(float frameTime);
	//UŒ‚ˆ—
	//void attack(float frameTime);
	void dead();
	//‰EŒü‚«‚©‚Ç‚¤‚©
	bool isDirectionRight(){ return direction == Direction::RIGHT; }
	//¶Œü‚«‚©‚Ç‚¤‚©
	bool isDirectionLeft(){ return direction == Direction::LEFT; }
	//1P‚©‚Ç‚¤‚©
	bool isPlayer1(){ return playerNum == PlayerNum::PLAYER1; }
	//2P‚©
	bool isPlayer2(){ return playerNum == PlayerNum::PLAYER2; }
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
	virtual void setPosition(float pointPositionX, int pointRow) = 0;
	//‘ŠŽè“X‚Æ‚ÌÕ“Ë”»’è
	virtual void otherShopCollision(Entity &entity,int &customerCount);
	//Ž©•ª“X‚Æ‚ÌÕ“Ë”»’è
	virtual void myShopColiision(Entity &entity, int &customerCout);
	//UŒ‚ŠJŽn
	virtual void startAttack(Character* characters) = 0;
	//UŒ‚ˆ—
	virtual void attack(float frameTime) = 0;
	SQUARE getCurrentSquare(){ return currentSquare; }
	void damage(float damage);
	//ó‘Ô‚Ì•ÏX
	void changeMode(Mode mode){ this->mode = mode;}
	//‘Ì—ÍŽæ“¾
	int getHp(){ return currentHp; }
	//Œ»Ý‚Ì—ñ‚ðŽæ“¾
	int getCurrentRow(){ return currentRow; }
	//ó‘Ô‚ÌŽæ“¾
	Mode getMode(){ return mode; }
	//ƒRƒXƒg‚ÌŽæ“¾
	int getCost(){ return status->cost; }
	Type getType(){ return type; }
};

#endif