#include"../../Header File/Character/character.h"

Character::Character()
{
	//Tag��ݒ�
	collisionTag = entityNS::COLLISION_TAG::CHARACTER;
	//�����蔻��̃^�C�v��ݒ�
	collisionType = entityNS::COLLISION_TYPE::BOX;

}

Character::~Character()
{
	delete status;
}

void Character::setAngle()
{
	if (isDirectionRight())
	{
		currentImage.setDegress(90);
	}
	if (isDirectionLeft())
	{
		currentImage.setDegress(270);
	}
}

//�ړ�����
void Character::move(float frameTime)
{
	//�ړ���Ԃ���Ȃ������珈�����Ȃ�
	if (mode == Mode::MOVE || mode == Mode::TRANSPORT)
	{
		currentImage.setDegress(0);
		//�E������������E�Ɉړ�
		if (isDirectionRight())
		{
			position.x += status->moveSpeed*frameTime;
		}
		//�������������獶�Ɉړ�
		if (isDirectionLeft())
		{
			position.x -= status->moveSpeed*frameTime;
		}
	}
}

//�o�ꎞ�̏���
void Character::appearance()
{
	//1P��������
	if (isPlayer1())
	{
		direction = Direction::RIGHT;
	}
	//2P��������
	else if (isPlayer2())
	{
		direction = Direction::LEFT;
	}
}

//����̓X�Ƃ̂����蔻��
void Character::otherShopCollision(Entity &entity, int &customerCount)
{
	////1P���E�����܂���2P��������
	//if ((isPlayer1() && direction == Direction::RIGHT) || (isPlayer2() && direction == Direction::LEFT))
	//{
		//�ړ���������X�ɓ���������
		if (mode == Mode::MOVE&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			changeMode(Mode::TRANSPORT);
			customerCount--;
		}
	//}


}

//�����̓X�Ƃ̂����蔻��
void Character::myShopColiision(Entity &entity, int &customerCount)
{
	////1P���E�����܂���2P��������
	//if ((playerNum == 1 && direction == Direction::LEFT) || (playerNum == 2 && direction == Direction::RIGHT))
	//{
		//�^�ђ�������X�ɓ���������
		if (mode == Mode::TRANSPORT&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			changeMode(Mode::MOVE);
			customerCount++;
		}
	//}
}

////�U���J�n
//void Character::startAttack(Character* character)
//{
//	attackTargetCharacter = nullptr;
//	attackTargetCharacter = character;
//	//�ړ������U���͈͂ɓG�����邩�ǂ���
//	if (mode == Mode::MOVE&&Distance(position, character->getPosition()) < status->attackRange)
//	{
//		changeMode(Mode::ATTACK);
//	}
//
//}

//�����̕ύX
void Character::changeDirection()
{
	if (isDirectionRight())
	{
		direction = Direction::LEFT;
	}
	else if (isDirectionLeft())
	{
		direction = Direction::RIGHT;
	}
}

//�����Ŏw�肵���_���[�W�ʂ�Hp���猸�炷
void Character::damage(float damage)
{
	currentHp -= damage;
}

void Character::dead()
{
	if (mode == Mode::DEAD)
	{
		delete this;
	}
}

//void Character::collisionWeapon(Weapon& weapon)
//{
//
//}