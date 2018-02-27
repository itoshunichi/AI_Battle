#include "../../Header File/Default/gamemain.h"

//コンストラクタ
GameMain::GameMain()
{
	
	
}

//デストラクタ
GameMain::~GameMain()
{
	releaseAll();//すべてのグラフィックスアイテムについてonLostDevice()を読み出す
}

//ゲームを初期化
//エラー時にGameErrorをスロー
void GameMain::initialize(HWND hwnd)
{
	Game::initialize(hwnd);//GameErrorをスロー
	text.initialize(getGraphics(), 14, false, false, "Courier New");
	text.setFontColor(gameNS::FONT_COLOR);

	gameManager.initialize(this, hwnd);

    sceneManager = SceneManager(&gameManager);
	sceneManager.addScene();
	sceneManager.change(SceneMode::GAMEPLAY);
}

//すべてのゲームアイテムを更新
void GameMain::update()
{
	sceneManager.update(frameTime);

}

//人工知能
void GameMain::ai()
{
}

//衝突を処理
void GameMain::collisions()
{
	sceneManager.collision();
}

//ゲームアイテムをレンダー
void GameMain::render()
{
	
	graphics->spriteBegin();   //スプライトの描画を開始

	//title.draw();
	sceneManager.draw();

	graphics->spriteEnd();
}

//グラフィックスデバイスが消失した場合
//グラフィックスデバイスをリセット可能にするため
//予約されていたビデオメモリをすべて解放
void GameMain::releaseAll()
{
	gameManager.getImageManager()->onLostDevice();
	Game::releseAll();
	return;
}

//グラフィックスがリセットされた場合
//すべてのサーフェイスを再作成
void GameMain::resetAll()
{
	gameManager.getImageManager()->onReserDevice();
	Game::resetAll();
	return;
}