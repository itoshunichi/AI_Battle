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
	formCharacterPoint1 = new FormCharacter(gameManager,*facility_1,1);
	formCharacterPoint2 = new FormCharacter(gameManager, *facility_2, 2);
	formCharacterPoint1->initalize();
	formCharacterPoint2->initalize();
	formCharacterPoint1->addCharacterType(CharacterType::TESTCHARACTER);
	formCharacterPoint1->addCharacterType(CharacterType::TESTCHARACTER);
	formCharacterPoint1->addCharacterType(CharacterType::TESTCHARACTER);
	formCharacterPoint1->addCharacterType(CharacterType::TESTCHARACTER);
	
	
	formCharacterPoint2->addCharacterType(CharacterType::TESTCHARACTER);
	formCharacterPoint2->addCharacterType(CharacterType::TESTCHARACTER);
	formCharacterPoint2->addCharacterType(CharacterType::TESTCHARACTER);
	formCharacterPoint2->addCharacterType(CharacterType::TESTCHARACTER);
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
	facility_1->update(frameTime);
	facility_2->update(frameTime);
	formCharacterPoint1->update(frameTime,*formCharacterPoint2);
	formCharacterPoint2->update(frameTime,*formCharacterPoint1);
	characterManager.update(frameTime);
}

/*描画*/
void GamePlay::draw()
{
	backImage.draw();
	//facility_1->draw();
	//facility_2->draw();
	formCharacterPoint1->draw();
	formCharacterPoint2->draw();
	fade.draw();
	
}

void GamePlay::collision()
{
	for each (Character* c in formCharacterPoint1->getFormCharacters())
	{
		c->myShopColiision(*facility_1, facility_1->customerCount);
		c->otherShopCollision(*facility_2, facility_2->customerCount);
	}
	for each (Character* c in formCharacterPoint2->getFormCharacters())
	{
		c->myShopColiision(*facility_1, facility_2->customerCount);
		c->otherShopCollision(*facility_2, facility_1->customerCount);
	}
	/*for (int i = 0; i < formCharacterPoint1->getFormCharacters().size(); i++)
	{
		formCharacterPoint1->getFormCharacters()[i]->myShopColiision(*facility_1, facility_1->customerCount);
		formCharacterPoint1->getFormCharacters()[i]->otherShopCollision(*facility_2, facility_2->customerCount);
	}
	for (int i = 0; i < formCharacterPoint2->getFormCharacters().size(); i++)
	{
		formCharacterPoint2->getFormCharacters()[i]->myShopColiision(*facility_2, facility_2->customerCount);
		formCharacterPoint2->getFormCharacters()[i]->otherShopCollision(*facility_1, facility_1->customerCount);
	}*/
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



