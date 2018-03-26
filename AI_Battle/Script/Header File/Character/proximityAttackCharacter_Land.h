#ifndef PROXIMITYATTACKCHARACTER_LAND_H_
#define PROXIMITYATTACKCHARACTER_LAND_H_

#include"landCharacter.h"

//近接攻撃のキャラクター
class ProximityAttackCharacter_Land:public LandCharacter
{
private:
	
public:
	ProximityAttackCharacter_Land();
	~ProximityAttackCharacter_Land();
protected:
	//攻撃処理
	void attack(float frameTime);
	void startAttack(Character* character);
	Timer attackTimer;
};

#endif