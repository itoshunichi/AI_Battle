#include"../../Header File/Character/longAttackTestCharacter.h"

LongAttackTestCharacter::LongAttackTestCharacter()
{

}

LongAttackTestCharacter::LongAttackTestCharacter(GameManager *gameManager, Vector2 position, int playerNum)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
	currentImage = gameManager->getImageManager()->getLongAttackTestCharacter_Image();
	this->position = position - vector2(0, currentImage.getHeight());
	status = new Status_LongAttackTestCharacter();
	hp = status->maxHp;
	status->attackRange += currentImage.getWidth();
	attackTimer = Timer(status->attackTime);
}

LongAttackTestCharacter::~LongAttackTestCharacter()
{

}

void LongAttackTestCharacter::initialize()
{
	appearance();
	mode = Mode::MOVE;
}

void LongAttackTestCharacter::update(float frameTime)
{
	Entity::update(frameTime);
	move(frameTime);
	attack(frameTime);
	dead();
	for each (TestWeapon* w in weapons)
	{
		w->update(frameTime);

	}
}

void LongAttackTestCharacter::draw()
{
	currentImage.draw();
	for each (TestWeapon* w in weapons)
	{
		w->draw();

	}
}

void LongAttackTestCharacter::firingWeapon()
{
	weapon = new TestWeapon(gameManager, direction, weaponFormPosition());
	weapon->initialize();
	weapons.push_back(weapon);
	
}

//武器の生成位置を設定
Vector2 LongAttackTestCharacter::weaponFormPosition()
{
	if (direction == Direction::RIGHT)
	{
		return position + vector2(currentImage.getWidth(), 0);
	}
	else if (direction == Direction::LEFT)
	{
		return position;
	}
}
