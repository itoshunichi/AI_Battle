#include"../../Header File/Character/formCharacter.h"

FormCharacter::FormCharacter()
{

}

FormCharacter::FormCharacter(GameManager *gameManager, PlayerNum playerNum)
{
	
	this->gameManager = gameManager;
	input = gameManager->getInput();
	this->playerNum = playerNum;
	pointImage = gameManager->getImageManager()->getFormCharacterPoint_Image();
	characterCost = CharacterCostManager(gameManager, playerNum);
}

FormCharacter::~FormCharacter()
{

}

//������
void FormCharacter::initalize()
{
	if (isPlayer1())
	{
		pointPosition = vector2(300, 410);
	}
	else if (isPlayer2())
	{
		pointPosition = vector2(800, 410);
	}
	
	characterCost.initialize();
}

//�`��
void FormCharacter::draw()
{
	for each (Character* c in  formCharacters)
	{
		c->draw();
	}
	pointImage.draw();
	characterCost.draw();
}

//�X�V
void FormCharacter::update(float frameTime, FormCharacter &otherFormCharacter)
{
	pointImage.setX(pointPosition.x);
	pointImage.setY(pointPosition.y);
	for each (Character* c in  formCharacters)
	{
		c->update(frameTime);
	}
	pointMove();
	formCharacter();
	input->update(frameTime, 0);
	setCurrentRow();
	removeCharacter();
	characterCost.update(frameTime);
}

//�ړ�����
void FormCharacter::pointMove()
{
	if (isPlayer1())
	{
		pointPosition.x = Math::clamp(pointPosition.x, gameManager->getImageManager()->getFacility_Image().getWidth(), (GAME_WIDTH / 2) - pointImage.getWidth());
		pointPosition.y = Math::clamp(pointPosition.y, thirdColumnMinY, firstColumnMaxY - pointImage.getHeight());
		pointPosition += (vector2(input->getGamepadThumbLX(0, false), -input->getGamepadThumbLY(0, false))*0.5f);

	}
	else if (isPlayer2())
	{
		pointPosition.x = Math::clamp(pointPosition.x, (GAME_WIDTH / 2) + pointImage.getWidth(), GAME_WIDTH - 
			gameManager->getImageManager()->getFacility_Image().getWidth() - pointImage.getWidth());
		pointPosition.y = Math::clamp(pointPosition.y, thirdColumnMinY, firstColumnMaxY - pointImage.getHeight());
		pointPosition += (vector2(input->getGamepadThumbRX(0, false), -input->getGamepadThumbRY(0, false))*0.5f);
	}
}

//�w�肵���L�����𐶐�
void FormCharacter::formSelectCharacter(CharacterType type)
{
	Character* character = nullptr;
	if (type == CharacterType::TESTCHARACTER)
	{
		if (characterCost.getCurrentCost() < TestCharacter_COST)return;
		character = new TestCharacter(gameManager, playerNum);
	}
	else if (type == CharacterType::LONGATTACKTESTCHARACTER)
	{
		if (characterCost.getCurrentCost() < TestCharacter_COST)return;
		character = new LongAttackTestCharacter(gameManager, playerNum);
	}
	else if (type == CharacterType::TESTAIRCHARACTER)
	{
		if (characterCost.getCurrentCost() < TestCharacter_COST)return;
		character = new TestAirCharacter(gameManager, playerNum);
	}
	character->setPosition(pointPosition.x, currentRow);
	//�L�����N�^�[��������
	character->initialize();
	//���݂̃R�X�g����L�����̃R�X�g��������
	characterCost.costDecrease(character->getCost());
	//�L�������X�g�ɒǉ�
	formCharacters.push_back(character);
	//�񂲂Ƃ̃��X�g�ɒǉ�
	addColumnCharacters(character);
}

//�񂲂Ƃ̃��X�g�ɒǉ�
void FormCharacter::addColumnCharacters(Character* character)
{
	if (currentRow == 3)
	{
		firstColumnCharacters.push_back(character);
	}
	else if (currentRow == 2)
	{
		secondColumnCharacters.push_back(character);
	}
	else if (currentRow == 1)
	{
		thirdColumnCharacters.push_back(character);
	}
}

//�L�����N�^�[����
void FormCharacter::formCharacter()
{
	//1P�̏ꍇ
	if (isPlayer1())
	{
		if (input->getGamepadDPadUp(0, true))
		{
			formSelectCharacter(formCharacterTypes[0]);
		}
		if (input->getGamepadDPadRight(0, true))
		{
			formSelectCharacter(formCharacterTypes[1]);

		}
		else if (input->getGamepadDPadDown(0, true))
		{
			formSelectCharacter(formCharacterTypes[2]);
		}
		else if (input->getGamepadDPadLeft(0, true))
		{
			formSelectCharacter(formCharacterTypes[3]);
		}
	}
	//2P�̏ꍇ
	else if (isPlayer2())
	{
		if (input->getGamepadY(0, true))
		{
			formSelectCharacter(formCharacterTypes[0]);
		}
		else if (input->getGamepadB(0, true))
		{
			formSelectCharacter(formCharacterTypes[1]);
		}
		else if (input->getGamepadA(0, true))
		{
			formSelectCharacter(formCharacterTypes[2]);
		}
		if (input->getGamepadX(0, true))
		{
			formSelectCharacter(formCharacterTypes[3]);
		}
	}
}

//���݂̗�̐ݒ�
void FormCharacter::setCurrentRow()
{
	//��
	if (pointPosition.y > thirdColumnMinY && pointPosition.y < thirdColumnMaxY)
	{
		currentRow = 3;
	}
	else if (pointPosition.y>seconsColumnMinY && pointPosition.y < secondColumnMaxY)
	{
		currentRow = 2;
	}
	else if (pointPosition.y>firstColumnMinY && pointPosition.y < firstColumnMaxY)
	{
		currentRow = 1;
	}
}



//�L�����N�^�[�̍폜
void FormCharacter::removeCharacter()
{
	//���X�g����HP��0�ȉ��̃L�������폜
	formCharacters.erase(remove_if(formCharacters.begin(), formCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), formCharacters.end());
	firstColumnCharacters.erase(remove_if(firstColumnCharacters.begin(), firstColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), firstColumnCharacters.end());
	secondColumnCharacters.erase(remove_if(secondColumnCharacters.begin(), secondColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), secondColumnCharacters.end());
	thirdColumnCharacters.erase(remove_if(thirdColumnCharacters.begin(), thirdColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), thirdColumnCharacters.end());
}
