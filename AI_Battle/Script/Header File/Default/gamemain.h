#ifndef _GAMEMAIN_H
#define _GAMEMAIN_H
#define WIM32_LEAN_AND_MEAN

#include"../Scene/sceneManager.h"
#include"../GameManager/gameManager.h"
#include "game.h"

//Game�N���X���p��
class GameMain :public Game
{
private:
	SceneManager sceneManager;
	TextDX text;
	GameManager gameManager;
	
public:
	//�R���X�g���N�^
	GameMain();
	//�f�X�g���N�^
	virtual ~GameMain();
	//�Q�[����������
	void initialize(HWND hwnd);
	void update();//Game����̏������z�֐����I�[�o�[���C�h����K�v������
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

	Input *getInput(){ return input; }
	
};

#endif