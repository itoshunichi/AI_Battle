#include"../../Header File/Character/proximityAttackCharacter_Air.h"


ProximityAttackCharacter_Air::ProximityAttackCharacter_Air()
{
	attackType = AttackType::PROXIMITY;
}

ProximityAttackCharacter_Air::~ProximityAttackCharacter_Air()
{

}

void ProximityAttackCharacter_Air::startAttack(Character* character)
{
	attackTargetCharacter = nullptr;
	attackTargetCharacter = character;
	//ˆÚ“®’†‚©‚ÂUŒ‚”ÍˆÍ‚É“G‚ª‚¢‚é‚©‚Ç‚¤‚©
	if (mode == Mode::MOVE&&Distance(position, vector2(character->getPosition().x, position.y)) < status->attackRange)
	{
		changeMode(Mode::ATTACK);
		
	}
}

void ProximityAttackCharacter_Air::attack(float frameTime)
{
	if (mode == Mode::ATTACK)
	{
		attackSetDegress();
		attackMove(frameTime);
		attackTimer.update(frameTime);
		if (attackTimer.isEnd())
		{
			//ƒ_ƒ[ƒW‚ð’¼Ú—^‚¦‚é
			attackTargetCharacter->damage(status->attackPower);
			if (attackTargetCharacter->getHp() <= 0)mode = Mode::MOVE;
			attackTimer.resetTimer();
		}
	}
}

//UŒ‚Žž‚ÌˆÚ“®ˆ—
void ProximityAttackCharacter_Air::attackMove(float frameTime)
{
	if (attackTargetCharacter->getPosition().x< position.x-currentImage.getWidth())
	{
		position.x -= status->moveSpeed*frameTime;
	}
	else if (attackTargetCharacter->getPosition().x+currentImage.getWidth() < position.x)
	{
		position.x +- status->moveSpeed*frameTime;
	}
}