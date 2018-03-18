#ifndef STATUS_H_
#define STATUS_H_

struct Status
{

	int maxHp;//‘Ì—Í
	int attackPower;//UŒ‚—Í
	float attackTime;//UŒ‚‘¬“x
	float moveSpeed;//ˆÚ“®‘¬“x
	float attackRange;//UŒ‚”ÍˆÍ
	virtual void setStatus() = 0;
};

#endif