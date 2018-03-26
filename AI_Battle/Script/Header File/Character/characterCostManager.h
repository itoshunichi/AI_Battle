#ifndef CHARACTERCOSTMANAGER_H_
#define CHARACTERCOSTMANAGER_H_

#include"../GameManager/gameManager.h"
#include"../Otherwise/timer.h"
#include"playerNum.h"

//�R�X�g�̏������܂Ƃ߂�N���X
class CharacterCostManager
{
public:
	CharacterCostManager();
	CharacterCostManager(GameManager *gameManager,PlayerNum playerNum);
	~CharacterCostManager();
	void initialize();
	void update(float frameTime);
	void draw();
	int getCurrentCost(){ return currentCost; }
	//�R�X�g����
	void costDecrease(int cost){ this->currentCost -= cost; }

private:
	//�R�X�g��
	void recoveryCost(float frameTime);
	//�A�C�R���̈ʒu
	void setCostIconPosition();
	//1P���ǂ���
	bool isPlayer1(){ return playerNum == PlayerNum::PLAYER1; }
	//2P���ǂ���
	bool isPlayer2(){ return playerNum == PlayerNum::PLAYER2; }

private:
	GameManager *gameManager;
	PlayerNum playerNum;
	//���݂̃R�X�g
	int currentCost;
	//�ő�R�X�g
	int maxCost = 10;
	//�R�X�g�̉摜
	Image costImage;
	vector<Image>costImages;
	//�R�X�g�p�̃^�C�}�[
	Timer costTimer;
	//�R�X�g�񕜂̊Ԋu
	float costRecoveryTime = 2;
};

#endif