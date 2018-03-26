
#ifndef STATUS_TESTCHARACTER_H_
#define STATUS_TESTCHARACTER_H_
#include"status.h"

class Status_TestCharacter :public Status
{
public:
	Status_TestCharacter(){ setStatus(); };
private:
	void setStatus()
	{
		//体力
		maxHp = 50;
		//攻撃範囲
		attackRange = 0;
		//攻撃力
		attackPower = 10;
		//攻撃間隔
		attackTime = 1;
		//移動スピード
		moveSpeed = 100;
		//コスト
		cost = 5;
	};
};

#endif