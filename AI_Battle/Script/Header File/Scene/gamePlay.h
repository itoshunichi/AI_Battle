#ifndef _GAMEPLAY_
#define _GAMEPLAY_

#include"scene.h"
#include"../Otherwise/timer.h"
#include"../Facility/shop.h"
#include"../Character/testCharacter.h"


class GamePlay:public Scene
{
private:
	Console *console;
	Shop *facility_1;
	Shop *facility_2;
	TestCharacter *testCharacter;
	
public:
	//コンストラクタ
	GamePlay();
	GamePlay(GameManager *gameManager);
	//描画
	void draw();
	//初期化
	void initialize();
	//更新
	void update(float frameTime);
	//次のシーン
	SceneMode Next();
	//シーン終了処理
	void endScene();
	//あたり判定
	void collision();

private:
	//画像の初期化
	void ImageInitialize();

};

#endif

