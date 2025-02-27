#include"../../Header File/Character/longDistanceAttackCharacter_Land.h"

//陸上遠距離キャラ
LongDistanceAttackCharacter_Land::LongDistanceAttackCharacter_Land()
{
	attackType = AttackType::LONG_DISTANCE;
}

LongDistanceAttackCharacter_Land::~LongDistanceAttackCharacter_Land()
{

}

//攻撃開始
void LongDistanceAttackCharacter_Land::startAttack(Character* character)
{
	attackTargetCharacter = nullptr;
	attackTargetCharacter = character;
	//移動中かつ攻撃範囲に敵がいるかどうか
	if (mode == Mode::MOVE&&Distance(position, character->getPosition()) < status->attackRange)
	{
		changeMode(Mode::ATTACK);
	}
}


void LongDistanceAttackCharacter_Land::attack(float frameTime)
{
	if (mode == Mode::ATTACK)
	{
		attackTimer.update(frameTime);
		if (attackTimer.isEnd())
		{
			//Weapon生成
			firingWeapon();
			weapon->setDamage(status->attackPower);
			if (attackTargetCharacter->getHp() <= 0)mode = Mode::MOVE;
			attackTimer.resetTimer();
		}
	}
}

void LongDistanceAttackCharacter_Land::collisionWeapon(Character *character)
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
