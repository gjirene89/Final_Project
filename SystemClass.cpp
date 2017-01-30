//************************************************************************//
//	SystemClass.cpp
//	2016-11-01
//	Irene Gersenowies
//************************************************************************//
# include "SystemClass.h"

//=======================================================================//
//		マクロ定数
//=======================================================================//
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define DEBUG_MODE (0)


# define NAME   L"就職作品"
# define TITLE  L"AT-13B-607-03 IRENE GERSENOWIES"

//==============================================================================
//  関数名        CSystem	
//  説明          CSystemクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CSystem::CSystem()
{
	m_Scene = 0;
	m_Input = 0;

	//m_Sound = 0;
	m_FPS = 0;
	m_CPU = 0;
	m_Timer = 0;
	m_Position = 0;
}

//==============================================================================
//  関数名        CSystem	
//  説明          CSystemクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CSystem& other			CSystemのインスタンス
//	戻り値
//          なし
//==============================================================================
CSystem::CSystem(const CSystem& other)
{
	//今は空
}

//==============================================================================
//  関数名        ～CSystem	
//  説明          CSystemクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CSystem::~CSystem()
{
	//今は空
}

//==============================================================================
//  関数名		 Initialize	
//  説明			 システムの初期関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CSystem::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	//ウインドウのサイズ初期化
	screenWidth = 0;
	screenHeight = 0;

	//Windows APIの初期化
	InitializeWindows(screenWidth, screenHeight);

	//キーボード入力用のInput オブジェクト生成.
	m_Input = new CInput;
	if (!m_Input)
	{
		return false;
	}

	//Input オブジェクトの初期化
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	//シーン管理者を初期化する
	result = CScene::InitializeSceneManager(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}

	//現在のシーンをタイトルシーンにする
	m_Scene = m_Scene->GetScene(CScene::SCENE_NAME::SCENE_TITLE);
	if (!m_Scene)
	{
		MessageBox(m_hwnd, L"Failed to Load Scene", L"Error", MB_OK);
		return false;
	}
	
	//タイトルシーンを初期化する
	result = m_Scene->Initialize();
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Title Scene object.", L"Error", MB_OK);
		return false;
	}

/*
	//FPSオブジェクト生成
	m_FPS = new CFps;
	if (!m_FPS)
	{
		return false;
	}

	//FPSオブジェクト初期化
	m_FPS->Initialize();

	//CPUオブジェクト生成
	m_CPU = new CCpu;
	if (!m_CPU)
	{
		return false;
	}

	//CPUオブジェクト初期化
	m__CPU->Initialize();
	*/

	//タイマー オブジェクト生成
	m_Timer = new CTimer;
	if (!m_Timer)
	{
		return false;
	}

	//タイマー オブジェクト初期化
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}

	/*
	//Create the sound object
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
	return false;
	}


	//Initialize the sound object
	result = m_Sound->Initialize(m_hwnd);
	if (!result)
	{
	MessageBox(m_hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
	return false;
	}
	
	//Create the position object
	m_Position = new CPosition;
	if (!m_Position)
	{
		return false;
	}
	*/
	return true;
}

//==============================================================================
//  関数名		 Shutdown	
//  説明			 システムの解放
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CSystem::Shutdown()
{
	//シーンを解放する
	if (m_Scene)
	{
		m_Scene->Shutdown();
		m_Scene = 0;
	}

/*	
	//移動管理オブジェクトを解放する
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}
	*/
	//タイマー オブジェクトを解放する
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}
	/*
	//CPUオブジェクトを解放する
	if (m_CPU)
	{
		m_CPU->Shutdown();
		delete m_CPU;
		m_CPU = 0;
	}

	//FPSオブジェクトを解放する
	if (m_FPS)
	{
		delete m_FPS;
		m_FPS = 0;
	}

	
	//Release the sound object
	if (m_Sound)
	{
		m_Sound->Shutdown();
		delete m_Sound;
		m_Sound = 0;
	}
	*/

	//Input オブジェクト解除
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	//ウインドウ解除
	ShutdownWindows();

	return;
}

//==============================================================================
//  関数名		 Run	
//  説明			 システムの処理関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CSystem::Run()
{
	MSG msg;
	bool done, result;

	//メッセージ構造体の初期化
	ZeroMemory(&msg, sizeof(MSG));
	done = false;

	//ゲームループ
	while (!done)
	{

		//ウインドウメッセージ
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//ウインドウが閉じられるとゲーム終了
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			//ゲーム処理
			result = Frame();
			if (!result)
			{
				MessageBox(m_hwnd, L"Frame Processing Failed", L"Error", MB_OK);
				done = true;
			}
		}

		//ESCキーが押されたら、ゲームが終わる
		if (m_Input->IsEscapePressed() == true)
		{
			done = true;
		}
	}

	return;
}

//==============================================================================
//  関数名		 Frame	
//  説明			 毎フレームのゲーム処理更新関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CSystem::Frame()
{
	bool result;
	//float posX, posY, posZ;
	//float rotX, rotY, rotZ;

	
	//システム情報を更新する
	m_Timer->Frame(); 
//	m_FPS->Frame();
//	m_CPU->Frame();
	

	//入力更新
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}
	
	m_Scene->Input(m_Input);

#if DEBUG_MODE
	if (m_Input->IsSpaceTriggered())
	{
#endif
		m_Scene->Action();
		m_Scene->Render();
		m_Scene->PostAction();
#if DEBUG_MODE
	}
#endif
	//入力取得
	result = HandleInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}
	
	//Get the view point postion/rotation
	//m_Position->GetPosition(posX, posY, posZ);
	//m_Position->GetRotation(rotX, rotY, rotZ);

	return true;
}

//==============================================================================
//  関数名		 MessageHandle	
//  説明			 ウインドウのメッセージを管理する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			LRESULT
//==============================================================================
LRESULT CALLBACK CSystem::MessageHandle(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

//==============================================================================
//  関数名		 InitializeWindows	
//  説明			 ウインドウの初期化関数
//------------------------------------------------------------------------------
//	引数
//			int& screenWidth			画面の幅
//          int& screenHeight			画面の高さ
//	戻り値
//			なし
//==============================================================================
void CSystem::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// 当オブジェクトへのポインタを取得
	ApplicationHandle = this;

	// インスタンス生成
	m_hinstance = GetModuleHandle(NULL);

	//名前設定
	m_applicationName = NAME;

	//ウインドウ設定
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//ウインドウの登録
	RegisterClassEx(&wc);

	//サイズ設定
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//フルスクリーン設定
	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//上左の位置を0にする
		posX = posY = 0;
	}
	//ウインドウ表示の設定
	else
	{
		//ウインドウサイズ設定
		screenWidth = SCREEN_WIDTH;
		screenHeight = SCREEN_HEIGHT;

		//ウインドウを真ん中に設置する
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//ウインドウ生成してハンドルを取得する
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	//ウインドウを開き、アクティブにする
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	//マウスを非表示にする
	ShowCursor(false);

	return;
}

//==============================================================================
//  関数名		 ShutdownWindows	
//  説明			 ウインドウを解放する関数
//------------------------------------------------------------------------------
//	引数
//			なし
//	戻り値
//			なし
//==============================================================================
void CSystem::ShutdownWindows()
{
	// マウスを表示する
	ShowCursor(true);

	//フルスクリーンの場合、ウインドウに戻す
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//ウインドウを削除
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	//アプリケーションのインスタンスを削除
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	//現在のクラスへのポインタを解放
	ApplicationHandle = NULL;

	return;
}

//==============================================================================
//  関数名		 WndProc	
//  説明			 ウインドウをメッセージを管理する関数
//------------------------------------------------------------------------------
//	引数
//			HWND     hwnd           ウインドウ ハンドル
//			UINT     uMessage       メッセージ
//			WPARAM   wParam         追加情報
//			LPARAM   lParam         追加情報
//	戻り値
//			LRESULT
//==============================================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		//ウインドウが破壊された場合
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	
		//ウインドウが閉じられた場合
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		//それ以外のメッセージをSystemクラスに送る
		default:
		{
			return ApplicationHandle->MessageHandle(hwnd, uMessage, wParam, lParam);
		}
	}
}

//==============================================================================
//  関数名		 HandleInput	
//  説明			 インプット管理する関数
//------------------------------------------------------------------------------
//	引数
//			float   frameTime          
//	戻り値
//			bool    true 成功          false　失敗
//==============================================================================
bool CSystem::HandleInput(float frameTime)
{
	
	bool key;
	CScene* newScene;

	//シーン遷移を行う
	key = m_Input->IsEnterTriggered();
	newScene = m_Scene->ChangeScene(key);
	if (!newScene)
	{
		MessageBox(m_hwnd, L"Failed to Load Scene.", L"Error", MB_OK);
		return false;
	}

	if (newScene != m_Scene)
	{
		m_Scene = newScene;
		m_Scene->Initialize();
	}



	/*
	//Set the frame time for calculating the update position
	m_Position->SetFrameTime(frameTime);

	//Handle the input
	keyDown = m_Input->IsAPressed();
	m_Position->MoveLeftwards(keyDown);

	keyDown = m_Input->IsDPressed();
	m_Position->MoveRightwards(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->MoveUpwards(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveDownwards(keyDown);

	keyDown = m_Input->IsEPressed();
	m_Position->MoveForwards(keyDown);

	keyDown = m_Input->IsQPressed();
	m_Position->MoveBackwards(keyDown);

	
	*/
	return true;
}

//******************************************************************************
//	End of file.
//******************************************************************************