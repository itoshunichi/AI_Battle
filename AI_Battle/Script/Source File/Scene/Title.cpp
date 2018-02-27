#include"../../Header File/Scene/title.h"

//コンストラクタ
Title::Title()
{

}

/*コンストラクタ*/
Title::Title(GameManager *gameManager)
{
	this->gameManager = gameManager;
}
	

/*初期化*/
void Title::initialize()
{
	//入力
	input = gameManager->getInput();
	//フェード
	fade = Fade(gameManager->getImageManager());
	fade.initialize();
	isEnd = false;

}


/*更新*/
void Title::update(float frameTime)
{
	fade.update();
	endScene();
	
}

/*シーン終了処理*/
void Title::endScene()
{
	if (isEnd)return;
	//スペースが押されたらフェード開始
	if (input->isKeyTrigger(VK_SPACE))
	{
		fade.fadeOutStart();
	}
	//フェードが終わったらシーンを終了させる
	if (fade.getIsEnd())
	{
		isEnd = true;

	}

}

/*描画*/
void Title::draw()
{
	fade.draw();
}
void Title::collision()
{

}

/*次のシーン*/
SceneMode Title::Next()
{
	return SceneMode::GAMEPLAY;
}

