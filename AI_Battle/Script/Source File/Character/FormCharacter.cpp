#include"../../Header File/Character/formCharacterPoint.h"

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
}

FormCharacter::~FormCharacter()
{

}

//初期化
void FormCharacter::initalize()
{
	if (playerNum == 1)
	{
		position = vector2(300, 400);
	}
	else if (playerNum == 2)
	{
		position = vector2(800, 400);
	}

}

//描画
void FormCharacter::draw()
{
	for (int i = 0; i < formCharacters.size(); i++)
	{
		formCharacters[i]->draw();
	}
	image.draw();
}

//更新
void FormCharacter::update(float frameTime)
{
	image.setX(position.x);
	image.setY(position.y);
	for (int i = 0; i < formCharacters.size(); i++)
	{
		formCharacters[i]->update(frameTime);
	}
	move();
	formCharacter();
	input->update(frameTime, 0);
}

//移動処理
void FormCharacter::move()
{
	if (playerNum == 1)
	{
		position.x = Math::clamp(position.x, myShop.getCurrentImage().getWidth(), (GAME_WIDTH / 2) - image.getWidth());
		position.y = Math::clamp(position.y, 0, GAME_HEIGHT - image.getHeight());
		position += (vector2(input->getGamepadThumbLX(0, false), -input->getGamepadThumbLY(0, false))*0.5f);

	}
	else if (playerNum == 2)
	{
		position.x = Math::clamp(position.x, (GAME_WIDTH / 2) + image.getWidth(), GAME_WIDTH - myShop.getCurrentImage().getWidth() - image.getWidth());
		position.y = Math::clamp(position.y, 0, GAME_HEIGHT - image.getHeight());
		position += (vector2(input->getGamepadThumbRX(0, false), -input->getGamepadThumbRY(0, false))*0.5f);
	}
}

void FormCharacter::formSelectCharacter(CharacterType type)
{
	if (type == CharacterType::TESTCHARACTER)
	{
		formCharacters.push_back(new TestCharacter(gameManager, position,playerNum));
		formCharacters[formCharacters.size() - 1]->initialize();
		
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