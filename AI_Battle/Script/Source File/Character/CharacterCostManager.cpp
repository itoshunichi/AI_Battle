#include"../../Header File/Character/characterCostManager.h"

CharacterCostManager::CharacterCostManager()
{

}

CharacterCostManager::CharacterCostManager(GameManager *gameManager,PlayerNum playerNum)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
	costImage = gameManager->getImageManager()->getHpImage();
	for (int i = 0; i < maxCost; i++)
	{
		costImages.push_back(costImage);
	}
	costTimer = Timer(costRecoveryTime);
}

CharacterCostManager::~CharacterCostManager()
{

}

//初期化
void CharacterCostManager::initialize()
{
	currentCost = 5;
	costTimer = Timer(costRecoveryTime);
	
}

//更新
void CharacterCostManager::update(float frameTime)
{
	recoveryCost(frameTime);
	setCostIconPosition();
}

//描画
void CharacterCostManager::draw()
{
	for (int i = 0; i < currentCost; i++)
	{
		costImages[i].draw();
	}
}

//コストの回復
void CharacterCostManager::recoveryCost(float frameTime)
{
	//コストが最大より大きくならないように
	if (currentCost >= maxCost)return;
	costTimer.update(frameTime);
	if (costTimer.isEnd())
	{
		//コストを増やす
		currentCost++;
		costTimer.resetTimer();
	}
}

void CharacterCostManager::setCostIconPosition()
{
	for (int i = 0; i < currentCost; i++)
	{
		//1Pだったら
		if (isPlayer1())
		{
			if (i < 5)
			{
				costImages[i].setX(i*costImage.getWidth());
				costImages[i].setY(GAME_HEIGHT - (costImage.getHeight() * 2));
			}
			else if (i>4)
			{
				costImages[i].setX(((i - 5)*costImage.getWidth()));
				costImages[i].setY(GAME_HEIGHT - (costImage.getHeight()));
			}
		}
		//2Pだったら
		else if (isPlayer2())
		{
			if (i < 5)
			{
				costImages[i].setX((GAME_WIDTH - (costImage.getWidth() * 5)) + (i*costImage.getWidth()));
				costImages[i].setY(GAME_HEIGHT - (costImage.getHeight() * 2));
			}
			else if (i>4)
			{
				costImages[i].setX((GAME_WIDTH - (costImage.getWidth() * 5)) + ((i - 5)*costImage.getWidth()));
				costImages[i].setY(GAME_HEIGHT - (costImage.getHeight()));
			}
		}
	}
}