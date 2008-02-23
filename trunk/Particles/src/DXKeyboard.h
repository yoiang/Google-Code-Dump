#ifndef __DXKEYBOARD_H__
#define __DXKEYBOARD_H__

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define DXKEY_UP 0
#define DXKEY_DOWN 1
#define DXKEY_STILL 2

class DXKeyboard
{
private:
	LPDIRECTINPUT8 m_pDirectInputObject ;
	LPDIRECTINPUTDEVICE8 m_pDirectInputKeyboardDevice;

	bool m_bOutsideObject ;

	char m_cKeyBuffer[256] ;
	int m_iKeyState[256] ;

	int InitDirectInput(const HINSTANCE &hInstance);
	int InitKeyboard(const HWND &hWnd);

public:
	DXKeyboard();
	~DXKeyboard();

	int Init(const HINSTANCE &hInstance, const HWND &hWnd) ;
	int Init(const LPDIRECTINPUT8 &pDirectInputObject, const HWND &hWnd) ;
	void Release() ;

	int Update();
	bool KeyPressed(const int &iKey);
	int State(const int &iKey) ;
};

#endif

// Ian Grossberg - 2002