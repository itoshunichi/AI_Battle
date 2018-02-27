#ifndef _GAMEMAIN_H
#define _GAMEMAIN_H
#define WIM32_LEAN_AND_MEAN

#include"../Scene/sceneManager.h"
#include"../GameManager/gameManager.h"
#include "game.h"

//Gameクラスを継承
class GameMain :public Game
{
private:
	SceneManager sceneManager;
	TextDX text;
	GameManager gameManager;
	
public:
	//コンストラクタ
	GameMain();
	//デストラクタ
	virtual ~GameMain();
	//ゲームを初期化
	void initialize(HWND hwnd);
	void update();//Gameからの純粋仮想関数をオーバーライドする必要がある
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

	Input *getInput(){ return input; }
	
};

#endif