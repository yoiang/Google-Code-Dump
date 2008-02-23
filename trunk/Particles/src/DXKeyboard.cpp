#include "DXKeyboard.h"

// required libraries: Dxguid.lib Dinput8.lib

DXKeyboard::DXKeyboard():m_pDirectInputObject(0), m_pDirectInputKeyboardDevice(0), m_bOutsideObject(false)
{
	for (int iTrav = 0 ; iTrav < 256 ; ++iTrav) m_iKeyState[iTrav] = DXKEY_UP ;
}

DXKeyboard::~DXKeyboard()
{
	Release() ;
}

int DXKeyboard::Init(const HINSTANCE &hInstance, const HWND &hWnd)
{
	if(InitDirectInput(hInstance))
	{
//		MessageBox(0,"InitDirectInput(hInstance) failed!","DXKeyboard::Init(HINSTANCE hInstance, HWND hWnd)",MB_OK);
		return 1 ;
	}

	if(InitKeyboard(hWnd))	
	{
//		MessageBox(0,"InitKeyboard(hWnd) failed!","DXKeyboard::Init(HINSTANCE hInstance, HWND hWnd)",MB_OK);
		return 2;
	}
	return 0 ;
}

int DXKeyboard::Init(const LPDIRECTINPUT8 &pDirectInputObject, const HWND &hWnd)
{
	if (pDirectInputObject == 0)
	{
		MessageBox(0, "DirectInput object not initialized!", "DXKeyboard::Init(LPDIRECTINPUTDEVICE8 pDirectInputObject, HWND hWnd)", MB_OK) ;
		return 1 ;
	}
	m_pDirectInputObject = pDirectInputObject ;
	m_bOutsideObject = true ;
	if(InitKeyboard(hWnd))	
	{
//		MessageBox(0,"InitKeyboard(hWnd) failed!","DXKeyboard::Init(LPDIRECTINPUTDEVICE8 pDirectInputObject, HWND hWnd)",MB_OK);
		return 2;
	}

	return 0 ;
}

int DXKeyboard::InitDirectInput(const HINSTANCE &hInstance)
{	
	m_bOutsideObject = false ;
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInputObject, NULL)))
	{
		MessageBox(0, "DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInputObject, NULL) failed!","DXKeyboard::InitDirectInput(HINSTANCE hInstance)",MB_OK);
		return 1 ;
	}
	
	return 0 ;
}

int DXKeyboard::InitKeyboard(const HWND &hWnd)
{
	if(FAILED(m_pDirectInputObject->CreateDevice(GUID_SysKeyboard, &m_pDirectInputKeyboardDevice, NULL)))
	{
		MessageBox(0, "CreateDevice(GUID_SysKeyboard, &m_pDirectInputKeyboardDevice, NULL) failed!","DXKeyboard::InitKeyboard(HWND hWnd)",MB_OK);
		return 1 ;
	}
	
	if(FAILED(m_pDirectInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(0, "SetDataFormat(&c_dfDIKeyboard) failed!","DXKeyboard::InitKeyboard(HWND hWnd)",MB_OK);
		return 2 ;
	}
	
	if(FAILED(m_pDirectInputKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(0, "SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE) failed!","DXKeyboard::InitKeyboard(HWND hWnd)",MB_OK);
		return 3;
	}
	
	if(FAILED(m_pDirectInputKeyboardDevice->Acquire()))
	{
		MessageBox(0, "Acquire() failed!","DXKeyboard::InitKeyboard(HWND hWnd)",MB_OK);
		return 4;
	}
	
	return 0;
}

void DXKeyboard::Release()
{
	if(m_pDirectInputKeyboardDevice != 0)
	{
		m_pDirectInputKeyboardDevice->Unacquire();
		m_pDirectInputKeyboardDevice->Release();
		m_pDirectInputKeyboardDevice = 0 ;
	}
	
	if(m_pDirectInputObject != 0 && !m_bOutsideObject)
	{
		m_pDirectInputObject->Release();
		m_pDirectInputObject = 0 ;
	}
}

int DXKeyboard::Update()
{
	if (m_pDirectInputKeyboardDevice == 0)
	{
		MessageBox(0, "DirectInput Keyboard device not initialized!", "DXKeyboard::Update()", MB_OK) ;
		return 1 ;
	}

	if(FAILED(m_pDirectInputKeyboardDevice->GetDeviceState(sizeof(m_cKeyBuffer),(LPVOID)&m_cKeyBuffer)))
	{
		MessageBox(0, "GetDeviceState() failed!", "DXKeyboard::Update()", MB_OK);
		return 2 ;
	}
	
	return 0;
}

bool DXKeyboard::KeyPressed(const int &iKey)
{	
	if (m_cKeyBuffer[iKey] & 0x80) return true ;
	return false ;
}

int DXKeyboard::State(const int &iKey)
{
	if (m_cKeyBuffer[iKey] & 0x80)
	{
		switch (m_iKeyState[iKey])
		{
		case DXKEY_UP:
			m_iKeyState[iKey] = DXKEY_DOWN ;
		break ;
		case DXKEY_DOWN:
			m_iKeyState[iKey] = DXKEY_STILL ;
		break ;
		case DXKEY_STILL:
		break ;
		}
	} else
	{
		switch (m_iKeyState[iKey])
		{
		case DXKEY_UP:
		break ;
		case DXKEY_DOWN:
			m_iKeyState[iKey] = DXKEY_UP ;
		break ;
		case DXKEY_STILL:
			m_iKeyState[iKey] = DXKEY_UP ;
		break ;
		}
	}
	return m_iKeyState[iKey] ;
}

// Ian Grossberg - 2002