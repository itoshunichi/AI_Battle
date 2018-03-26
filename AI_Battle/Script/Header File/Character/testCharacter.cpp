#include"testCharacter.h"

TestCharacter::TestCharacter()
{

}
TestCharacter::TestCharacter(GameManager *gameManager, PlayerNum playerNum)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
	currentImage = gameManager->getImageManager()->getTestCharacter_Image();
	status = new Status_TestCharacter();
	currentHp = status->maxHp;
	status->attackRange += currentImage.getWidth();
	attackTimer = Timer(status->attackTime);
	
}

TestCharacter::~TestCharacter()
{
	
}

void TestCharacter::initialize()
{
	appearance();
	mode = Mode::MOVE;
}

void TestCharacter::update(float frameTime)
{
	Entity::update(frameTime);
	move(frameTime);
	attack(frameTime);
	dead();
}

void TestCharacter::draw()
{
	currentImage.draw();
}

