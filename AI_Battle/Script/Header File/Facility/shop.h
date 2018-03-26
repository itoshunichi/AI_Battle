#ifndef FACILITY_H_
#define FACILITY_H_

#include"../GameManager/gameManager.h"
#include"../Default/entity.h"
#include"../Character/playerNum.h"

//�X
class Shop:public Entity
{
private:
	GameManager *gameManager;
	//Image image;
	Image customerIcon;
	vector<Image>customerIcons;
	PlayerNum playerNum;
	//Vector2 position;

private:
	//�A�C�e���̃A�C�R���̈ʒu�̐ݒ�
	void setAitemIconsPosition();
	//1P���ǂ���
	bool isPlayer1(){ return playerNum == PlayerNum::PLAYER1; }
	//2P���ǂ���
	bool isPlayer2(){ return playerNum == PlayerNum::PLAYER2; }
public:
	Shop();
	Shop(GameManager *gameManager,PlayerNum playerNum);
	~Shop();
	int maxCustonerCount;
	//�q��
	int customerCount;
	void initialize();
	void update(float frameTime);
	void draw();
	void collision();
	//int getCutomerCount(){ return customerCount; }
	void setPosition(Vector2 position){ this->position = position; currentImage.setX(position.x); currentImage.setY(position.y); }
	

};

#endif