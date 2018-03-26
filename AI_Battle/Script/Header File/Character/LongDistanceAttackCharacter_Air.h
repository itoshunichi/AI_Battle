#ifndef LONGDISTANCEATTACKCHARACTER_AIR_H_
#define LONGDISTANCEATTACKCHARACTER_AIR_H_

#include"airCharacter.h"
#include"Weapon\weapon.h"

//����̉������U���L����
class LongDistanceAttackCharacter_Air :public AirCharacter
{
private:

public:
	LongDistanceAttackCharacter_Air();
	~LongDistanceAttackCharacter_Air();
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
	void attackSetDegress();
};
#endif