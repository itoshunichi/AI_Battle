#ifndef _GAMEPLAY_
#define _GAMEPLAY_

#include"scene.h"
#include"../Otherwise/timer.h"


class GamePlay:public Scene
{
private:
	Console *console;
public:
	//�R���X�g���N�^
	GamePlay();
	GamePlay(GameManager *gameManager);
	//�`��
	void draw();
	//������
	void initialize();
	//�X�V
	void update(float frameTime);
	//���̃V�[��
	SceneMode Next();
	//�V�[���I������
	void endScene();
	//�����蔻��
	void collision();

private:
	//�摜�̏�����
	void ImageInitialize();

};

#endif

