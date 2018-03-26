#ifndef TESTCHARACTER_H_
#define TESTCHARACTER_H_

#include"../Character/proximityAttackCharacter_Land.h"
#include"../Character/landCharacter.h"
#include"Status\status_TestCharacter.h"

class TestCharacter:public ProximityAttackCharacter_Land
{
public:
	TestCharacter();
	TestCharacter(GameManager *gameManager,PlayerNum pleryNum);
	~TestCharacter();
	void initialize();
	void update(float frameTime);
	void draw();

};

#endif