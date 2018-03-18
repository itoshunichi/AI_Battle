#include"../../Header File/Character/characterManager.h"

CharacterManager::CharacterManager()
{

}

CharacterManager::CharacterManager(FormCharacter *formCharacter1, FormCharacter *formCharacter2)
{
	this->formCharacter_1P = formCharacter1;
	this->formCharacter_2P = formCharacter2;
}


void CharacterManager::update(float frameTime)
{
	attackManager();
}

//UŒ‚ŠÇ—
void CharacterManager::attackManager()
{
	for each (Character* c1 in formCharacter_1P->getFirstColumnCharacters())
	{
		for each (Character* c2 in formCharacter_2P->getFirstColumnCharacters())
		{
			c1->startAttack(c2);
			c2->startAttack(c1);
			if (dynamic_cast<LongAttackTestCharacter*>(c1))
			dynamic_cast<LongAttackTestCharacter*>(c1)->collisionWeapon(c2);
			if (dynamic_cast<LongAttackTestCharacter*>(c2))
			dynamic_cast<LongAttackTestCharacter*>(c2)->collisionWeapon(c1);
		}
	}

	for each (Character* c1 in formCharacter_1P->getSecondColumnCharacters())
	{
		for each (Character* c2 in formCharacter_2P->getSecondColumnCharacters())
		{
			c1->startAttack(c2);
			c2->startAttack(c1);
			if (dynamic_cast<LongAttackTestCharacter*>(c1))
				dynamic_cast<LongAttackTestCharacter*>(c1)->collisionWeapon(c2);
			if (dynamic_cast<LongAttackTestCharacter*>(c2))
				dynamic_cast<LongAttackTestCharacter*>(c2)->collisionWeapon(c1);
		}
	}

	for each (Character* c1 in formCharacter_1P->getThirdColumnCharacters())
	{
		for each (Character* c2 in formCharacter_2P->getThirdColumnCharacters())
		{
			c1->startAttack(c2);
			c2->startAttack(c1);
			if (dynamic_cast<LongAttackTestCharacter*>(c1))
				dynamic_cast<LongAttackTestCharacter*>(c1)->collisionWeapon(c2);
			if (dynamic_cast<LongAttackTestCharacter*>(c2))
				dynamic_cast<LongAttackTestCharacter*>(c2)->collisionWeapon(c1);
		}
	}
	
}



