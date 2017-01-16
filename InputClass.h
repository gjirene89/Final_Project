//************************************************************************//
//	InputClass.h
//	2016-11-02
//	2016-11-22 Revisited DirectX input
//	Irene Gersenowies
//************************************************************************//
#ifndef __INPUTCLASS_H__
#define __INPUTCLASS_H__

//=======================================================================//
//	PRE-PROCESSING DIRECTIVES
//=======================================================================//
#define DIRECTINPUT_VERSION 0x0800

//=======================================================================//
//	リンク
//=======================================================================//
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//=======================================================================//
//	インクルード
//=======================================================================//
#include <dinput.h>

//=======================================================================//
//	クラス名		CInput
//=======================================================================//
class CInput
{
public:
	CInput(void);
	CInput(const CInput& other);
	~CInput(void);

	bool Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown(void);
	bool Frame(void);

	bool IsEnterTriggered(void);
	bool IsEscapePressed(void);
	bool IsLeftArrowPressed(void);
	bool IsRightArrowPressed(void);
	bool IsUpArrowPressed(void);
	bool IsDownArrowPressed(void);
	bool IsAPressed(void);
	bool IsSPressed(void);
	bool IsWPressed(void);
	bool IsDPressed(void);
	bool IsQPressed(void);
	bool IsEPressed(void);
	bool IsF1Pressed(void);

	void GetMouseLocation(int&, int&);

private:
	bool ReadKeyboard(void);
	bool ReadMouse(void);
	void ProcessInput(void);

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	unsigned char m_keyboardStateOld[256];

	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;

};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************