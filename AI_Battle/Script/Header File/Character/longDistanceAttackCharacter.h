#ifndef LONGDISTANCEATTACKCHARACTER_H_
#define LONGDISTANCEATTACKCHARACTER_H_

#include"character.h"
#include"Weapon\weapon.h"

class LongDistanceAttackCharacter:public Character
{
private:
	
public:
	LongDistanceAttackCharacter();
	~LongDistanceAttackCharacter();
	void collisionWeapon(Character *Character);
protected:
	//����
	Weapon* weapon;
	list<Weapon*> weapons;
	Timer attackTimer;
	//�U������
	void attack(float frameTime);
	//���픭��
	virtual void firingWeapon() = 0;
	virtual Vector2 weaponFormPosition() = 0;
};
#endif