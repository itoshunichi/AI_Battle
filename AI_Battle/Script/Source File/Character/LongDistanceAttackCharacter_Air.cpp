#include"../../Header File/Character/LongDistanceAttackCharacter_Air.h"

//�󒆉������L�����N�^�[
LongDistanceAttackCharacter_Air::LongDistanceAttackCharacter_Air()
{
	attackType = AttackType::LONG_DISTANCE;
}

LongDistanceAttackCharacter_Air::~LongDistanceAttackCharacter_Air()
{

}

//�U���J�n
void LongDistanceAttackCharacter_Air::startAttack(Character* character)
{
	attackTargetCharacter = nullptr;
	attackTargetCharacter = character;
	attackSetDegress();
	//�ړ������U���͈͂ɓG�����邩�ǂ���
	if (mode == Mode::MOVE&&Distance(position, character->getPosition()) < status->attackRange)
	{
		changeMode(Mode::ATTACK);
	}
}


void LongDistanceAttackCharacter_Air::attack(float frameTime)
{
	if (mode == Mode::ATTACK)
	{
		attackTimer.update(frameTime);
		if (attackTimer.isEnd())
		{
			//Weapon����
			firingWeapon();
			weapon->setDamage(status->attackPower);
			if (attackTargetCharacter->getHp() <= 0)mode = Mode::MOVE;
			attackTimer.resetTimer();
		}
	}
}

void LongDistanceAttackCharacter_Air::collisionWeapon(Character *character)
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

