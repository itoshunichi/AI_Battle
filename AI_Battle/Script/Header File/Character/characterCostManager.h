#ifndef CHARACTERCOSTMANAGER_H_
#define CHARACTERCOSTMANAGER_H_

#include"../GameManager/gameManager.h"
#include"../Otherwise/timer.h"
#include"playerNum.h"

//コストの処理をまとめるクラス
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
	//コスト減少
	void costDecrease(int cost){ this->currentCost -= cost; }

private:
	//コスト回復
	void recoveryCost(float frameTime);
	//アイコンの位置
	void setCostIconPosition();
	//1Pかどうか
	bool isPlayer1(){ return playerNum == PlayerNum::PLAYER1; }
	//2Pかどうか
	bool isPlayer2(){ return playerNum == PlayerNum::PLAYER2; }

private:
	GameManager *gameManager;
	PlayerNum playerNum;
	//現在のコスト
	int currentCost;
	//最大コスト
	int maxCost = 10;
	//コストの画像
	Image costImage;
	vector<Image>costImages;
	//コスト用のタイマー
	Timer costTimer;
	//コスト回復の間隔
	float costRecoveryTime = 2;
};

#endif