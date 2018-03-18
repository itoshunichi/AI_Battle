
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
		//‘Ì—Í
		maxHp = 50;
		//UŒ‚”ÍˆÍ
		attackRange = 0;
		//UŒ‚—Í
		attackPower = 10;
		//UŒ‚ŠÔŠu
		attackTime = 1;
		//ˆÚ“®ƒXƒs[ƒh
		moveSpeed = 100;
	};
};

#endif