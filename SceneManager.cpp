//************************************************************************//
//	SceneManager.cpp
//	2016-12-05
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
# include "SceneManager.h"
# include "TitleScene.h"
# include "GameScene.h"
# include "GameClearScene.h"
# include "ShaderManager.h"

//=======================================================================//
//		�O���[�o���ϐ�
//=======================================================================//
CScene* CScene::m_titleScene     = nullptr;
CScene* CScene::m_gameScene      = nullptr;
CScene* CScene::m_gameClearScene = nullptr;

CDirect3D*  CScene::m_Direct3D = nullptr;

//==============================================================================
//	�֐���		InitializeSceneManager
//	����	        �V�[���Ǘ��҂̏�����
//------------------------------------------------------------------------------
//	����
//          int		screenWidth			��ʂ̕�
//			int		screenHeight		��ʂ̍���
//			HWND	hwnd				�E�C���h�E�n���h��
//	�߂�l
//          �Ȃ�
//==============================================================================
bool CScene::InitializeSceneManager(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	//DirectX�@�I�u�W�F�N�g����
	m_Direct3D = new CDirect3D;
	if (!m_Direct3D)
	{
		return false;
	}

	//DirectX�@�I�u�W�F�N�g�̏�����
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	//�V�F�[�_�[�Ǘ��҂̏�����
	CShaderManager::getInstance().Initialize(m_Direct3D->GetDevice(), hwnd);

	return true;
}

//==============================================================================
//	�֐���		Initialize
//	����	        �Q�[���I�u�W�F�N�g�̏��������Ăяo��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
bool CScene::Initialize()
{
	CGameObjectBase* tempObj;
	
	tempObj = objArray;
	while (tempObj)
	{
		tempObj->Initialize();
		tempObj = tempObj->GetNextObj();
	}

	m_Camera->Initialize();

	return true;
}

//==============================================================================
//	�֐���		Input
//	����	        �Q�[�����̓���
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CScene::Input(CInput* input)
{
	CGameObjectBase* tempObj;
	tempObj = objArray;

	while (tempObj)
	{
		tempObj->Input(input);
		tempObj = tempObj->GetNextObj();
	}
	return;
}

//==============================================================================
//	�֐���		Render
//	����	        �Q�[���I�u�W�F�N�g�̕`����Ăяo��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          bool		true ����          false�@���s
//==============================================================================
bool CScene::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	XMFLOAT3 cameraPosition;
	CGameObjectBase* tempObj;

	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();
	
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	cameraPosition = m_Camera->GetPosition();

	tempObj = objArray;
	while (tempObj)
	{
		tempObj->Render(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, cameraPosition, m_Light);
		tempObj = tempObj->GetNextObj();
	}

	m_Direct3D->EndScene();

	return true;
}

//==============================================================================
//	�֐���		Action
//	����	        �Q�[���I�u�W�F�N�g�̏����֐����Ăяo��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CScene::Action()
{
	CGameObjectBase* tempObj;
	
	m_Camera->Action();

	tempObj = objArray;
	while (tempObj)
	{
		tempObj->Action();
		tempObj = tempObj->GetNextObj();
	}

	return;
}

//==============================================================================
//	�֐���		PostAction
//	����	        �Q�[���I�u�W�F�N�g�̌㏈���֐����Ăяo��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CScene::PostAction()
{
	CGameObjectBase* tempObj;
	tempObj = objArray;

	while (tempObj)
	{
		tempObj->PostAction();
		tempObj = tempObj->GetNextObj();
	}

	return;
}

//==============================================================================
//	�֐���		GetScene
//	����	        ���݂̃V�[���ւ̃|�C���^��߂�
//------------------------------------------------------------------------------
//	����
//          SCENE_NAME   sceneName      �V�[����
//	�߂�l
//          CScene*      �V�[���ւ̃|�C���^
//==============================================================================
CScene* CScene::GetScene(SCENE_NAME sceneName)
{
	bool result;
	//�V�[���̃|�C���^��߂��B�V�[�������݂��Ȃ��ꍇ�A��������
	switch (sceneName)
	{
		case SCENE_TITLE : 
			if (m_titleScene == nullptr)
			{
				m_titleScene = new CTitleScene();
				result = m_titleScene->LoadScene();
				if (!result)	return nullptr;
			}
			return m_titleScene;

		case SCENE_GAME  : 
			if (m_gameScene == nullptr)
			{
				m_gameScene = new CGameScene();
				result = m_gameScene->LoadScene();
				if (!result)	return nullptr;
			}
			return m_gameScene;

		case SCENE_CLEAR : 
			if (m_gameClearScene == nullptr)
			{
				m_gameClearScene = new CGameClearScene();
				result = m_gameClearScene->LoadScene();
				if (!result)	return nullptr;
			}
			return m_gameClearScene;
	}

	return nullptr;
}

//==============================================================================
//	�֐���		Shutdown
//	����	        �V�[�����������
//------------------------------------------------------------------------------
//	����
//          SCENE_NAME   sceneName      �V�[����
//	�߂�l
//          CScene*      �V�[���ւ̃|�C���^�[
//==============================================================================
void CScene::Shutdown()
{
	CShaderManager::getInstance().Shutdown();

	//DirectX�̃I�u�W�F�N�g���������
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = nullptr;
	}
	
	//�V�[���ւ̃|�C���^�[�����
	if (m_titleScene != nullptr)
	{
		m_titleScene->ShutdownSceneObjects();
		delete m_titleScene;
	}

	if (m_gameScene != nullptr)
	{
		m_gameScene->ShutdownSceneObjects();
		delete m_gameScene;
	}

	if (m_gameClearScene != nullptr)
	{
		m_gameClearScene->ShutdownSceneObjects();
		delete m_gameClearScene;
	}


	return;

}

void CScene::ShutdownSceneObjects(void)
{
	CGameObjectBase* nextObj;

	while (objArray)
	{
		nextObj = objArray->GetNextObj();
		delete objArray;
		objArray = nextObj;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = nullptr;
	}

	if (m_Light)
	{
		delete m_Light;
		m_Light = nullptr;
	}
}

//******************************************************************************
//	End of file.
//******************************************************************************