#include"../../Header File/Scene/gamePlay.h"
//#include"net.h"

/*コンストラクタ*/
GamePlay::GamePlay()
{
}

/*コンストラクタ*/
GamePlay::GamePlay(GameManager *gameManager)
{
	this->gameManager = gameManager;
	this->console = gameManager->getConsole();
}

/*初期化*/
void GamePlay::initialize()
{
	//画像の初期化
	ImageInitialize();
	//入力
	input = gameManager->getInput();
	//フェード
	fade = Fade(gameManager->getImageManager());
	fade.initialize();
	//player.initialize();
	//player2.initialize();
	isEnd = false;

}

/*画像の初期化*/
void GamePlay::ImageInitialize()
{
}

/*更新*/
void GamePlay::update(float frameTime)
{
	//フェードの更新
	fade.update();

}

/*描画*/
void GamePlay::draw()
{
	fade.draw();
}

void GamePlay::collision()
{
	
}


/*次のシーン*/
SceneMode GamePlay::Next()
{

	return SceneMode::GAMEOVER;
}



void  GamePlay::endScene()
{

	//フェードアウトを開始
	//fade.fadeOutStart();
	//フェードが終わったら
	if (fade.getIsEnd())
	{
		//シーン終了
		isEnd = true;
	}
}



