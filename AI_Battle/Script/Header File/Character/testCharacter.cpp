#include"testCharacter.h"

TestCharacter::TestCharacter()
{

}
TestCharacter::TestCharacter(GameManager *gameManager, Vector2 position, int playerNum)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
	currentImage = gameManager->getImageManager()->getTestCharacter_Image();
	this->position = position - vector2(0, currentImage.getHeight());
	status = new Status_TestCharacter();
	hp = status->maxHp;
	status->attackRange += currentImage.getWidth();
	attackTimer = Timer(status->attackTime);
}

TestCharacter::~TestCharacter()
{
	
}

void TestCharacter::initialize()
{
	//states.moveSpeed = 200;
	
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

