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



// マウス用
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif
//--------------------------

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;    //キー配列のサイズ

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
	float vibrateTimeLeft; //ミリ秒
	float vibrateTimeRight;//ミリ秒
	bool connected;
};


class Input
{
private:
	//指定のキーが押されている状態の場合にtrue
	bool keysDown[inputNS::KEYS_ARRAY_LEN];
	//指定のキーが押された場合にtrue
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];
	std::string textIn;    //ユーザーが入力したテキスト
	char charIn;//最後に入力された文字
	bool newLine;//新しい行の開始時にtrue
	int mouseX, mouseY;//マウスの画面座標
	int mouseRawX, mouseRawY;//高精細マウスのデータ
	RAWINPUTDEVICE Rid[1];//高精細マウス用
	bool mouseCaptured;//マウスがキャプチャされている場合にtrue
	bool mouseLButton;//左マウスが押されている場合にtrue
	bool mouseMButton;//中央マウスが押されている場合にtrue
	bool mouseRButton;//右マウスが押されている場合にtrue
	bool mouseX1Button;//X1マウスボタンが押されている場合にtrue
	bool mouseX2Button;//X2マウスボタンが押されている場合にtrue
	ControllerState controllers[MAX_CONTROLLERS]; //コントローラーの状態
	bool ispush;
	int Count;

public:
	Input();//コンストラクタ
	~Input();//デストラクタ
	void initialize(HWND hwnd, bool capture);//初期化
	void update(float frameTime, UINT n);
	void keyDown(WPARAM wParam);
	void keyUp(WPARAM wParam);
	void keyIn(WPARAM wParam);
	bool isKeyDown(UCHAR vkey)const;
	bool isKeyTrigger(UCHAR vkey);
	bool wasKeyPressed(UCHAR vkey)const;
	bool anyKeyPressed(UCHAR vkey)const;
	//テキスト入力を文字列として戻す
	std::string getTextIn(){ return textIn; }
	//最後に入力された文字を戻す
	char getCharIn(){ return charIn; }

	void clearKeyPress(UCHAR vkey);
	//テキスト入力バッファをクリア
	void clearTextIn(){ textIn.clear(); }
	void clear(UCHAR what);
	void clearAll(){ clear(inputNS::KEYS_MOUSE_TEXT); }

	void mouseIn(LPARAM lParam);
	void mouseRawIn(LPARAM lParam);
	//マウスボタンの状態を保存
	void setMouseLButton(bool b){ mouseLButton = b; }
	//マウスボタンの状態を保存
	void setMouseMButton(bool b){ mouseMButton = b; }
	//マウスボタンの状態を保存
	void setMouseRButton(bool b){ mouseRButton = b; }
	//マウスボタンの状態を保存
	void setMouseXButton(WPARAM wParam)
	{
		mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
		mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	}
	//マウスのX位置を戻す
	int getMouseX()const{ return mouseX; }
	//マウスのY位置を戻す
	int getMouseY()const{ return mouseY; }
	//マウスのX位置の移動のローデータを戻す。左への移動は<0,右への移動は>0
	//高精細マウスに対応
	int getMouseRawX()const{ return mouseRawX; }
	//マウスのY位置の移動のローデータを戻す。上への移動は<0,下への移動は>0
	//高精細マウスに対応
	int getMouseRawY()const { return mouseRawY; }
	//左マウスボタンの状態を戻す
	bool getMouseLButton(bool isTrigger)
	{
		return mouseLButton;

	}
	//中央マウスボタンの状態を戻す
	bool getMouseMButton(bool isTrigger)const{ return mouseMButton; }
	//右マウスボタンの状態を戻す
	bool getMouseRButton(bool isTrigger)const{ return mouseRButton; }
	//X1マウスボタンの状態を戻す
	bool getMouseX1Button(bool isTrigger)const{ return mouseX1Button; }
	//X2マウスボタンの状態を戻す
	bool getMouseX2Button(bool isTrigger)const { return mouseX2Button; }


	void checkControllers();
	void readControllers();
	//指定のゲームコントローラの状態を戻す
	const ControllerState* getControllerState(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return &controllers[n];
	}
	//コントローラーnのボタンの状態を戻す
	const WORD getGamepadButtons(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;

		return(controllers[n].state.Gamepad.wButtons);
	}

	//コントローラnの方向パッド上の状態を戻す
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

	//コントローラnの方向パッド下の状態を戻す
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

	// コントローラnの方向パッド左の状態を戻す
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

	//コントローラnの方向パッド右の状態を戻す
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

	// コントローラnのSTARTボタンの状態を戻す
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

	//コントローラnのBACKボタンの状態を戻す
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

	// コントローラnの左サムボタンの状態を戻す
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

	// コントローラnの右サムボタンの状態を戻す
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

	//コントローラnの左ショルダーボタンの状態を戻す
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

	// コントローラnの右ショルダーボタンの状態を戻す
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

	//コントローラnのAボタンの状態を戻す
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

	//コントローラnのBボタンの状態を戻す
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

	//コントローラnのXボタンの状態を戻す
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

	//コントローラnのYボタンの状態を戻す
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

	//コントローラnの左トリガーの値を戻します
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

	////コントローラnの右トリガーの値を戻します
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

	//コントローラnの左サムスティック、Xの値を戻します
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

	////コントローラnの左サムスティック、Yの値を戻します
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

	////コントローラnの右サムスティック、Xの値を戻します
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

	////コントローラnの右サムスティック、Yの値を戻します
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

	// コントローラnの左モーターを振動させる
	// 左は低周波振動
	//speed:0 = オフ、65536=100パーセント
	// sec:振動させる時間(秒)
	void gamePadVibrateLeft(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		controllers[n].vibration.wLeftMotorSpeed = speed;
		controllers[n].vibrateTimeLeft = sec;
	}

	// コントローラnの右モーターを振動させる
	// 右は低周波振動
	//speed:0 = オフ、65536=100パーセント
	// sec:振動させる時間(秒)
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