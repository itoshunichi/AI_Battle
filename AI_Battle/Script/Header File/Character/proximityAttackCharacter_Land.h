#ifndef PROXIMITYATTACKCHARACTER_LAND_H_
#define PROXIMITYATTACKCHARACTER_LAND_H_

#include"landCharacter.h"

//�ߐڍU���̃L�����N�^�[
class ProximityAttackCharacter_Land:public LandCharacter
{
private:
	
public:
	ProximityAttackCharacter_Land();
	~ProximityAttackCharacter_Land();
protected:
	//�U������
	void attack(float frameTime);
	void startAttack(Character* character);
	Timer attackTimer;
};

#endif