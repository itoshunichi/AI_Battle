#include"testCharacter.h"

TestCharacter::TestCharacter()
{

}
TestCharacter::TestCharacter(GameManager *gameManager, Vector2 position, int playerNum, int currentRow)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
	this->currentRow = currentRow;
	currentImage = gameManager->getImageManager()->getTestCharacter_Image();
	this->position = position - vector2(0, currentImage.getHeight());
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

