#ifndef STATUS_H_
#define STATUS_H_

struct Status
{

	int maxHp;//�̗�
	int attackPower;//�U����
	float attackTime;//�U�����x
	float moveSpeed;//�ړ����x
	float attackRange;//�U���͈�
	virtual void setStatus() = 0;
};

#endif