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
	facility_1 = new Shop(gameManager);
	facility_1->initialize();
	facility_1->setPosition(vector2(0, 0));
	facility_2 = new Shop(gameManager);
	facility_2->initialize();
	facility_2->setPosition(vector2(GAME_WIDTH - 128, 0));
	testCharacter = new TestCharacter(gameManager,1);
	testCharacter->initialize();
	testCharacter->setPosition(vector2(128, 128));
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
	facility_1->update(frameTime);
	facility_2->update(frameTime);
	testCharacter->update(frameTime);
}

/*描画*/
void GamePlay::draw()
{
	facility_1->draw();
	facility_2->draw();
	testCharacter->draw();
	fade.draw();
	
}

void GamePlay::collision()
{
	testCharacter->myShopColiision(*facility_1, facility_1->customerCount);
	testCharacter->otherShopCollision(*facility_2,facility_2->customerCount);
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



