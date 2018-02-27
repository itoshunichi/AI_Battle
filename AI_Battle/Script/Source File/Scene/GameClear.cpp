#include"../../Header File/Scene/gameClear.h"

//�R���X�g���N�^
GameClear::GameClear()
{
	//input = new Input();
}

GameClear::GameClear(GameManager *gameManager)
{
	this->gameManager = gameManager;
	
}

void GameClear::initialize()
{
	this->input = gameManager->getInput();
}



void GameClear::update(float frameTime)
{
	endScene();
}

void GameClear::draw()
{
}

void GameClear::collision()
{
	
}

void GameClear::endScene()
{
	if (isEnd)return;
	//�X�y�[�X�������ꂽ��Q�[���v���C��
	if (input->wasKeyPressed(VK_SPACE))
	{
		
		isEnd = true;
	}
}



SceneMode GameClear::Next()
{
	return SceneMode::TITLE;
}


