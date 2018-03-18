#include"../../Header File/Character/proximityAttackCharacter.h"


ProximityAttackCharacter::ProximityAttackCharacter()
{
	attackType = AttackType::PROXIMITY;
}

ProximityAttackCharacter::~ProximityAttackCharacter()
{

}

void ProximityAttackCharacter::attack(float frameTime)
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