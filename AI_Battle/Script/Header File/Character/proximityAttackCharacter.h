#ifndef PROXIMITYATTACKCHARACTER_H_
#define PROXIMITYATTACKCHARACTER_H_

#include"character.h"

//近接攻撃のキャラクター
class ProximityAttackCharacter:public Character
{
private:
	
public:
	ProximityAttackCharacter();
	~ProximityAttackCharacter();
protected:
	//攻撃処理
	void attack(float frameTime);
	Timer attackTimer;
};

#endif