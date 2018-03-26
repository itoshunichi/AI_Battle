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
	shop_1 = new Shop(gameManager,PlayerNum::PLAYER1);
	shop_1->initialize();
	shop_2 = new Shop(gameManager,PlayerNum::PLAYER2);
	shop_2->initialize();
	formCharacterPoint1 = new FormCharacter(gameManager,PlayerNum::PLAYER1);
	formCharacterPoint2 = new FormCharacter(gameManager, PlayerNum::PLAYER2);
	formCharacterPoint1->initalize();
	formCharacterPoint2->initalize();
	formCharacterPoint1->addFormCharacterType(CharacterType::TESTCHARACTER);
	formCharacterPoint1->addFormCharacterType(CharacterType::LONGATTACKTESTCHARACTER);
	formCharacterPoint1->addFormCharacterType(CharacterType::TESTAIRCHARACTER);
	formCharacterPoint1->addFormCharacterType(CharacterType::TESTCHARACTER);
	
	
	formCharacterPoint2->addFormCharacterType(CharacterType::TESTCHARACTER);
	formCharacterPoint2->addFormCharacterType(CharacterType::LONGATTACKTESTCHARACTER);
	formCharacterPoint2->addFormCharacterType(CharacterType::TESTAIRCHARACTER);
	formCharacterPoint2->addFormCharacterType(CharacterType::TESTCHARACTER);
	isEnd = false;
	backImage = gameManager->getImageManager()->getBackGround_Image();

	characterManager = CharacterManager(formCharacterPoint1, formCharacterPoint2);

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
	shop_1->update(frameTime);
	shop_2->update(frameTime);
	formCharacterPoint1->update(frameTime,*formCharacterPoint2);
	formCharacterPoint2->update(frameTime,*formCharacterPoint1);
	characterManager.update(frameTime);
}

/*描画*/
void GamePlay::draw()
{
	backImage.draw();
	shop_1->draw();
	shop_2->draw();
	formCharacterPoint1->draw();
	formCharacterPoint2->draw();
	fade.draw();
	
}

void GamePlay::collision()
{
	for each (Character* c in formCharacterPoint1->getFormCharacters())
	{
		c->myShopColiision(*shop_1, shop_1->customerCount);
		c->otherShopCollision(*shop_2, shop_2->customerCount);
	}
	for each (Character* c in formCharacterPoint2->getFormCharacters())
	{
		c->myShopColiision(*shop_2, shop_2->customerCount);
		c->otherShopCollision(*shop_1, shop_1->customerCount);
	}

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



