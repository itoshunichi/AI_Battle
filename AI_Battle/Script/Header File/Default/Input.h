#ifndef _INPUT_H                
#define _INPUT_H                
#define WIN32_LEAN_AND_MEAN

class Input;

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>
#include"constants.h"
#include "gameError.h"



// �}�E�X�p
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif
//--------------------------

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;    //�L�[�z��̃T�C�Y

	// what values for clear(), bit flag
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

const DWORD GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.20f * 0X7FFF);    // default to 20% of range as deadzone
const DWORD GAMEPAD_TRIGGER_DEADZONE = 30;                      // trigger range 0-255
const DWORD MAX_CONTROLLERS = 4;                                // Maximum number of controllers supported by XInput

// Bit corresponding to gamepad button in state.Gamepad.wButtons
const DWORD GAMEPAD_DPAD_UP = 0x0001;
const DWORD GAMEPAD_DPAD_DOWN = 0x0002;
const DWORD GAMEPAD_DPAD_LEFT = 0x0004;
const DWORD GAMEPAD_DPAD_RIGHT = 0x0008;
const DWORD GAMEPAD_START_BUTTON = 0x0010;
const DWORD GAMEPAD_BACK_BUTTON = 0x0020;
const DWORD GAMEPAD_LEFT_THUMB = 0x0040;
const DWORD GAMEPAD_RIGHT_THUMB = 0x0080;
const DWORD GAMEPAD_LEFT_SHOULDER = 0x0100;
const DWORD GAMEPAD_RIGHT_SHOULDER = 0x0200;
const DWORD GAMEPAD_A = 0x1000;
const DWORD GAMEPAD_B = 0x2000;
const DWORD GAMEPAD_X = 0x4000;
const DWORD GAMEPAD_Y = 0x8000;

struct ControllerState
{
	XINPUT_STATE state;
	XINPUT_VIBRATION vibration;
	float vibrateTimeLeft; //�~���b
	float vibrateTimeRight;//�~���b
	bool connected;
};


class Input
{
private:
	//�w��̃L�[��������Ă����Ԃ̏ꍇ��true
	bool keysDown[inputNS::KEYS_ARRAY_LEN];
	//�w��̃L�[�������ꂽ�ꍇ��true
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];
	std::string textIn;    //���[�U�[�����͂����e�L�X�g
	char charIn;//�Ō�ɓ��͂��ꂽ����
	bool newLine;//�V�����s�̊J�n����true
	int mouseX, mouseY;//�}�E�X�̉�ʍ��W
	int mouseRawX, mouseRawY;//�����׃}�E�X�̃f�[�^
	RAWINPUTDEVICE Rid[1];//�����׃}�E�X�p
	bool mouseCaptured;//�}�E�X���L���v�`������Ă���ꍇ��true
	bool mouseLButton;//���}�E�X��������Ă���ꍇ��true
	bool mouseMButton;//�����}�E�X��������Ă���ꍇ��true
	bool mouseRButton;//�E�}�E�X��������Ă���ꍇ��true
	bool mouseX1Button;//X1�}�E�X�{�^����������Ă���ꍇ��true
	bool mouseX2Button;//X2�}�E�X�{�^����������Ă���ꍇ��true
	ControllerState controllers[MAX_CONTROLLERS]; //�R���g���[���[�̏��
	bool ispush;
	int Count;

public:
	Input();//�R���X�g���N�^
	~Input();//�f�X�g���N�^
	void initialize(HWND hwnd, bool capture);//������
	void update(float frameTime, UINT n);
	void keyDown(WPARAM wParam);
	void keyUp(WPARAM wParam);
	void keyIn(WPARAM wParam);
	bool isKeyDown(UCHAR vkey)const;
	bool isKeyTrigger(UCHAR vkey);
	bool wasKeyPressed(UCHAR vkey)const;
	bool anyKeyPressed(UCHAR vkey)const;
	//�e�L�X�g���͂𕶎���Ƃ��Ė߂�
	std::string getTextIn(){ return textIn; }
	//�Ō�ɓ��͂��ꂽ������߂�
	char getCharIn(){ return charIn; }

	void clearKeyPress(UCHAR vkey);
	//�e�L�X�g���̓o�b�t�@���N���A
	void clearTextIn(){ textIn.clear(); }
	void clear(UCHAR what);
	void clearAll(){ clear(inputNS::KEYS_MOUSE_TEXT); }

	void mouseIn(LPARAM lParam);
	void mouseRawIn(LPARAM lParam);
	//�}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseLButton(bool b){ mouseLButton = b; }
	//�}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseMButton(bool b){ mouseMButton = b; }
	//�}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseRButton(bool b){ mouseRButton = b; }
	//�}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseXButton(WPARAM wParam)
	{
		mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
		mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	}
	//�}�E�X��X�ʒu��߂�
	int getMouseX()const{ return mouseX; }
	//�}�E�X��Y�ʒu��߂�
	int getMouseY()const{ return mouseY; }
	//�}�E�X��X�ʒu�̈ړ��̃��[�f�[�^��߂��B���ւ̈ړ���<0,�E�ւ̈ړ���>0
	//�����׃}�E�X�ɑΉ�
	int getMouseRawX()const{ return mouseRawX; }
	//�}�E�X��Y�ʒu�̈ړ��̃��[�f�[�^��߂��B��ւ̈ړ���<0,���ւ̈ړ���>0
	//�����׃}�E�X�ɑΉ�
	int getMouseRawY()const { return mouseRawY; }
	//���}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseLButton(bool isTrigger)
	{
		return mouseLButton;

	}
	//�����}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseMButton(bool isTrigger)const{ return mouseMButton; }
	//�E�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseRButton(bool isTrigger)const{ return mouseRButton; }
	//X1�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseX1Button(bool isTrigger)const{ return mouseX1Button; }
	//X2�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseX2Button(bool isTrigger)const { return mouseX2Button; }


	void checkControllers();
	void readControllers();
	//�w��̃Q�[���R���g���[���̏�Ԃ�߂�
	const ControllerState* getControllerState(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return &controllers[n];
	}
	//�R���g���[���[n�̃{�^���̏�Ԃ�߂�
	const WORD getGamepadButtons(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;

		return(controllers[n].state.Gamepad.wButtons);
	}

	//�R���g���[��n�̕����p�b�h��̏�Ԃ�߂�
	bool getGamepadDPadUp(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_DPAD_UP) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else
			return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_UP) != 0);

	}

	//�R���g���[��n�̕����p�b�h���̏�Ԃ�߂�
	bool getGamepadDPadDown(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_DPAD_DOWN) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
			
		}
		else
		return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_DOWN) != 0);
	}

	// �R���g���[��n�̕����p�b�h���̏�Ԃ�߂�
	bool getGamepadDPadLeft(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_DPAD_LEFT) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_LEFT) != 0);
	}

	//�R���g���[��n�̕����p�b�h�E�̏�Ԃ�߂�
	bool getGamepadDPadRight(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_DPAD_RIGHT) != 0)
			{
				Count++;
				if (Count == 1)
				{

					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
			
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_RIGHT) != 0);
	}

	// �R���g���[��n��START�{�^���̏�Ԃ�߂�
	bool getGamepadStart(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_START_BUTTON) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}

			}
			return false;
			
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_START_BUTTON) != 0);
	}

	//�R���g���[��n��BACK�{�^���̏�Ԃ�߂�
	bool getGamepadBack(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_BACK_BUTTON) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_BACK_BUTTON) != 0);
	}

	// �R���g���[��n�̍��T���{�^���̏�Ԃ�߂�
	bool getGamepadLeftThumb(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_LEFT_THUMB) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_THUMB) != 0);
	}

	// �R���g���[��n�̉E�T���{�^���̏�Ԃ�߂�
	bool getGamepadRightThumb(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_RIGHT_THUMB) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_THUMB) != 0);
	}

	//�R���g���[��n�̍��V�����_�[�{�^���̏�Ԃ�߂�
	bool getGamepadLeftShoulder(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_LEFT_SHOULDER) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_SHOULDER) != 0);
	}

	// �R���g���[��n�̉E�V�����_�[�{�^���̏�Ԃ�߂�
	bool getGamepadRightShoulder(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_RIGHT_SHOULDER) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_SHOULDER) != 0);
	}

	//�R���g���[��n��A�{�^���̏�Ԃ�߂�
	bool getGamepadA(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_A) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_A) != 0);
	}

	//�R���g���[��n��B�{�^���̏�Ԃ�߂�
	bool getGamepadB(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_B) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_B) != 0);
	}

	//�R���g���[��n��X�{�^���̏�Ԃ�߂�
	bool getGamepadX(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_X) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_X) != 0);
	}

	//�R���g���[��n��Y�{�^���̏�Ԃ�߂�
	bool getGamepadY(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if ((getGamepadButtons(n)&GAMEPAD_Y) != 0)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_Y) != 0);
	}

	//�R���g���[��n�̍��g���K�[�̒l��߂��܂�
	BYTE getGamepadLeftTrigger(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if (controllers[n].state.Gamepad.bLeftTrigger)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return (controllers[n].state.Gamepad.bLeftTrigger);
	}

	////�R���g���[��n�̉E�g���K�[�̒l��߂��܂�
	BYTE getGamepadRightTrigger(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if (controllers[n].state.Gamepad.bRightTrigger)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return (controllers[n].state.Gamepad.bRightTrigger);
	}

	//�R���g���[��n�̍��T���X�e�B�b�N�AX�̒l��߂��܂�
	SHORT getGamepadThumbLX(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if (controllers[n].state.Gamepad.sThumbLX)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return (controllers[n].state.Gamepad.sThumbLX) / 10000;
	}

	////�R���g���[��n�̍��T���X�e�B�b�N�AY�̒l��߂��܂�
	SHORT getGamepadThumbLY(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if (controllers[n].state.Gamepad.sThumbLY)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return (controllers[n].state.Gamepad.sThumbLY) / 10000;
	}

	////�R���g���[��n�̉E�T���X�e�B�b�N�AX�̒l��߂��܂�
	SHORT getGamepadThumbRX(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if (controllers[n].state.Gamepad.sThumbRX)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return (controllers[n].state.Gamepad.sThumbRX) / 10000;
	}

	////�R���g���[��n�̉E�T���X�e�B�b�N�AY�̒l��߂��܂�
	SHORT getGamepadThumbRY(UINT n, bool isTrigger)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		if (isTrigger)
		{
			if (controllers[n].state.Gamepad.sThumbRY)
			{
				Count++;
				if (Count == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		else return (controllers[n].state.Gamepad.sThumbRY) / 10000;
	}

	// �R���g���[��n�̍����[�^�[��U��������
	// ���͒���g�U��
	//speed:0 = �I�t�A65536=100�p�[�Z���g
	// sec:�U�������鎞��(�b)
	void gamePadVibrateLeft(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		controllers[n].vibration.wLeftMotorSpeed = speed;
		controllers[n].vibrateTimeLeft = sec;
	}

	// �R���g���[��n�̉E���[�^�[��U��������
	// �E�͒���g�U��
	//speed:0 = �I�t�A65536=100�p�[�Z���g
	// sec:�U�������鎞��(�b)
	void gamePadVibrateRight(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		controllers[n].vibration.wRightMotorSpeed = speed;
		controllers[n].vibrateTimeRight = sec;
	}

	void vibrateControllers(float frameTime);


	int getCount(){ return Count; }

};
#endif