#include"../../Header File/Character/testAirCharacter.h"

TestAirCharacter::TestAirCharacter()
{

}
TestAirCharacter::TestAirCharacter(GameManager *gameManager, PlayerNum playerNum)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
	currentImage = gameManager->getImageManager()->getTestCharacter_Image();
	status = new Status_TestCharacter();
	currentHp = status->maxHp;
	status->attackRange += currentImage.getWidth();
	attackTimer = Timer(status->attackTime);

}

TestAirCharacter::~TestAirCharacter()
{

}

void TestAirCharacter::initialize()
{
	appearance();
	mode = Mode::MOVE;
}

void TestAirCharacter::update(float frameTime)
{
	Entity::update(frameTime);
	move(frameTime);
	attack(frameTime);
	dead();
}

void TestAirCharacter::draw()
{
	currentImage.draw();
}

