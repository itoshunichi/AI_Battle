#ifndef _GAMEPLAY_
#define _GAMEPLAY_

#include"scene.h"
#include"../Otherwise/timer.h"
#include"../Facility/shop.h"
#include"../Character/formCharacter.h"
#include"../Character/characterManager.h"


class GamePlay:public Scene
{
private:
	Image backImage;
	Console *console;
	Shop *shop_1;
	Shop *shop_2;
	FormCharacter *formCharacterPoint1;
	FormCharacter *formCharacterPoint2;
	CharacterManager characterManager;
	
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

