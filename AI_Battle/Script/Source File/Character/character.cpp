#include"../../Header File/Character/character.h"

Character::Character()
{
	collisionTag = entityNS::COLLISION_TAG::CHARACTER;
	collisionType = entityNS::COLLISION_TYPE::BOX;

}

Character::~Character()
{

}

void Character::setAngle()
{
	if (direction == Direction::RIGHT)
	{
		currentImage.setDegress(90);
	}
	if (direction == Direction::LEFT)
	{
		currentImage.setDegress(270);
	}
}

//�ړ�����
void Character::move(float frameTime)
{
	//�ړ���Ԃ���Ȃ������珈�����Ȃ�
	if (mode != Mode::MOVE)return;
	//�E������������E�Ɉړ�
	if (direction == Direction::RIGHT)
	{
		position.x += states.moveSpeed*frameTime;
	}
	//�������������獶�Ɉړ�
	if (direction == Direction::LEFT)
	{
		position.x -= states.moveSpeed*frameTime;
	}
}

//�o�ꎞ�̏���
void Character::appearance()
{
	attackTimer = Timer(states.attackTime);
	//1P��������
	if (playerNum == 1)
	{
		direction = Direction::RIGHT;
	}
	//2P��������
	else if (playerNum == 2)
	{
		direction = Direction::LEFT;
	}
}

//����̓X�Ƃ̂����蔻��
void Character::otherShopCollision(Entity &entity, int &customerCount)
{
	//1P���E�����܂���2P��������
	if ((playerNum == 1 && direction == Direction::RIGHT) || (playerNum == 2 && direction == Direction::LEFT))
	{
		//�ړ���������X�ɓ���������
		if (mode == Mode::MOVE&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			customerCount--;
		}
	}


}

void Character::myShopColiision(Entity &entity, int &customerCount)
{
	//1P���E�����܂���2P��������
	if ((playerNum == 1 && direction == Direction::LEFT) || (playerNum == 2 && direction == Direction::RIGHT))
	{
		//�ړ���������X�ɓ���������
		if (mode == Mode::MOVE&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			customerCount++;
		}
	}
}

//�U���J�n
void Character::startAttack(Character* character)
{
	attackTargetCharacter = nullptr;
	attackTargetCharacter = character;
	//�ړ������U���͈͂ɓG�����邩�ǂ���
	if (mode == Mode::MOVE&&Distance(position, character->getPosition()) < states.attackRange)
	{
		mode = Mode::ATTACK;
	}

}

//�����̕ύX
void Character::changeDirection()
{
	if (direction == Direction::RIGHT)
	{
		direction = Direction::LEFT;
	}
	else if (direction == Direction::LEFT)
	{
		direction = Direction::RIGHT;
	}
}

//�U������
void Character::attack(float frameTime)
{
	if (mode == Mode::ATTACK)
	{
		attackTimer.update(frameTime);
		if (attackTimer.isEnd())
		{
			//�ߐڂȂ�
			if (attackType = AttackType::PROXIMITY)
			{
				//�_���[�W�𒼐ڗ^����
				attackTargetCharacter->damage(states.attackPower);
			}
			//�������Ȃ�
			if (attackType = AttackType::LONG_DISTANCE)
			{
				//�U���𐶐�
			}

			attackTimer.resetTimer();
		}
	}
}

//�����Ŏw�肵���_���[�W�ʂ�Hp���猸�炷
void Character::damage(float damage)
{
	states.hp -= damage;
}

void Character::dead()
{
	if (mode == Mode::DEAD)
	{
		delete this;
	}
}