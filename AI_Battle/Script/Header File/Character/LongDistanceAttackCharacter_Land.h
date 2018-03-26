#ifndef LONGDISTANCEATTACKCHARACTER_LAND_H_
#define LONGDISTANCEATTACKCHARACTER_LAND_H_

#include"landCharacter.h"
#include"Weapon\weapon.h"

//����̉������U���L����
class LongDistanceAttackCharacter_Land:public LandCharacter
{
private:
	
public:
	LongDistanceAttackCharacter_Land();
	~LongDistanceAttackCharacter_Land();
	void collisionWeapon(Character *Character);
protected:
	//����
	Weapon* weapon;
	list<Weapon*> weapons;
	Timer attackTimer;
	void startAttack(Character* character);
	//�U������
	void attack(float frameTime);
	//���픭��
	virtual void firingWeapon() = 0;
	virtual Vector2 weaponFormPosition() = 0;
};
#endif