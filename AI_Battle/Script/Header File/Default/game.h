#ifndef _GAME_H  //このファイルが複数の箇所でインクルードされる場合に
#define _GAME_H //多重に定義されることを防ぎます
#define WIM32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include<Windows.h>
#include<mmsystem.h>
#include"graphics.h"
#include"constants.h"
#include"gameError.h"
#include"TextDX.h"
#include"console.h"
#include<iostream>
#include<algorithm>
#include <functional>
#include"../Otherwise/vector2.h"



namespace gameNS
{
	const char FONT[] = "Courier New";   //フォント
	const int POINT_SIZE = 14;  //ポイントサイズ
	const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 255, 255);//白
}

class Game
{
protected:
	//共通のゲームプロパティ
	Graphics *graphics; //Graphicsへのポインタ
	Input *input; //Inputへのポインタ
	HWND hwnd; //ウィンドウハンドル
	HRESULT hr; //標準の戻り型
	LARGE_INTEGER timeStart; //パフォーマンスカウンターの開始値
	LARGE_INTEGER timeEnd; //パフォーマンスカウンターの終了値
	LARGE_INTEGER timerFreq; //パフォーマンスカウンターの周波数
	float frameTime; //最後のフレームに要した時間
	float fps;   //フレームレート(１秒あたりのフレーム数)
	TextDX dxFont;//フレームレート用のDirectXフォント
	bool fpsOn;   //trueの場合フレームレートを表示
	DWORD sleepTime; //フレーム間でスリープする時間
	bool paused;    //ゲームが一時停止されている場合
	bool initialized;
	//Audio *audio; //Audioへのポイン
	Console *console;
	std::string  command;

public:
	//コンストラクタ
	Game();
	//デストラクタ
	~Game();
	//メンバー関数
	//Windowsメッセージハンドラ
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//ゲームを初期化
	//実行前:hwndはウィンドウへのハンドル
	virtual void initialize(HWND hwnd);
	//WinMain内のメインメッセージループでrunを繰り返し呼び出す
	virtual void run(HWND);
	//グラフィックスデバイスが消失したときに呼び出す
	//グラフィックスデバイスをリセット可能にするため、
	//予約されていたビデオメモリをすべて解放
	virtual void releseAll();
	//すべてのサーフェイスを再作成し、すべてのエンティティをリセット
	virtual void resetAll();
	//予約されていたメモリをすべて削除
	virtual void deleteAll();
	//ゲームアイテムをレンダー
	virtual void renderGame();
	//消失したグラフィックスデバイスを処理
	virtual void handleLostGraphicsDevice();

	void setDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	//Graphicsへのポインタを戻す
	Graphics* getGraphics(){ return graphics; }
	//Inputへのポインタを戻す
	Input* getInput(){ return input; }
	//ゲームを終了
	void exitGame(){ PostMessage(hwnd, WM_DESTROY, 0, 0); }
	//純粋仮想関数の宣言
	//これらの関数は、Gameを継承するクラス内で記述する必要があります
	//ゲームアイテムを更新
	virtual void update() = 0;
	//AI計算を実行
	virtual void ai() = 0;
	//衝突をチェック
	virtual void collisions() = 0;
	//グラフィックスをレンダー
	//graphics->spriteBegin();を呼び出す
	//スプライトを描画
	//graphics->spriteEnd();を呼び出す
	virtual void render() = 0;

	//Audio* getAudio()       { return audio; }
	virtual void consoleCommand();//コンソールコマンドを処理

	HWND Hwnd(){ return hwnd; }

};

#endif