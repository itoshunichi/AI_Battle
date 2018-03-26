#ifndef TESAIRTCHARACTER_H_
#define TESTAIRCHARACTER_H_

#include"../Character/proximityAttackCharacter_Air.h"
#include"../Character/landCharacter.h"
#include"Status\status_TestCharacter.h"

class TestAirCharacter :public ProximityAttackCharacter_Air
{
public:
	TestAirCharacter();
	TestAirCharacter(GameManager *gameManager, PlayerNum pleryNum);
	~TestAirCharacter();
	void initialize();
	void update(float frameTime);
	void draw();

};

#endif