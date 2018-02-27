#include"../../Header File/Scene/gameOver.h"

//コンストラクタ
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
	//スペースが押されたらゲームプレイへ
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