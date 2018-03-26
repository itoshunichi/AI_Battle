#include"../../Header File/Scene/gamePlay.h"
//#include"net.h"

/*�R���X�g���N�^*/
GamePlay::GamePlay()
{
}

/*�R���X�g���N�^*/
GamePlay::GamePlay(GameManager *gameManager)
{
	this->gameManager = gameManager;
	this->console = gameManager->getConsole();
}

/*������*/
void GamePlay::initialize()
{
	//�摜�̏�����
	ImageInitialize();
	//����
	input = gameManager->getInput();
	//�t�F�[�h
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

/*�摜�̏�����*/
void GamePlay::ImageInitialize()
{
}

/*�X�V*/
void GamePlay::update(float frameTime)
{
	//�t�F�[�h�̍X�V
	fade.update();
	shop_1->update(frameTime);
	shop_2->update(frameTime);
	formCharacterPoint1->update(frameTime,*formCharacterPoint2);
	formCharacterPoint2->update(frameTime,*formCharacterPoint1);
	characterManager.update(frameTime);
}

/*�`��*/
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


/*���̃V�[��*/
SceneMode GamePlay::Next()
{

	return SceneMode::GAMEOVER;
}



void  GamePlay::endScene()
{

	//�t�F�[�h�A�E�g���J�n
	//fade.fadeOutStart();
	//�t�F�[�h���I�������
	if (fade.getIsEnd())
	{
		//�V�[���I��
		isEnd = true;
	}
}



