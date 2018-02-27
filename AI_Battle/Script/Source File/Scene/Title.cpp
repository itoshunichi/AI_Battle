#include"../../Header File/Scene/title.h"

//�R���X�g���N�^
Title::Title()
{

}

/*�R���X�g���N�^*/
Title::Title(GameManager *gameManager)
{
	this->gameManager = gameManager;
}
	

/*������*/
void Title::initialize()
{
	//����
	input = gameManager->getInput();
	//�t�F�[�h
	fade = Fade(gameManager->getImageManager());
	fade.initialize();
	isEnd = false;

}


/*�X�V*/
void Title::update(float frameTime)
{
	fade.update();
	endScene();
	
}

/*�V�[���I������*/
void Title::endScene()
{
	if (isEnd)return;
	//�X�y�[�X�������ꂽ��t�F�[�h�J�n
	if (input->isKeyTrigger(VK_SPACE))
	{
		fade.fadeOutStart();
	}
	//�t�F�[�h���I�������V�[�����I��������
	if (fade.getIsEnd())
	{
		isEnd = true;

	}

}

/*�`��*/
void Title::draw()
{
	fade.draw();
}
void Title::collision()
{

}

/*���̃V�[��*/
SceneMode Title::Next()
{
	return SceneMode::GAMEPLAY;
}

