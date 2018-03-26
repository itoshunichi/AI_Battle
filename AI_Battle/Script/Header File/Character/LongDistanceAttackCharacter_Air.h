#ifndef LONGDISTANCEATTACKCHARACTER_AIR_H_
#define LONGDISTANCEATTACKCHARACTER_AIR_H_

#include"airCharacter.h"
#include"Weapon\weapon.h"

//—¤ã‚Ì‰“‹——£UŒ‚ƒLƒƒƒ‰
class LongDistanceAttackCharacter_Air :public AirCharacter
{
private:

public:
	LongDistanceAttackCharacter_Air();
	~LongDistanceAttackCharacter_Air();
	void collisionWeapon(Character *Character);
protected:
	//•Ší
	Weapon* weapon;
	list<Weapon*> weapons;
	Timer attackTimer;
	void startAttack(Character* character);
	//UŒ‚ˆ—
	void attack(float frameTime);
	//•Ší”­Ë
	virtual void firingWeapon() = 0;
	virtual Vector2 weaponFormPosition() = 0;
	void attackSetDegress();
};
#endif