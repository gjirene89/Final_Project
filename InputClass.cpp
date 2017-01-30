//************************************************************************//
//	inputClass.cpp
//	2016-11-02
//	Irene Gersenowies
//************************************************************************//
#include "inputClass.h"

//==============================================================================
//  関数名        CInput	
//  説明          CInputクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CInput::CInput()
{
	//初期化
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
}

//==============================================================================
//  関数名        CInput	
//  説明          CInputクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CInput& other			CInputのインスタンス
//	戻り値
//          なし
//==============================================================================
CInput::CInput(const CInput& other)
{
	//空
}

//==============================================================================
//  関数名        CInput	
//  説明          CInputクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CInput::~CInput()
{
	//空
}

//==============================================================================
//  関数名		 Initialize	
//  説明			 入力クラスの初期化関数
//------------------------------------------------------------------------------
//	引数
//          HINSTANCE   hInstance			ウインドウ インスタンス
//          HWND        hwnd                ウインドウ ハンドル
//          int         screenWidth         画面の幅
//          int         screenHeight        画面の高さ
//	戻り値
//			bool        true 成功　　　false 失敗
//==============================================================================
bool CInput::Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;
	int i;

	//画面サイズ設定
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	//マウス位置の初期化
	m_mouseX = 0;
	m_mouseY = 0;

	// 全キー状態の配列をfalseにする
	for (i = 0; i<256; i++)
	{
		m_keyboardState[i] = false;
		m_keyboardStateOld[i] = false;
	}


	//入力インタフェースの初期化
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	//キーボード入力の初期化
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	//データ形式を設定する(キーボード用）
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	//キーボード入力を共通しないという設定にする
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	//キーボード取得
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	//マウス初期化
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	//データ形式を設定する(マウス用）
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	//マウス入力を共通できるように設定にする
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	//マウス取得
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//==============================================================================
//  関数名		 Shutdown	
//  説明			 入力クラスの解放
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CInput::Shutdown()
{
	//マウスを解放
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	//キーボードを解放
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	//入力インタフェースを解放
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}

//==============================================================================
//  関数名		 Frame	
//  説明			 毎フレームの入力更新関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CInput::Frame()
{
	bool result;

	//キーボード状態を取得
	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	//マウス状態を取得
	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	//入力データの処理
	ProcessInput();

	return true;
}

//==============================================================================
//  関数名		 ReadKeyboard	
//  説明			 キーボード状態を取得する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CInput::ReadKeyboard()
{
	int i;
	HRESULT result;

	//前のフレームの状態を保存する
	for (i = 0; i<256; i++)
	{
		m_keyboardStateOld[i] = m_keyboardState[i];
	}

	//キーボードを取得
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		//アクセスが無くしたら、再取得する
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;

}

//==============================================================================
//  関数名		 ReadMouse	
//  説明			 マウス状態を取得する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CInput::ReadMouse()
{
	HRESULT result;

	//マウスを取得
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		//アクセスが無くしたら、再取得する
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

//==============================================================================
//  関数名		 ProcessInput	
//  説明			 入力データを処理する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CInput::ProcessInput()
{
	//マウスの位置を更新する
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	//マウスが画面から出ないように座標位置を制限する
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	return;
}

//==============================================================================
//  関数名		 IsSpaceTriggered
//  説明			 SpaceBarがトリガーされるかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true トリガーされた　　　false トリガーされていない
//==============================================================================
bool CInput::IsSpaceTriggered()
{
	if ((m_keyboardState[DIK_SPACE] & 0x80) && !(m_keyboardStateOld[DIK_SPACE] & 0x80))
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsEnterTriggered
//  説明			 Enterキーがトリガーされるかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true トリガーされた　　　false トリガーされていない
//==============================================================================
bool CInput::IsEnterTriggered()
{
	if ((m_keyboardState[DIK_RETURN] & 0x80) && !(m_keyboardStateOld[DIK_RETURN] & 0x80))
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsEscapePressed	
//  説明			 ESCキーが押されたかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 押されている　　　false 押されていない
//==============================================================================
bool CInput::IsEscapePressed()
{
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsRightPressed	
//  説明			 右矢印 (→) が押されたかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 押されている　　　false 押されていない
//==============================================================================
bool CInput::IsRightPressed()
{
	if (m_keyboardState[DIK_RIGHTARROW] & 0x80)
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsLeftPressed	
//  説明			 左矢印 (←) が押されたかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 押されている　　　false 押されていない
//==============================================================================
bool CInput::IsLeftPressed()
{
	if (m_keyboardState[DIK_LEFTARROW] & 0x80)
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsUpPressed	
//  説明			 上矢印 (↑) が押されたかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 押されている　　　false 押されていない
//==============================================================================
bool CInput::IsUpPressed()
{
	if (m_keyboardState[DIK_UPARROW] & 0x80)
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsDownPressed	
//  説明			 下矢印 (↓) が押されたかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 押されている　　　false 押されていない
//==============================================================================
bool CInput::IsDownPressed()
{
	if (m_keyboardState[DIK_DOWNARROW] & 0x80)
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsDashTriggered
//  説明			 ダッシュ開始のキーがトリガーされたかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 押されている　　　false 押されていない
//==============================================================================
bool CInput::IsDashTriggered()
{
	if ((m_keyboardState[DIK_A] & 0x80) && !(m_keyboardStateOld[DIK_A] & 0x80))
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsFlipTriggered
//  説明			 パタパタ開始のキーがトリガーされるかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 押されている　　　false 押されていない
//==============================================================================
bool CInput::IsFlipTriggered()
{
	if ((m_keyboardState[DIK_S] & 0x80) && !(m_keyboardStateOld[DIK_S] & 0x80))
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 IsF1Pressed	
//  説明			 F1キーが押されたかどうか確認する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 押されている　　　false 押されていない
//==============================================================================
bool CInput::IsF1Pressed()
{
	if (m_keyboardState[DIK_F1] & 0x80)
	{
		return true;
	}

	return false;
}

//==============================================================================
//  関数名		 GetMouseLocation	
//  説明			 マウスの位置をゲットする関数
//------------------------------------------------------------------------------
//	引数
//			int&    mouseX				マウスのX軸
//			int&    mouseY				マウスのY軸
//	戻り値
//          なし
//==============================================================================
void CInput::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************