#include"../../Header File/Character/proximityAttackCharacter_Land.h"


ProximityAttackCharacter_Land::ProximityAttackCharacter_Land()
{
	attackType = AttackType::PROXIMITY;
}

ProximityAttackCharacter_Land::~ProximityAttackCharacter_Land()
{

}

void ProximityAttackCharacter_Land::startAttack(Character* character)
{
	//空のキャラなら処理しない
	if (character->getType() == Type::SKY)return;
	attackTargetCharacter = nullptr;
	attackTargetCharacter = character;
	//移動中かつ攻撃範囲に敵がいるかどうか
	if (mode == Mode::MOVE&&Distance(position, character->getPosition()) < status->attackRange)
	{
		changeMode(Mode::ATTACK);
	}
}

void ProximityAttackCharacter_Land::attack(float frameTime)
{
	if (mode == Mode::ATTACK)
	{
		attackTimer.update(frameTime);
		if (attackTimer.isEnd())
		{
			//ダメージを直接与える
			attackTargetCharacter->damage(status->attackPower);
			if (attackTargetCharacter->getHp()<=0)mode = Mode::MOVE;
			attackTimer.resetTimer();
		}
	}
}