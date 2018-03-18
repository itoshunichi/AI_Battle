#ifndef LONGATTAKTESTCHARACTER_H_
#define LONGATTAKTESTCHARACTER_H_

#include"longDistanceAttackCharacter.h"
#include"Status\status_longAttackTestCharacter.h"
#include"Weapon\testWeapon.h"

class LongAttackTestCharacter :public LongDistanceAttackCharacter
{
	
public:
	LongAttackTestCharacter();
	LongAttackTestCharacter(GameManager *gameManager, Vector2 position, int pleryNum);
	~LongAttackTestCharacter();
	void initialize();
	void update(float frameTime);
	void draw();
	void firingWeapon();
private:
	Vector2 weaponFormPosition();

};

#endif