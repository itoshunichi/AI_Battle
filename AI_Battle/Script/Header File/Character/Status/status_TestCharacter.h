
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
		//�̗�
		maxHp = 50;
		//�U���͈�
		attackRange = 0;
		//�U����
		attackPower = 10;
		//�U���Ԋu
		attackTime = 1;
		//�ړ��X�s�[�h
		moveSpeed = 100;
	};
};

#endif