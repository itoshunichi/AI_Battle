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
	//��̃L�����Ȃ珈�����Ȃ�
	if (character->getType() == Type::SKY)return;
	attackTargetCharacter = nullptr;
	attackTargetCharacter = character;
	//�ړ������U���͈͂ɓG�����邩�ǂ���
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
			//�_���[�W�𒼐ڗ^����
			attackTargetCharacter->damage(status->attackPower);
			if (attackTargetCharacter->getHp()<=0)mode = Mode::MOVE;
			attackTimer.resetTimer();
		}
	}
}