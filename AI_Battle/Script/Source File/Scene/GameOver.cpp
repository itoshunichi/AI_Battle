#include"../../Header File/Scene/gameOver.h"

//�R���X�g���N�^
GameOver::GameOver()
{

}

GameOver::GameOver(GameManager *gameManager)
{
	this->gameManager = gameManager;

}


void GameOver::initialize()
{

	this->input = gameManager->getInput();
	isEnd = false;
	fade.initialize();
}

void GameOver::update(float frameTime)
{
	fade.update();
	endScene();
}

void GameOver::draw()
{
	fade.draw();
}

void GameOver::collision()
{

}

void GameOver::endScene()
{
	if (isEnd)return;
	//�X�y�[�X�������ꂽ��Q�[���v���C��
	if (input->isKeyTrigger(VK_SPACE))
	{
		fade.fadeOutStart();
	}

	if (fade.getIsEnd())
	{
		isEnd = true;
	}
}



SceneMode GameOver::Next()
{
	return SceneMode::TITLE;
}