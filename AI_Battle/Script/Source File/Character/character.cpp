#include"../../Header File/Character/character.h"

Character::Character()
{
	//Tagを設定
	collisionTag = entityNS::COLLISION_TAG::CHARACTER;
	//あたり判定のタイプを設定
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

//移動処理
void Character::move(float frameTime)
{
	//移動状態じゃなかったら処理しない
	if (mode == Mode::MOVE || mode == Mode::TRANSPORT)
	{
		currentImage.setDegress(0);
		//右向きだったら右に移動
		if (isDirectionRight())
		{
			position.x += status->moveSpeed*frameTime;
		}
		//左向きだったら左に移動
		if (isDirectionLeft())
		{
			position.x -= status->moveSpeed*frameTime;
		}
	}
}

//登場時の処理
void Character::appearance()
{
	//1Pだったら
	if (isPlayer1())
	{
		direction = Direction::RIGHT;
	}
	//2Pだったら
	else if (isPlayer2())
	{
		direction = Direction::LEFT;
	}
}

//相手の店とのあたり判定
void Character::otherShopCollision(Entity &entity, int &customerCount)
{
	////1Pかつ右向きまたは2Pかつ左向き
	//if ((isPlayer1() && direction == Direction::RIGHT) || (isPlayer2() && direction == Direction::LEFT))
	//{
		//移動中かつ相手店に当たったら
		if (mode == Mode::MOVE&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			changeMode(Mode::TRANSPORT);
			customerCount--;
		}
	//}


}

//自分の店とのあたり判定
void Character::myShopColiision(Entity &entity, int &customerCount)
{
	////1Pかつ右向きまたは2Pかつ左向き
	//if ((playerNum == 1 && direction == Direction::LEFT) || (playerNum == 2 && direction == Direction::RIGHT))
	//{
		//運び中かつ相手店に当たったら
		if (mode == Mode::TRANSPORT&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			changeMode(Mode::MOVE);
			customerCount++;
		}
	//}
}

////攻撃開始
//void Character::startAttack(Character* character)
//{
//	attackTargetCharacter = nullptr;
//	attackTargetCharacter = character;
//	//移動中かつ攻撃範囲に敵がいるかどうか
//	if (mode == Mode::MOVE&&Distance(position, character->getPosition()) < status->attackRange)
//	{
//		changeMode(Mode::ATTACK);
//	}
//
//}

//向きの変更
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

//引数で指定したダメージ量をHpから減らす
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