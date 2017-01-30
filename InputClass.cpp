//************************************************************************//
//	inputClass.cpp
//	2016-11-02
//	Irene Gersenowies
//************************************************************************//
#include "inputClass.h"

//==============================================================================
//  �֐���        CInput	
//  ����          CInput�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CInput::CInput()
{
	//������
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
}

//==============================================================================
//  �֐���        CInput	
//  ����          CInput�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CInput& other			CInput�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CInput::CInput(const CInput& other)
{
	//��
}

//==============================================================================
//  �֐���        CInput	
//  ����          CInput�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CInput::~CInput()
{
	//��
}

//==============================================================================
//  �֐���		 Initialize	
//  ����			 ���̓N���X�̏������֐�
//------------------------------------------------------------------------------
//	����
//          HINSTANCE   hInstance			�E�C���h�E �C���X�^���X
//          HWND        hwnd                �E�C���h�E �n���h��
//          int         screenWidth         ��ʂ̕�
//          int         screenHeight        ��ʂ̍���
//	�߂�l
//			bool        true �����@�@�@false ���s
//==============================================================================
bool CInput::Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;
	int i;

	//��ʃT�C�Y�ݒ�
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	//�}�E�X�ʒu�̏�����
	m_mouseX = 0;
	m_mouseY = 0;

	// �S�L�[��Ԃ̔z���false�ɂ���
	for (i = 0; i<256; i++)
	{
		m_keyboardState[i] = false;
		m_keyboardStateOld[i] = false;
	}


	//���̓C���^�t�F�[�X�̏�����
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	//�L�[�{�[�h���͂̏�����
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	//�f�[�^�`����ݒ肷��(�L�[�{�[�h�p�j
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	//�L�[�{�[�h���͂����ʂ��Ȃ��Ƃ����ݒ�ɂ���
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	//�L�[�{�[�h�擾
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	//�}�E�X������
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	//�f�[�^�`����ݒ肷��(�}�E�X�p�j
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	//�}�E�X���͂����ʂł���悤�ɐݒ�ɂ���
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	//�}�E�X�擾
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//==============================================================================
//  �֐���		 Shutdown	
//  ����			 ���̓N���X�̉��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CInput::Shutdown()
{
	//�}�E�X�����
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	//�L�[�{�[�h�����
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	//���̓C���^�t�F�[�X�����
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}

//==============================================================================
//  �֐���		 Frame	
//  ����			 ���t���[���̓��͍X�V�֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CInput::Frame()
{
	bool result;

	//�L�[�{�[�h��Ԃ��擾
	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	//�}�E�X��Ԃ��擾
	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	//���̓f�[�^�̏���
	ProcessInput();

	return true;
}

//==============================================================================
//  �֐���		 ReadKeyboard	
//  ����			 �L�[�{�[�h��Ԃ��擾����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CInput::ReadKeyboard()
{
	int i;
	HRESULT result;

	//�O�̃t���[���̏�Ԃ�ۑ�����
	for (i = 0; i<256; i++)
	{
		m_keyboardStateOld[i] = m_keyboardState[i];
	}

	//�L�[�{�[�h���擾
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		//�A�N�Z�X������������A�Ď擾����
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
//  �֐���		 ReadMouse	
//  ����			 �}�E�X��Ԃ��擾����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CInput::ReadMouse()
{
	HRESULT result;

	//�}�E�X���擾
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		//�A�N�Z�X������������A�Ď擾����
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
//  �֐���		 ProcessInput	
//  ����			 ���̓f�[�^����������֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CInput::ProcessInput()
{
	//�}�E�X�̈ʒu���X�V����
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	//�}�E�X����ʂ���o�Ȃ��悤�ɍ��W�ʒu�𐧌�����
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	return;
}

//==============================================================================
//  �֐���		 IsSpaceTriggered
//  ����			 SpaceBar���g���K�[����邩�ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �g���K�[���ꂽ�@�@�@false �g���K�[����Ă��Ȃ�
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
//  �֐���		 IsEnterTriggered
//  ����			 Enter�L�[���g���K�[����邩�ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �g���K�[���ꂽ�@�@�@false �g���K�[����Ă��Ȃ�
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
//  �֐���		 IsEscapePressed	
//  ����			 ESC�L�[�������ꂽ���ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true ������Ă���@�@�@false ������Ă��Ȃ�
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
//  �֐���		 IsRightPressed	
//  ����			 �E��� (��) �������ꂽ���ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true ������Ă���@�@�@false ������Ă��Ȃ�
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
//  �֐���		 IsLeftPressed	
//  ����			 ����� (��) �������ꂽ���ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true ������Ă���@�@�@false ������Ă��Ȃ�
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
//  �֐���		 IsUpPressed	
//  ����			 ���� (��) �������ꂽ���ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true ������Ă���@�@�@false ������Ă��Ȃ�
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
//  �֐���		 IsDownPressed	
//  ����			 ����� (��) �������ꂽ���ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true ������Ă���@�@�@false ������Ă��Ȃ�
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
//  �֐���		 IsDashTriggered
//  ����			 �_�b�V���J�n�̃L�[���g���K�[���ꂽ���ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true ������Ă���@�@�@false ������Ă��Ȃ�
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
//  �֐���		 IsFlipTriggered
//  ����			 �p�^�p�^�J�n�̃L�[���g���K�[����邩�ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true ������Ă���@�@�@false ������Ă��Ȃ�
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
//  �֐���		 IsF1Pressed	
//  ����			 F1�L�[�������ꂽ���ǂ����m�F����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true ������Ă���@�@�@false ������Ă��Ȃ�
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
//  �֐���		 GetMouseLocation	
//  ����			 �}�E�X�̈ʒu���Q�b�g����֐�
//------------------------------------------------------------------------------
//	����
//			int&    mouseX				�}�E�X��X��
//			int&    mouseY				�}�E�X��Y��
//	�߂�l
//          �Ȃ�
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