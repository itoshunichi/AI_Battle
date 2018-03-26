#ifndef LONGATTAKTESTCHARACTER_H_
#define LONGATTAKTESTCHARACTER_H_

#include"longDistanceAttackCharacter_Land.h"
#include"Status\status_longAttackTestCharacter.h"
#include"Weapon\testWeapon.h"

class LongAttackTestCharacter :public LongDistanceAttackCharacter_Land
{
	
public:
	LongAttackTestCharacter();
	LongAttackTestCharacter(GameManager *gameManager, PlayerNum pleryNum);
	~LongAttackTestCharacter();
	void initialize();
	void update(float frameTime);
	void draw();
	void firingWeapon();
private:
	Vector2 weaponFormPosition();

};

#endif