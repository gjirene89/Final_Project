//*****************************************************************************
//  GameClearScene.cpp
//  2017-01-14
//  Irene Gersenowies
//*****************************************************************************

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
# include "GameClearScene.h"

//==============================================================================
//	�֐���		CGameClearScene
//	����	        �Q�[���N���A�V�[���̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CGameClearScene::CGameClearScene()
{
	sceneName = SCENE_CLEAR;

	objArray = nullptr;

	return;
}

//==============================================================================
//	�֐���		Initialize
//	����	        �Q�[���N���A�V�[���̏�����
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CGameClearScene::Initialize(void)
{
	m_Camera->SetPosition(0, 0, -10);

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
CScene* CGameClearScene::ChangeScene(bool isChange)
{
	if (!isChange)
		return this;

	return GetScene(SCENE_TITLE);
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
bool CGameClearScene::LoadScene(void)
{
	bool result;
	CGameObjectBase* tempObj;

	//�J�����I�u�W�F�N�g�̐���
	m_Camera = new CCamera;
	if (!m_Camera)
	{
		return false;
	}

	//�I�u�W�F�N�g�̒ǉ�
	objArray = new CPlane(10, 10);
	if (!objArray)
	{
		return false;
	}

	//�|���̃e�N�X�`���ǉ�
	result = ((CPlane*)objArray)->LoadColorTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "Resources/Texture/wallColor.tga", 10, 10);
	if (!result)
	{
		return false;
	}


	//�I�u�W�F�N�g�̏�����
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