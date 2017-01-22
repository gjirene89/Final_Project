//*****************************************************************************
//!	@file	HitManager.cpp
//!	@brief	
//!	@note	�����蔻��p
//!	@author	�C���l�@�w���Z�m�E�C�X�@�n�\
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
# include "HitManager.h"
//# include "CDirectxGraphics.h"
# include <stdio.h>
//# include "Debug.h"
//# include "input.h"

//-----------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-----------------------------------------------------------------------------
int HitManager::nHitCnt;
CHit_Base* HitManager::hitList[MAX_HIT_CNT];

//==============================================================================
//!	@fn		HitManager
//!	@brief	�����蔻��̔z��̃R���X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
HitManager::HitManager(void)
{
	//font.CreateFontA();
	isVisible = false;
	nHitCnt = 0;

}

//==============================================================================
//!	@fn		~HitManager()
//!	@brief	�����蔻��̔z��̃f�X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
HitManager::~HitManager(void)
{
	isVisible = false;
	nHitCnt = 0;
}

//==============================================================================
//!	@fn		Init
//!	@brief	�����蔻��̔z��̃f�[�^������������
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void HitManager::Init(void)
{
	//�����[���ɖ߂�
	nHitCnt = 0;
}

//==============================================================================
//!	@fn		Reset
//!	@brief	�����蔻��̔z��̃f�[�^�����Z�b�g����
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void HitManager::Reset(void)
{
	//�����[���ɖ߂�
	nHitCnt = 0;
}


//==============================================================================
//!	@fn		Render
//!	@brief	�����蔻���`�悷��
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void HitManager::Render(void)
{
	//if (CDebug::GetIsHidden() || !CDebug::displayCollision)	return;

	for (int i = 0; i < nHitCnt; i++)
	{
		hitList[i]->Render();
	}
}

//==============================================================================
//!	@fn		AddHit
//!	@brief	�����蔻��̔z��ɃI�u�W�F�N�g��ǉ�����
//!	@param	GameObjHit	�ǉ�����I�u�W�F�N�g
//!	@retval	�Ȃ�
//==============================================================================
void HitManager::AddHit(CHit_Base *newObj)
{
	//�z��̍ő吔�𒴂�����A�ǉ����Ȃ�
	if (nHitCnt >= MAX_HIT_CNT)
		return;

	//�I�u�W�F�N�g��ǉ�����
	hitList[nHitCnt] = newObj;
	hitList[nHitCnt]->Initialize();
	nHitCnt++;
}

//==============================================================================
//!	@fn		CheckHit
//!	@brief	�����蔻��̔z��ɃI�u�W�F�N�g��ǉ�����
//!	@param	GameObjHit	�I�u�W�F�N�g���g
//! @param	GAMEOBJTYPE �T���Ă���I�u�W�F�N�g�̎��
//!	@retval	true : �������Ă���@�@�@false : �������Ă��Ȃ�
//==============================================================================
CGameObjectBase* HitManager::CheckHit(CHit_Base *pHit, GAMEHIT_TYPE  objType)
{
	CGameObjectBase* tempHit;
	for (int i = 0; i < nHitCnt; i++)
	{
		tempHit = pHit->CheckHit(hitList[i], objType);
		if (tempHit!=nullptr)
		{
			pHit->Highlight();
			return tempHit;
		}
	}

	return nullptr;
}

bool HitManager::CheckStage(CHit_Base *pHit)
{
	return pHit->CheckStage();
}

//******************************************************************************
//	End of file.
//******************************************************************************
