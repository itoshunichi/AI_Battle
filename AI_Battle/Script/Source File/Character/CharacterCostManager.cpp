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

//������
void CharacterCostManager::initialize()
{
	currentCost = 5;
	costTimer = Timer(costRecoveryTime);
	
}

//�X�V
void CharacterCostManager::update(float frameTime)
{
	recoveryCost(frameTime);
	setCostIconPosition();
}

//�`��
void CharacterCostManager::draw()
{
	for (int i = 0; i < currentCost; i++)
	{
		costImages[i].draw();
	}
}

//�R�X�g�̉�
void CharacterCostManager::recoveryCost(float frameTime)
{
	//�R�X�g���ő���傫���Ȃ�Ȃ��悤��
	if (currentCost >= maxCost)return;
	costTimer.update(frameTime);
	if (costTimer.isEnd())
	{
		//�R�X�g�𑝂₷
		currentCost++;
		costTimer.resetTimer();
	}
}

void CharacterCostManager::setCostIconPosition()
{
	for (int i = 0; i < currentCost; i++)
	{
		//1P��������
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
		//2P��������
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