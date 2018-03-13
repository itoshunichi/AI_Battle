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
void Character::otherShopCollision(Entity &entity,int &customerCount)
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