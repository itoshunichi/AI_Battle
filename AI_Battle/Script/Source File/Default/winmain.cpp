//Window�A�v���P�[�V�����̊J�n�_

#define _CRTDBG_MAP_ALLOC 
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<stdlib.h>
#include<crtdbg.h>"
#include"../../Header File/Default/gamemain.h"

//�֐��v���g�^�C�v
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

//�O���[�o���ϐ�
HWND hwnd = NULL;
GameMain *game = NULL;



int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	//�f�o�b�N�r���h�̏ꍇ�A���������[�N���`�F�b�N
#if defined(DEBUG)|defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	MSG msg;

	//Game�I�u�W�F�N�g���쐬
	game = new GameMain;

	//�E�B���h�E���쐬
	if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
		return 1;
	try
	{
		game->initialize(hwnd);

		//���C���̃��b�Z�[�W���[�v
		int done = 0;
		while (!done)
		{
			//PeekMessage��Windows���b�Z�[�W�����邩���e�X�g�����u���b�N���\�b�h
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				//�I�����b�Z�[�W�����m
				if (msg.message == WM_QUIT)done = 1;
				//���b�Z�[�W���f�R�[�h����WinPro�ɓn��
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				game->run(hwnd);//�Q�[�����[�v�����s
		}
		SAFE_DELETE(game);//�I���̑O�Ƀ����������
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
	SAFE_DELETE(game);//�I���̑O�Ƀ����������

	return 0;



}

//�E�B���h�E�C�x���g�R�[���o�b�N�֐�
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return (game->messageHandler(hWnd, msg, wParam, lParam));
}

bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;


	//�E�B���h�E�N���X�̍\���̂����C���E�B���h�E���L�q����p�����[�^�Őݒ�
	wcx.cbSize = sizeof(wcx);   //�\���̂̃T�C�Y
	wcx.style = CS_HREDRAW | CS_VREDRAW; //�E�B���h�E�T�C�Y�ύX���ɍĕ`��
	wcx.lpfnWndProc = WinProc; //�E�B���h�E�v���V�[�W�����w��
	wcx.cbClsExtra = 0; //�g���N���X����������
	wcx.cbWndExtra = 0; //�g���E�B���h�E����������
	wcx.hInstance = hInstance;//�C���X�^���X�ւ̃n���h��
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//���O��`����Ă�����J�[�\��
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //�w�i�u���V
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME; //�E�B���h�E�N���X�̖��O
	wcx.hIconSm = NULL;//�������A�C�R��

	//�E�B���h�E�N���X��o�^
	//�G���[��,RegisterClassEx�͂O�ɖ߂�
	if (RegisterClassEx(&wcx) == 0)    //�G���[�̏ꍇ
		return false;

	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	//�E�B���h�E���쐬
	hwnd = CreateWindow(
		CLASS_NAME,          //�E�B���h�E�N���X�̖��O
		GAME_TITLE,           //�^�C�g���o�[�̃e�L�X�g
		style, //�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,       //�E�B���h�E�̐����ʒu�̃f�t�H���g
		CW_USEDEFAULT,       //�E�B���h�E�̐����ʒu�̃f�t�H���g
		GAME_WIDTH,        //�E�B���h�E�̕�
		GAME_HEIGHT,       //�E�B���h�E�̍���
		(HWND)NULL,          //�e�E�B���h�E����
		(HMENU)NULL,         //���j���[����
		hInstance,           //�A�v���P�[�V�����C���X�^���X�ւ̃n���h��
		(LPVOID)NULL         //�E�B���h�E�p�����[�^����
		);

	//�E�B���h�E�̍쐬�ŃG���[�����������ꍇ
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

	//�E�B���h�E��\��
	ShowWindow(hwnd, nCmdShow);
	
	return true;

}