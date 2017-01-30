//************************************************************************//
//	SystemClass.cpp
//	2016-11-01
//	Irene Gersenowies
//************************************************************************//
# include "SystemClass.h"

//=======================================================================//
//		�}�N���萔
//=======================================================================//
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define DEBUG_MODE (0)


# define NAME   L"�A�E��i"
# define TITLE  L"AT-13B-607-03 IRENE GERSENOWIES"

//==============================================================================
//  �֐���        CSystem	
//  ����          CSystem�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
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
//  �֐���        CSystem	
//  ����          CSystem�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CSystem& other			CSystem�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CSystem::CSystem(const CSystem& other)
{
	//���͋�
}

//==============================================================================
//  �֐���        �`CSystem	
//  ����          CSystem�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CSystem::~CSystem()
{
	//���͋�
}

//==============================================================================
//  �֐���		 Initialize	
//  ����			 �V�X�e���̏����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CSystem::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	//�E�C���h�E�̃T�C�Y������
	screenWidth = 0;
	screenHeight = 0;

	//Windows API�̏�����
	InitializeWindows(screenWidth, screenHeight);

	//�L�[�{�[�h���͗p��Input �I�u�W�F�N�g����.
	m_Input = new CInput;
	if (!m_Input)
	{
		return false;
	}

	//Input �I�u�W�F�N�g�̏�����
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	//�V�[���Ǘ��҂�����������
	result = CScene::InitializeSceneManager(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}

	//���݂̃V�[�����^�C�g���V�[���ɂ���
	m_Scene = m_Scene->GetScene(CScene::SCENE_NAME::SCENE_TITLE);
	if (!m_Scene)
	{
		MessageBox(m_hwnd, L"Failed to Load Scene", L"Error", MB_OK);
		return false;
	}
	
	//�^�C�g���V�[��������������
	result = m_Scene->Initialize();
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Title Scene object.", L"Error", MB_OK);
		return false;
	}

/*
	//FPS�I�u�W�F�N�g����
	m_FPS = new CFps;
	if (!m_FPS)
	{
		return false;
	}

	//FPS�I�u�W�F�N�g������
	m_FPS->Initialize();

	//CPU�I�u�W�F�N�g����
	m_CPU = new CCpu;
	if (!m_CPU)
	{
		return false;
	}

	//CPU�I�u�W�F�N�g������
	m__CPU->Initialize();
	*/

	//�^�C�}�[ �I�u�W�F�N�g����
	m_Timer = new CTimer;
	if (!m_Timer)
	{
		return false;
	}

	//�^�C�}�[ �I�u�W�F�N�g������
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
//  �֐���		 Shutdown	
//  ����			 �V�X�e���̉��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CSystem::Shutdown()
{
	//�V�[�����������
	if (m_Scene)
	{
		m_Scene->Shutdown();
		m_Scene = 0;
	}

/*	
	//�ړ��Ǘ��I�u�W�F�N�g���������
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}
	*/
	//�^�C�}�[ �I�u�W�F�N�g���������
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}
	/*
	//CPU�I�u�W�F�N�g���������
	if (m_CPU)
	{
		m_CPU->Shutdown();
		delete m_CPU;
		m_CPU = 0;
	}

	//FPS�I�u�W�F�N�g���������
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

	//Input �I�u�W�F�N�g����
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	//�E�C���h�E����
	ShutdownWindows();

	return;
}

//==============================================================================
//  �֐���		 Run	
//  ����			 �V�X�e���̏����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CSystem::Run()
{
	MSG msg;
	bool done, result;

	//���b�Z�[�W�\���̂̏�����
	ZeroMemory(&msg, sizeof(MSG));
	done = false;

	//�Q�[�����[�v
	while (!done)
	{

		//�E�C���h�E���b�Z�[�W
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//�E�C���h�E��������ƃQ�[���I��
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			//�Q�[������
			result = Frame();
			if (!result)
			{
				MessageBox(m_hwnd, L"Frame Processing Failed", L"Error", MB_OK);
				done = true;
			}
		}

		//ESC�L�[�������ꂽ��A�Q�[�����I���
		if (m_Input->IsEscapePressed() == true)
		{
			done = true;
		}
	}

	return;
}

//==============================================================================
//  �֐���		 Frame	
//  ����			 ���t���[���̃Q�[�������X�V�֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CSystem::Frame()
{
	bool result;
	//float posX, posY, posZ;
	//float rotX, rotY, rotZ;

	
	//�V�X�e�������X�V����
	m_Timer->Frame(); 
//	m_FPS->Frame();
//	m_CPU->Frame();
	

	//���͍X�V
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
	//���͎擾
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
//  �֐���		 MessageHandle	
//  ����			 �E�C���h�E�̃��b�Z�[�W���Ǘ�����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			LRESULT
//==============================================================================
LRESULT CALLBACK CSystem::MessageHandle(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

//==============================================================================
//  �֐���		 InitializeWindows	
//  ����			 �E�C���h�E�̏������֐�
//------------------------------------------------------------------------------
//	����
//			int& screenWidth			��ʂ̕�
//          int& screenHeight			��ʂ̍���
//	�߂�l
//			�Ȃ�
//==============================================================================
void CSystem::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// ���I�u�W�F�N�g�ւ̃|�C���^���擾
	ApplicationHandle = this;

	// �C���X�^���X����
	m_hinstance = GetModuleHandle(NULL);

	//���O�ݒ�
	m_applicationName = NAME;

	//�E�C���h�E�ݒ�
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

	//�E�C���h�E�̓o�^
	RegisterClassEx(&wc);

	//�T�C�Y�ݒ�
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//�t���X�N���[���ݒ�
	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//�㍶�̈ʒu��0�ɂ���
		posX = posY = 0;
	}
	//�E�C���h�E�\���̐ݒ�
	else
	{
		//�E�C���h�E�T�C�Y�ݒ�
		screenWidth = SCREEN_WIDTH;
		screenHeight = SCREEN_HEIGHT;

		//�E�C���h�E��^�񒆂ɐݒu����
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//�E�C���h�E�������ăn���h�����擾����
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	//�E�C���h�E���J���A�A�N�e�B�u�ɂ���
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	//�}�E�X���\���ɂ���
	ShowCursor(false);

	return;
}

//==============================================================================
//  �֐���		 ShutdownWindows	
//  ����			 �E�C���h�E���������֐�
//------------------------------------------------------------------------------
//	����
//			�Ȃ�
//	�߂�l
//			�Ȃ�
//==============================================================================
void CSystem::ShutdownWindows()
{
	// �}�E�X��\������
	ShowCursor(true);

	//�t���X�N���[���̏ꍇ�A�E�C���h�E�ɖ߂�
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//�E�C���h�E���폜
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	//�A�v���P�[�V�����̃C���X�^���X���폜
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	//���݂̃N���X�ւ̃|�C���^�����
	ApplicationHandle = NULL;

	return;
}

//==============================================================================
//  �֐���		 WndProc	
//  ����			 �E�C���h�E�����b�Z�[�W���Ǘ�����֐�
//------------------------------------------------------------------------------
//	����
//			HWND     hwnd           �E�C���h�E �n���h��
//			UINT     uMessage       ���b�Z�[�W
//			WPARAM   wParam         �ǉ����
//			LPARAM   lParam         �ǉ����
//	�߂�l
//			LRESULT
//==============================================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		//�E�C���h�E���j�󂳂ꂽ�ꍇ
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	
		//�E�C���h�E������ꂽ�ꍇ
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		//����ȊO�̃��b�Z�[�W��System�N���X�ɑ���
		default:
		{
			return ApplicationHandle->MessageHandle(hwnd, uMessage, wParam, lParam);
		}
	}
}

//==============================================================================
//  �֐���		 HandleInput	
//  ����			 �C���v�b�g�Ǘ�����֐�
//------------------------------------------------------------------------------
//	����
//			float   frameTime          
//	�߂�l
//			bool    true ����          false�@���s
//==============================================================================
bool CSystem::HandleInput(float frameTime)
{
	
	bool key;
	CScene* newScene;

	//�V�[���J�ڂ��s��
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