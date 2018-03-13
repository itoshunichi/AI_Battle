#include"testCharacter.h"

TestCharacter::TestCharacter()
{

}
TestCharacter::TestCharacter(GameManager *gameManager,Vector2 position,int playerNum)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
	this->position = position;
	currentImage = gameManager->getImageManager()->getTestCharacter_Image();
}

TestCharacter::~TestCharacter()
{

}

void TestCharacter::initialize()
{
	states.moveSpeed = 200;
	
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

