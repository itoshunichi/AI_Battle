//Windowアプリケーションの開始点

#define _CRTDBG_MAP_ALLOC 
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<stdlib.h>
#include<crtdbg.h>"
#include"../../Header File/Default/gamemain.h"

//関数プロトタイプ
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

//グローバル変数
HWND hwnd = NULL;
GameMain *game = NULL;



int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	//デバックビルドの場合、メモリリークをチェック
#if defined(DEBUG)|defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	MSG msg;

	//Gameオブジェクトを作成
	game = new GameMain;

	//ウィンドウを作成
	if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
		return 1;
	try
	{
		game->initialize(hwnd);

		//メインのメッセージループ
		int done = 0;
		while (!done)
		{
			//PeekMessageはWindowsメッセージがあるかをテストする非ブロックメソッド
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				//終了メッセージを検知
				if (msg.message == WM_QUIT)done = 1;
				//メッセージをデコードしてWinProに渡す
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				game->run(hwnd);//ゲームループを実行
		}
		SAFE_DELETE(game);//終了の前にメモリを解放
		return msg.wParam;
	}
	catch (const GameError &err)
	{
		game->deleteAll();
		DestroyWindow(hwnd);
		MessageBox(NULL, err.getMessage(), "Error", MB_OK);
	}
	catch (...)
	{
		game->deleteAll();
		DestroyWindow(hwnd);
		MessageBox(NULL, "Unknown error occyrred in game.",
			"Error", MB_OK);
	}
	SAFE_DELETE(game);//終了の前にメモリを解放

	return 0;



}

//ウィンドウイベントコールバック関数
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return (game->messageHandler(hWnd, msg, wParam, lParam));
}

bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;


	//ウィンドウクラスの構造体をメインウィンドウを記述するパラメータで設定
	wcx.cbSize = sizeof(wcx);   //構造体のサイズ
	wcx.style = CS_HREDRAW | CS_VREDRAW; //ウィンドウサイズ変更時に再描画
	wcx.lpfnWndProc = WinProc; //ウィンドウプロシージャを指す
	wcx.cbClsExtra = 0; //拡張クラスメモリ無し
	wcx.cbWndExtra = 0; //拡張ウィンドウメモリ無し
	wcx.hInstance = hInstance;//インスタンスへのハンドル
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//事前定義されている矢印カーソル
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //背景ブラシ
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME; //ウィンドウクラスの名前
	wcx.hIconSm = NULL;//小さいアイコン

	//ウィンドウクラスを登録
	//エラー時,RegisterClassExは０に戻す
	if (RegisterClassEx(&wcx) == 0)    //エラーの場合
		return false;

	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	//ウィンドウを作成
	hwnd = CreateWindow(
		CLASS_NAME,          //ウィンドウクラスの名前
		GAME_TITLE,           //タイトルバーのテキスト
		style, //ウィンドウのスタイル
		CW_USEDEFAULT,       //ウィンドウの水平位置のデフォルト
		CW_USEDEFAULT,       //ウィンドウの垂直位置のデフォルト
		GAME_WIDTH,        //ウィンドウの幅
		GAME_HEIGHT,       //ウィンドウの高さ
		(HWND)NULL,          //親ウィンドウ無し
		(HMENU)NULL,         //メニュー無し
		hInstance,           //アプリケーションインスタンスへのハンドル
		(LPVOID)NULL         //ウィンドウパラメータ無し
		);

	//ウィンドウの作成でエラーが発生した場合
	if (!hwnd)return false;

	if (!FULLSCREEN)             // if window
	{
		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);   // get size of client area of window
		MoveWindow(hwnd,
			0,                                           // Left
			0,                                           // Top
			GAME_WIDTH + (GAME_WIDTH - clientRect.right),    // Right
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), // Bottom
			TRUE);                                       // Repaint the window
	}

	//ウィンドウを表示
	ShowWindow(hwnd, nCmdShow);
	
	return true;

}