#include"testCharacter.h"

TestCharacter::TestCharacter()
{

}
TestCharacter::TestCharacter(GameManager *gameManager,int playerNum)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
}

TestCharacter::~TestCharacter()
{

}

void TestCharacter::initialize()
{
	states.moveSpeed = 200;
	currentImage = gameManager->getImageManager()->getTestCharacter_Image();
	appearance();
	mode = Mode::MOVE;
	//position = vector2(0, 0);
}

void TestCharacter::update(float frameTime)
{
	Entity::update(frameTime);
	move(frameTime);
}

void TestCharacter::draw()
{
	currentImage.draw();
}

