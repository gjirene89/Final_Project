//************************************************************************//
//	GameScene.cpp
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
# include "GameScene.h"


//==============================================================================
//	�֐���		CGameScene
//	����	        �Q�[���V�[���̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CGameScene::CGameScene()
{
	sceneName = SCENE_GAME;

	objArray = nullptr;

	return;
}


//==============================================================================
//	�֐���		Initialize
//	����	        �V�[���̃Q�[���I�u�W�F�N�g�̏��������Ăԏo��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CGameScene::Initialize()
{
	m_Camera->SetPosition(50, 50, -50);

	m_Light->SetAmbientColor(0.26f, 0.24f, 0.30f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 0.99f, 0.79f, 1.0f);
	m_Light->SetDirection(-0.25f, -1.0f, 0.5f);
	m_Light->SetPosition(500.0f, 500.0f, -50.0f);
	m_Light->SetLookAt(0.0f, 0.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(30.0f);
	m_Light->GenerateOrthoMatrix(20.0f, 20.0f, SHADOW_MAP_DEPTH, SHADOW_MAP_NEAR);

	CScene::Initialize();

	return true;
}

//==============================================================================
//	�֐���		ChangeScene
//	����	        �V�[���J��
//------------------------------------------------------------------------------
//	����
//          bool    isChange		�J�ڂ��邩�ǂ����������t���O
//	�߂�l
//			CScene*	�@              �V�����V�[��
//==============================================================================
CScene* CGameScene::ChangeScene(bool isChange)
{
	if (!isChange)
		return this;
	
	return GetScene(SCENE_CLEAR);
}

//==============================================================================
//	�֐���		LoadScene
//	����	        �V�[���̃I�u�W�F�N�g�����[�h����
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CGameScene::LoadScene(void)
{
	bool result;
	CGameObjectBase* tempObj;

	//�J�����I�u�W�F�N�g�̐���
	m_Camera = new CTrackingCamera();
	if (!m_Camera)
	{
		return false;
	}

	//���̃I�u�W�F�N�g����
	m_Light = new CLight();
	if (!m_Light)
	{
		return false;
	}

	//�I�u�W�F�N�g�̒ǉ�
	objArray = new CStage();
	if (objArray == nullptr)
	{
		//error message
		return false;
	}

	objArray->SetNextObj(new CPlayer(4,5));
	tempObj = objArray->GetNextObj();
	if(tempObj == nullptr)
	{
		//error message
		return false;
	}
	
	((CTrackingCamera*)m_Camera)->SetTarget(tempObj);
		
	tempObj = objArray;
	while (tempObj)
	{
		result = tempObj->InitializeObject(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
		if (!result)
		{
			//error message
			return false;
		}
		tempObj = tempObj->GetNextObj();
	}

	return true;

}

//******************************************************************************
//	End of file.
//******************************************************************************