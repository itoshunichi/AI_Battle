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

//ˆÚ“®ˆ—
void Character::move(float frameTime)
{
	//ˆÚ“®ó‘Ô‚¶‚á‚È‚©‚Á‚½‚çˆ—‚µ‚È‚¢
	if (mode != Mode::MOVE)return;
	//‰EŒü‚«‚¾‚Á‚½‚ç‰E‚ÉˆÚ“®
	if (direction == Direction::RIGHT)
	{
		position.x += states.moveSpeed*frameTime;
	}
	//¶Œü‚«‚¾‚Á‚½‚ç¶‚ÉˆÚ“®
	if (direction == Direction::LEFT)
	{
		position.x -= states.moveSpeed*frameTime;
	}
}

//“oê‚Ìˆ—
void Character::appearance()
{
	attackTimer = Timer(states.attackTime);
	//1P‚¾‚Á‚½‚ç
	if (playerNum == 1)
	{
		direction = Direction::RIGHT;
	}
	//2P‚¾‚Á‚½‚ç
	else if (playerNum == 2)
	{
		direction = Direction::LEFT;
	}
}

//‘Šè‚Ì“X‚Æ‚Ì‚ ‚½‚è”»’è
void Character::otherShopCollision(Entity &entity, int &customerCount)
{
	//1P‚©‚Â‰EŒü‚«‚Ü‚½‚Í2P‚©‚Â¶Œü‚«
	if ((playerNum == 1 && direction == Direction::RIGHT) || (playerNum == 2 && direction == Direction::LEFT))
	{
		//ˆÚ“®’†‚©‚Â‘Šè“X‚É“–‚½‚Á‚½‚ç
		if (mode == Mode::MOVE&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			customerCount--;
		}
	}


}

void Character::myShopColiision(Entity &entity, int &customerCount)
{
	//1P‚©‚Â‰EŒü‚«‚Ü‚½‚Í2P‚©‚Â¶Œü‚«
	if ((playerNum == 1 && direction == Direction::LEFT) || (playerNum == 2 && direction == Direction::RIGHT))
	{
		//ˆÚ“®’†‚©‚Â‘Šè“X‚É“–‚½‚Á‚½‚ç
		if (mode == Mode::MOVE&&collideWith(entity, entityNS::COLLISION_TAG::FACILITY))
		{
			changeDirection();
			customerCount++;
		}
	}
}

//UŒ‚ŠJn
void Character::startAttack(Character* character)
{
	attackTargetCharacter = nullptr;
	attackTargetCharacter = character;
	//ˆÚ“®’†‚©‚ÂUŒ‚”ÍˆÍ‚É“G‚ª‚¢‚é‚©‚Ç‚¤‚©
	if (mode == Mode::MOVE&&Distance(position, character->getPosition()) < states.attackRange)
	{
		mode = Mode::ATTACK;
	}

}

//Œü‚«‚Ì•ÏX
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

//UŒ‚ˆ—
void Character::attack(float frameTime)
{
	if (mode == Mode::ATTACK)
	{
		attackTimer.update(frameTime);
		if (attackTimer.isEnd())
		{
			//‹ßÚ‚È‚ç
			if (attackType = AttackType::PROXIMITY)
			{
				//ƒ_ƒ[ƒW‚ğ’¼Ú—^‚¦‚é
				attackTargetCharacter->damage(states.attackPower);
			}
			//‰“‹——£‚È‚ç
			if (attackType = AttackType::LONG_DISTANCE)
			{
				//UŒ‚‚ğ¶¬
			}

			attackTimer.resetTimer();
		}
	}
}

//ˆø”‚Åw’è‚µ‚½ƒ_ƒ[ƒW—Ê‚ğHp‚©‚çŒ¸‚ç‚·
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