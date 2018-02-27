#ifndef _GAME_H  //���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ��
#define _GAME_H //���d�ɒ�`����邱�Ƃ�h���܂�
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
	const char FONT[] = "Courier New";   //�t�H���g
	const int POINT_SIZE = 14;  //�|�C���g�T�C�Y
	const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 255, 255);//��
}

class Game
{
protected:
	//���ʂ̃Q�[���v���p�e�B
	Graphics *graphics; //Graphics�ւ̃|�C���^
	Input *input; //Input�ւ̃|�C���^
	HWND hwnd; //�E�B���h�E�n���h��
	HRESULT hr; //�W���̖߂�^
	LARGE_INTEGER timeStart; //�p�t�H�[�}���X�J�E���^�[�̊J�n�l
	LARGE_INTEGER timeEnd; //�p�t�H�[�}���X�J�E���^�[�̏I���l
	LARGE_INTEGER timerFreq; //�p�t�H�[�}���X�J�E���^�[�̎��g��
	float frameTime; //�Ō�̃t���[���ɗv��������
	float fps;   //�t���[�����[�g(�P�b������̃t���[����)
	TextDX dxFont;//�t���[�����[�g�p��DirectX�t�H���g
	bool fpsOn;   //true�̏ꍇ�t���[�����[�g��\��
	DWORD sleepTime; //�t���[���ԂŃX���[�v���鎞��
	bool paused;    //�Q�[�����ꎞ��~����Ă���ꍇ
	bool initialized;
	//Audio *audio; //Audio�ւ̃|�C��
	Console *console;
	std::string  command;

public:
	//�R���X�g���N�^
	Game();
	//�f�X�g���N�^
	~Game();
	//�����o�[�֐�
	//Windows���b�Z�[�W�n���h��
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//�Q�[����������
	//���s�O:hwnd�̓E�B���h�E�ւ̃n���h��
	virtual void initialize(HWND hwnd);
	//WinMain���̃��C�����b�Z�[�W���[�v��run���J��Ԃ��Ăяo��
	virtual void run(HWND);
	//�O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo��
	//�O���t�B�b�N�X�f�o�C�X�����Z�b�g�\�ɂ��邽�߁A
	//�\�񂳂�Ă����r�f�I�����������ׂĉ��
	virtual void releseAll();
	//���ׂẴT�[�t�F�C�X���č쐬���A���ׂẴG���e�B�e�B�����Z�b�g
	virtual void resetAll();
	//�\�񂳂�Ă��������������ׂč폜
	virtual void deleteAll();
	//�Q�[���A�C�e���������_�[
	virtual void renderGame();
	//���������O���t�B�b�N�X�f�o�C�X������
	virtual void handleLostGraphicsDevice();

	void setDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	//Graphics�ւ̃|�C���^��߂�
	Graphics* getGraphics(){ return graphics; }
	//Input�ւ̃|�C���^��߂�
	Input* getInput(){ return input; }
	//�Q�[�����I��
	void exitGame(){ PostMessage(hwnd, WM_DESTROY, 0, 0); }
	//�������z�֐��̐錾
	//�����̊֐��́AGame���p������N���X���ŋL�q����K�v������܂�
	//�Q�[���A�C�e�����X�V
	virtual void update() = 0;
	//AI�v�Z�����s
	virtual void ai() = 0;
	//�Փ˂��`�F�b�N
	virtual void collisions() = 0;
	//�O���t�B�b�N�X�������_�[
	//graphics->spriteBegin();���Ăяo��
	//�X�v���C�g��`��
	//graphics->spriteEnd();���Ăяo��
	virtual void render() = 0;

	//Audio* getAudio()       { return audio; }
	virtual void consoleCommand();//�R���\�[���R�}���h������

	HWND Hwnd(){ return hwnd; }

};

#endif