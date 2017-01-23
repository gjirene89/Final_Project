//*****************************************************************************
//!	@file	NormalStateBase.h
//!	@brief	�R�f�̕��ʂ̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "NormalStateBase.h"
# include "SackBaseClass.h"
//# include "input.h"
# include "PlayerClass.h"
# include "MathUtility.h"
# include "HitManager.h"
# include "Macros.h"

//==============================================================================
//!	@fn		Action
//!	@brief	�����֐�
//!	@param	CSackBase *sack		�R�f�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void NormalStateBase::Action(CSackBase* sack)
{
	//�X�s�[�h�𗎂Ƃ��֐����Ăяo��
	sack->Slide();

}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CSackBase *sack		�R�f�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void NormalStateBase::PostAction(CSackBase* sack)
{
	//���ɉ����Ȃ���΁A����������
	if (!HitManager::CheckStage(sack->m_hitDown) &&
		HitManager::CheckHit(sack->m_hitDown, GAMEHIT_TYPE::HIT_SACK) == nullptr)
	{
		if (sack->GetParent() == nullptr)
		{
			sack->SetState(SACK_FALL);
		}
		else if (CalculateDistance(sack->GetWorldPos(), sack->GetParent()->GetWorldPos()) < SACK_RADIUS * 2.0f ||
			CalculateAngle(sack->GetWorldPos(), sack->GetParent()->GetWorldPos()) < 0.0f)
		{
			sack->SetState(SACK_FALL);
		}
	}

	//�����ƂԂ�������A�������~�܂�
	if (HitManager::CheckStage(sack->m_hitLeft) ||
		HitManager::CheckStage(sack->m_hitRight) ||
		HitManager::CheckHit(sack->m_hitLeft, GAMEHIT_TYPE::HIT_SACK) ||
		HitManager::CheckHit(sack->m_hitRight, GAMEHIT_TYPE::HIT_SACK))
	{
		sack->SetImpulseX(0);
		sack->ResetPositionX();
	}

	//���̏R�f����ɏ���Ă�����`�F�b�N����
	sack->Chain();

	//�e������΁A�R�f����������
	sack->Pull();

	//�Ԃ���ꂽ��A����
	sack->Dash();
}


//******************************************************************************
//	End of file.
//******************************************************************************