//*****************************************************************************
//!	@file	DashingStateBase.cpp
//!	@brief	�R�f�̃_�b�V���̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "DashingStateBase.h"
# include "SackBaseClass.h"
# include "HitManager.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	�J�n�֐�
//!	@param	CSackBase *sack		�R�f�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void DashingStateBase::Enter(CSackBase* sack)
{
	//�_�b�V���[�֐����Ăяo��
	sack->Dash();
}

//==============================================================================
//!	@fn		Action
//!	@brief	�����֐�
//!	@param	CSackBase *sack		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void DashingStateBase::Action(CSackBase* sack)
{
	//�w���̃X�s�[�h�����炷
	sack->Slide();
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CSackBase *sack		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void DashingStateBase::PostAction(CSackBase* sack)
{
	//�����Ȃ��Ȃ�����AnormalState�ɖ߂�
	if (sack->GetImpulse().x == 0)
		sack->SetState(SACK_NORMAL);

	if (sack->GetImpulse().x > 0)
	{
		if (HitManager::CheckStage(sack->m_hitRight) ||
			HitManager::CheckHit(sack->m_hitRight, GAMEHIT_TYPE::HIT_SACK))
		{
			sack->SetImpulseX(0);
			sack->ResetPositionX();
			sack->SetState(SACK_NORMAL);
		}
	}

	if (sack->GetImpulse().x < 0)
	{
		if (HitManager::CheckStage(sack->m_hitLeft) ||
			HitManager::CheckHit(sack->m_hitLeft, GAMEHIT_TYPE::HIT_SACK))
		{
			sack->SetImpulseX(0);
			sack->ResetPositionX();
			sack->SetState(SACK_NORMAL);
		}
	}
}



//******************************************************************************
//	End of file.
//******************************************************************************