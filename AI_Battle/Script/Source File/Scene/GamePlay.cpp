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

/*�摜�̏�����*/
void GamePlay::ImageInitialize()
{
}

/*�X�V*/
void GamePlay::update(float frameTime)
{
	//�t�F�[�h�̍X�V
	fade.update();
	facility_1->update(frameTime);
	facility_2->update(frameTime);
	formCharacterPoint1->update(frameTime,*formCharacterPoint2);
	formCharacterPoint2->update(frameTime,*formCharacterPoint1);
	characterManager.update(frameTime);
}

/*�`��*/
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



