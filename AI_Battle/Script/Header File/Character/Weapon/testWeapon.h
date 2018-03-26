#ifndef TESTWEAPON_H_
#define TESTWEAPON_J_

#include"weapon.h"

class TestWeapon:public Weapon
{
public:
	TestWeapon();
	TestWeapon(GameManager *gameManager,Vector2 targetCharacterPosition, Vector2 position);
	~TestWeapon();
	void initialize();
	void update(float frameTime);
	void draw();
};

#endif