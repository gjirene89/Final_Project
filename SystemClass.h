//************************************************************************//
//	SystemClass.h
//	2016-11-01
//	Irene Gersenowies
//************************************************************************//
#ifndef __SYSTEMCLASS_H__
#define __SYSTEMCLASS_H__

//=======================================================================//
//	PRE-PROCESSING DIRECTIVES
//=======================================================================//
# define WIN32_LEAN

//=======================================================================//
//		インクルード
//=======================================================================//
# include <windows.h>

#include "SceneManager.h"

# include "InputClass.h"
//# include "GraphicsClass.h"
//# include "SoundClass.h"
# include "FPSClass.h"
# include "CPUClass.h"
# include "TimerClass.h"
# include "PositionClass.h"

//=======================================================================//
//	クラス名		CSystem
//=======================================================================//
class CSystem
{
public: 
	CSystem(void);
	CSystem(const CSystem& other);
	~CSystem(void);

	bool Initialize(void);
	void Shutdown(void);
	void Run(void);

	LRESULT CALLBACK MessageHandle(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:
	bool Frame(void);
	bool HandleInput(float frameTime);
	void InitializeWindows(int &screenWidth, int &screenHeight);
	void ShutdownWindows(void);

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	CScene* m_Scene;
	CInput* m_Input;
	//CGraphics* m_Graphics;
	//SoundClass* m_Sound;
	
	CFps* m_FPS;
	CCpu* m_CPU;
	CTimer* m_Timer;
	CPosition* m_Position;
	
};

//=======================================================================//
//	プロトタイプ宣言
//=======================================================================//
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//=======================================================================//
//	グローバル変数
//=======================================================================//
static CSystem* ApplicationHandle = 0;


#endif
//******************************************************************************
//	End of file.
//******************************************************************************