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
		//�̗�
		maxHp = 30;
		//�U���͈�
		attackRange = 200;
		//�U����
		attackPower = 20;
		//�U���Ԋu
		attackTime = 1;
		//�ړ��X�s�[�h
		moveSpeed = 50;
		//�R�X�g
		cost = 5;
	}
};

#endif