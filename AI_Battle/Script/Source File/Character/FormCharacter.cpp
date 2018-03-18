#include"../../Header File/Character/formCharacter.h"

FormCharacter::FormCharacter()
{

}

FormCharacter::FormCharacter(GameManager *gameManager, Entity &myShop, int playerNum)
{
	this->gameManager = gameManager;
	input = gameManager->getInput();
	this->playerNum = playerNum;
	pointImage = gameManager->getImageManager()->getFormCharacterPoint_Image();
	this->myShop = myShop;
}

FormCharacter::~FormCharacter()
{

}

//初期化
void FormCharacter::initalize()
{
	if (playerNum == 1)
	{
		pointPosition = vector2(300, 410);
	}
	else if (playerNum == 2)
	{
		pointPosition = vector2(800, 410);
	}

}

//描画
void FormCharacter::draw()
{
	for each (Character* c in  formCharacters)
	{
		c->draw();
	}
	pointImage.draw();
}

//更新
void FormCharacter::update(float frameTime,FormCharacter &otherFormCharacter)
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
}

//移動処理
void FormCharacter::pointMove()
{
	if (playerNum == 1)
	{
		pointPosition.x = Math::clamp(pointPosition.x, myShop.getCurrentImage().getWidth(), (GAME_WIDTH / 2) - pointImage.getWidth());
		pointPosition.y = Math::clamp(pointPosition.y, 225, 550 - pointImage.getHeight());
		pointPosition += (vector2(input->getGamepadThumbLX(0, false), -input->getGamepadThumbLY(0, false))*0.5f);

	}
	else if (playerNum == 2)
	{
		pointPosition.x = Math::clamp(pointPosition.x, (GAME_WIDTH / 2) + pointImage.getWidth(), GAME_WIDTH - myShop.getCurrentImage().getWidth() - pointImage.getWidth());
		pointPosition.y = Math::clamp(pointPosition.y, 225, 550 - pointImage.getHeight());
		pointPosition += (vector2(input->getGamepadThumbRX(0, false), -input->getGamepadThumbRY(0, false))*0.5f);
	}
}

//指定したキャラを生成
void FormCharacter::formSelectCharacter(CharacterType type)
{
	Character* character = nullptr;
	if (type == CharacterType::TESTCHARACTER)
	{
		character = new TestCharacter(gameManager, formPosition(), playerNum);
	}
	else if (type == CharacterType::LONGATTACKTESTCHARACTER)
	{
		character = new LongAttackTestCharacter(gameManager, formPosition(), playerNum);
	}
	character->initialize();
	formCharacters.push_back(character);
	//列ごとのリストに追加
	addColumnCharacters(character);
}

//列ごとのリストに追加
void FormCharacter::addColumnCharacters(Character* character)
{
	if (currentRow == 1)
	{
		firstColumnCharacters.push_back(character);
	}
	else if (currentRow == 2)
	{
		secondColumnCharacters.push_back(character);
	}
	else if (currentRow == 3)
	{
		thirdColumnCharacters.push_back(character);
	}
}

//キャラクター生成
void FormCharacter::formCharacter()
{
	if (playerNum == 1)
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
	else if (playerNum == 2)
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

//現在の列の設定
void FormCharacter::setCurrentRow()
{
	//仮
	if (pointPosition.y > 225 && pointPosition.y < 325)
	{
		currentRow = 3;
	}
	else if (pointPosition.y>325 && pointPosition.y < 425)
	{
		currentRow = 2;
	}
	else if (pointPosition.y>425 && pointPosition.y < 550)
	{
		currentRow = 1;
	}
}

Vector2 FormCharacter::formPosition()
{
	if (currentRow == 3)
	{
		return vector2(pointPosition.x,325);
	}
	else if (currentRow == 2)
	{
		return vector2(pointPosition.x, 425);
	}
	else if (currentRow == 1)
	{
		return vector2(pointPosition.x, 550);
	}
}

void FormCharacter::removeCharacter()
{
	formCharacters.erase(remove_if(formCharacters.begin(), formCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), formCharacters.end());
	firstColumnCharacters.erase(remove_if(firstColumnCharacters.begin(), firstColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), firstColumnCharacters.end());
	secondColumnCharacters.erase(remove_if(secondColumnCharacters.begin(), secondColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), secondColumnCharacters.end());
	thirdColumnCharacters.erase(remove_if(thirdColumnCharacters.begin(), thirdColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), thirdColumnCharacters.end());
}