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
	//player.initialize();
	//player2.initialize();
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

}

/*�`��*/
void GamePlay::draw()
{
	fade.draw();
}

void GamePlay::collision()
{
	
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



