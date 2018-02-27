#ifndef CONSOLE_H
#define CONSOLE_H
#define WIN32_LEAN_AND_MEAN

#include<string>
#include<deque>
#include"constants.h"
#include"TextDX.h"
#include"graphics.h"
#include"Input.h"

namespace consoleNS
{
	const UINT WIDTH = 500;//コンソールの幅
	const UINT HEIGHT = 400;//コンソールの高さ
	//コンソールの左上隅の画面位置。
	const UINT X = 5;
	const UINT Y = 5;

	const UINT MARGIN = 4;//コンソールの端からテキストまでの余白
	const char FONT[] = "Courier New";//コンソールのテキストに使用するフォント
	const int FONT_HEIGHT = 14;//コンソールのフォントのデフォルトの高さ
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;//コンソールのデフォルトの色
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(0, 0, 0, 5); //コンソールの背景の色。(半透明のグレー)
	const int MAX_LINES = 256;//テキストバッファ内の表示可能なテキストの最大行数
}

class Console
{
private:
	Graphics *graphics;
	Input *input;
	TextDX dxFont;
	float x, y;
	int rows;
	std::string commantStr;
	std::string inputStr;
	std::deque<std::string>text;
	RECT  textRect;
	COLOR_ARGB fontColor;
	COLOR_ARGB backColor;
	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;
	int scrollAmount;
	bool initialized;
	bool visible;

public:
	Console();//コンストラクタ
	virtual ~Console();//デストラクタ
	//コンソールを初期化
	bool initialize(Graphics *g, Input *in);
	//コンソールをゲーム画面に描画
	const void draw();
	//コンソールの表示/非表示を制御するプロパティを反転
	void shoeHide();
	//表示/非表示を制御するプロパティの現在の状態を戻します
	bool getVisible(){ return visible; }
	//コンソールを表示します
	void show(){ visible = true; }
	//コンソールを非表示にする
	void hide(){ visible = false; }
	//コンソールディスプレイにテキスト文字列を追加します
	void print(const std::string &str);
	//シングルキーのコンソールコマンドを処理
	std::string getCommand();
	//コンソールの入力テキストを戻す
	std::string getInput(){ inputStr = ""; }
	//コンソールの入力テキストをクリアします
	void clearInput(){ inputStr = ""; }

	void onLostDevice();
	void onResetDevice();
};

#endif