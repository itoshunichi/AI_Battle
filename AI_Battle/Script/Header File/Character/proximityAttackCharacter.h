#ifndef PROXIMITYATTACKCHARACTER_H_
#define PROXIMITYATTACKCHARACTER_H_

#include"character.h"

//�ߐڍU���̃L�����N�^�[
class ProximityAttackCharacter:public Character
{
private:
	
public:
	ProximityAttackCharacter();
	~ProximityAttackCharacter();
protected:
	//�U������
	void attack(float frameTime);
	Timer attackTimer;
};

#endif