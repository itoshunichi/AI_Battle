#include"../../Header File/Character/formCharacter.h"

FormCharacter::FormCharacter()
{

}

FormCharacter::FormCharacter(GameManager *gameManager, Entity &myShop, int playerNum)
{
	this->gameManager = gameManager;
	input = gameManager->getInput();
	this->playerNum = playerNum;
	image = gameManager->getImageManager()->getFormCharacterPoint_Image();
	this->myShop = myShop;
	//this->otherFormCharacter = otherFormCharacter;
}

FormCharacter::~FormCharacter()
{

}

//初期化
void FormCharacter::initalize()
{
	if (playerNum == 1)
	{
		position = vector2(300, 410);
	}
	else if (playerNum == 2)
	{
		position = vector2(800, 410);
	}

}

//描画
void FormCharacter::draw()
{
	for each (Character* c in  formCharacters)
	{
		c->draw();
	}
	/*for (int i = 0; i < formCharacters.size(); i++)
	{
		formCharacters[i]->draw();
	}*/
	image.draw();
}

//更新
void FormCharacter::update(float frameTime,FormCharacter &otherFormCharacter)
{
	image.setX(position.x);
	image.setY(position.y);
	for each (Character* c in  formCharacters)
	{
		c->update(frameTime);
	}
	/*for (int i = 0; i < formCharacters.size(); i++)
	{
		formCharacters[i]->update(frameTime);
	}*/
	move();
	formCharacter();
	input->update(frameTime, 0);
	setCurrentRow();
	removeCharacter();
}

//移動処理
void FormCharacter::move()
{
	if (playerNum == 1)
	{
		position.x = Math::clamp(position.x, myShop.getCurrentImage().getWidth(), (GAME_WIDTH / 2) - image.getWidth());
		position.y = Math::clamp(position.y, 400, 650 - image.getHeight());
		position += (vector2(input->getGamepadThumbLX(0, false), -input->getGamepadThumbLY(0, false))*0.5f);

	}
	else if (playerNum == 2)
	{
		position.x = Math::clamp(position.x, (GAME_WIDTH / 2) + image.getWidth(), GAME_WIDTH - myShop.getCurrentImage().getWidth() - image.getWidth());
		position.y = Math::clamp(position.y, 400, 650 - image.getHeight());
		position += (vector2(input->getGamepadThumbRX(0, false), -input->getGamepadThumbRY(0, false))*0.5f);
	}
}

//指定したキャラを生成
void FormCharacter::formSelectCharacter(CharacterType type)
{
	Character* character = nullptr;
	if (type == CharacterType::TESTCHARACTER)
	{
		character = new TestCharacter(gameManager, formPosition(), playerNum, currentRow);
		//formCharacters.push_back(new TestCharacter(gameManager, formPosition(), playerNum, currentRow));
	}
	character->initialize();
	formCharacters.push_back(character);
	//リストに追加
	//formCharacters.push_back(character);
	//キャラを初期化
	//formCharacters[formCharacters.size()-1]->initialize();
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
	if (position.y > 400 && position.y < 475)
	{
		currentRow = 3;
	}
	else if (position.y>475 && position.y < 550)
	{
		currentRow = 2;
	}
	else if (position.y>550 && position.y < 650)
	{
		currentRow = 1;
	}
}

Vector2 FormCharacter::formPosition()
{
	if (currentRow == 3)
	{
		return vector2(position.x, 475);
	}
	else if (currentRow == 2)
	{
		return vector2(position.x, 550);
	}
	else if (currentRow == 1)
	{
		return vector2(position.x, 650);
	}
}

void FormCharacter::removeCharacter()
{
	formCharacters.erase(remove_if(formCharacters.begin(), formCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), formCharacters.end());
	firstColumnCharacters.erase(remove_if(firstColumnCharacters.begin(), firstColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), firstColumnCharacters.end());
	secondColumnCharacters.erase(remove_if(secondColumnCharacters.begin(), secondColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), secondColumnCharacters.end());
	thirdColumnCharacters.erase(remove_if(thirdColumnCharacters.begin(), thirdColumnCharacters.end(), ([](Character* c){return c->getHp() <= 0; })), thirdColumnCharacters.end());
}