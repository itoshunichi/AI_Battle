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
	const UINT WIDTH = 500;//�R���\�[���̕�
	const UINT HEIGHT = 400;//�R���\�[���̍���
	//�R���\�[���̍�����̉�ʈʒu�B
	const UINT X = 5;
	const UINT Y = 5;

	const UINT MARGIN = 4;//�R���\�[���̒[����e�L�X�g�܂ł̗]��
	const char FONT[] = "Courier New";//�R���\�[���̃e�L�X�g�Ɏg�p����t�H���g
	const int FONT_HEIGHT = 14;//�R���\�[���̃t�H���g�̃f�t�H���g�̍���
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;//�R���\�[���̃f�t�H���g�̐F
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(0, 0, 0, 5); //�R���\�[���̔w�i�̐F�B(�������̃O���[)
	const int MAX_LINES = 256;//�e�L�X�g�o�b�t�@���̕\���\�ȃe�L�X�g�̍ő�s��
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
	Console();//�R���X�g���N�^
	virtual ~Console();//�f�X�g���N�^
	//�R���\�[����������
	bool initialize(Graphics *g, Input *in);
	//�R���\�[�����Q�[����ʂɕ`��
	const void draw();
	//�R���\�[���̕\��/��\���𐧌䂷��v���p�e�B�𔽓]
	void shoeHide();
	//�\��/��\���𐧌䂷��v���p�e�B�̌��݂̏�Ԃ�߂��܂�
	bool getVisible(){ return visible; }
	//�R���\�[����\�����܂�
	void show(){ visible = true; }
	//�R���\�[�����\���ɂ���
	void hide(){ visible = false; }
	//�R���\�[���f�B�X�v���C�Ƀe�L�X�g�������ǉ����܂�
	void print(const std::string &str);
	//�V���O���L�[�̃R���\�[���R�}���h������
	std::string getCommand();
	//�R���\�[���̓��̓e�L�X�g��߂�
	std::string getInput(){ inputStr = ""; }
	//�R���\�[���̓��̓e�L�X�g���N���A���܂�
	void clearInput(){ inputStr = ""; }

	void onLostDevice();
	void onResetDevice();
};

#endif