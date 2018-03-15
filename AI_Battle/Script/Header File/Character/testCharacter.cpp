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
	states.attackRange = currentImage.getWidth();
	states.attackPower = 10;
	states.hp = 30;
	states.attackTime = 1;
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
	attack(frameTime);
	dead();
}

void TestCharacter::draw()
{
	currentImage.draw();
}

