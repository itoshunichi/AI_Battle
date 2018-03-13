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

//移動処理
void Character::move(float frameTime)
{
	//移動状態じゃなかったら処理しない
	if (mode != Mode::MOVE)return;
	//右向きだったら右に移動
	if (direction == Direction::RIGHT)
	{
		position.x += states.moveSpeed*frameTime;
	}
	//左向きだったら左に移動
	if (direction == Direction::LEFT)
	{
		position.x -= states.moveSpeed*frameTime;
	}
}

//登場時の処理
void Character::appearance()
{
	//1Pだったら
	if (playerNum == 1)
	{
		direction = Direction::RIGHT;
	}
	//2Pだったら
	else if (playerNum == 2)
	{
		direction = Direction::LEFT;
	}
}

//相手の店とのあたり判定
void Character::otherShopCollision(Entity &entity,int &customerCount)
{
	//1Pかつ右向きまたは2Pかつ左向き
	if ((playerNum == 1 && direction == Direction::RIGHT) || (playerNum == 2 && direction == Direction::LEFT))
	{
		//移動中かつ相手店に当たったら
		if (mode == Mode::MOVE&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			customerCount--;
		}
	}
	

}

void Character::myShopColiision(Entity &entity, int &customerCount)
{
	//1Pかつ右向きまたは2Pかつ左向き
	if ((playerNum == 1 && direction == Direction::LEFT) || (playerNum == 2 && direction == Direction::RIGHT))
	{
		//移動中かつ相手店に当たったら
		if (mode == Mode::MOVE&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			customerCount++;
		}
	}
}

//向きの変更
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