#include"../../../Header File/Character/Weapon/testWeapon.h"

TestWeapon::TestWeapon()
{

}

TestWeapon::TestWeapon(GameManager *gameManager, Vector2 targetCharacterPosition, Vector2 position)
{
	this->gameManager = gameManager;
	this->targetCharacterPosition = targetCharacterPosition;
	this->position = position;
	currentImage = this->gameManager->getImageManager()->getTestWeapon_Image();
	speed = 200;
}

TestWeapon::~TestWeapon()
{

}

void TestWeapon::initialize()
{

}

void TestWeapon::update(float frameTime)
{
	Entity::update(frameTime);
	move(frameTime);
}

void TestWeapon::draw()
{
	currentImage.draw();
}