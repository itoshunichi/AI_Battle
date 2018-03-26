#ifndef STATUS_LONGATTACKTESTCHARACTER_H_
#define STATUS_LONGATTACKTESTCHARACTER_H_

#include"status.h"

class Status_LongAttackTestCharacter :public Status
{
public:
	Status_LongAttackTestCharacter(){ setStatus(); }
private:
	void setStatus()
	{
		//体力
		maxHp = 30;
		//攻撃範囲
		attackRange = 200;
		//攻撃力
		attackPower = 20;
		//攻撃間隔
		attackTime = 1;
		//移動スピード
		moveSpeed = 50;
		//コスト
		cost = 5;
	}
};

#endif