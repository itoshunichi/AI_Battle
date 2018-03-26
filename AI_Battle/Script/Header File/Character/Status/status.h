#ifndef STATUS_H_
#define STATUS_H_

struct Status
{

	int maxHp;//体力
	int attackPower;//攻撃力
	float attackTime;//攻撃速度
	float moveSpeed;//移動速度
	float attackRange;//攻撃範囲
	int cost;//コスト

	virtual void setStatus() = 0;
};

#endif