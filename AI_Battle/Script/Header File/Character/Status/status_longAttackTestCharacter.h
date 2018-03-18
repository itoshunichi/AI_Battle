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
		//‘Ì—Í
		maxHp = 30;
		//UŒ‚”ÍˆÍ
		attackRange = 200;
		//UŒ‚—Í
		attackPower = 20;
		//UŒ‚ŠÔŠu
		attackTime = 1;
		//ˆÚ“®ƒXƒs[ƒh
		moveSpeed = 50;
	}
};

#endif