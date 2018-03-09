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
	testCharacter = new TestCharacter(gameManager,1);
	testCharacter->initialize();
	testCharacter->setPosition(vector2(128, 128));
	isEnd = false;

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
	testCharacter->update(frameTime);
}

/*�`��*/
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



