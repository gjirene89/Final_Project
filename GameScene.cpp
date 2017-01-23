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
	m_Camera = new CCamera;
	if (!m_Camera)
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
		
	//objArray->LoadColorMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "Resources/Texture/sun.tga");

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