#include"../../Header File/Character/longDistanceAttackCharacter.h"

LongDistanceAttackCharacter::LongDistanceAttackCharacter()
{
	attackType = AttackType::LONG_DISTANCE;
}

LongDistanceAttackCharacter::~LongDistanceAttackCharacter()
{

}

void LongDistanceAttackCharacter::attack(float frameTime)
{
	if (mode == Mode::ATTACK)
	{
		attackTimer.update(frameTime);
		if (attackTimer.isEnd())
		{
			//Weapon¶¬
			firingWeapon();
			weapon->setDamage(status->attackPower);
			if (attackTargetCharacter->getHp() <= 0)mode = Mode::MOVE;
			attackTimer.resetTimer();
		}
	}
}

void LongDistanceAttackCharacter::collisionWeapon(Character *character)
{
	//Character *chara;
	weapons.erase(remove_if(weapons.begin(), weapons.end(), ([character](Weapon* w){return w->collisionCharacter(character); })), weapons.end());
	/*for each (Weapon* w in weapons)
	{
		if (w->collisionCharacter(character))
		{
			weapons.erase(remove(weapons.begin(), weapons.end(), w), weapons.end());
		}
	}*/
}
