#ifndef CHARACTERMANAGER
#define CHARACTERMANAGER

#include"formCharacter.h"
#include"longDistanceAttackCharacter_Land.h"
#include"longDistanceAttackCharacter_Air.h"

//�L�����N�^�[���܂Ƃ߂�N���X
class CharacterManager
{
private:
	FormCharacter *formCharacter_1P;
	FormCharacter *formCharacter_2P;
	void attackManager();

public:
	CharacterManager();
	CharacterManager(FormCharacter *formCharacter1, FormCharacter *formCharacter2);
	void update(float frameTime);
	
};

#endif