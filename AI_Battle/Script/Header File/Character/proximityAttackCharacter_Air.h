#ifndef PROXIMITYATTACKCHARACTER_AIR_H_
#define PROXIMITYATTACKCHARACTER_AIR_H_

#include"airCharacter.h"

//�ߐڍU���̃L�����N�^�[
class ProximityAttackCharacter_Air :public AirCharacter
{
private:

public:
	ProximityAttackCharacter_Air();
	~ProximityAttackCharacter_Air();
protected:
	//�U������
	void attack(float frameTime);
	void startAttack(Character* character);
	void attackMove(float frameTime);
	Timer attackTimer;
};

#endif