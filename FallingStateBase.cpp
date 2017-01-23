//*****************************************************************************
//!	@file	FallingStateBase.h
//!	@brief	�R�f�̗����̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
# include "FallingStateBase.h"
# include "SackBaseClass.h"
# include "MathUtility.h"
# include "HitManager.h"
# include "Macros.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	�J�n�֐�
//!	@param	CSackBase *sack		�R�f�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void FallingStateBase::Enter(CSackBase* sack)
{
	sack->SetImpulseY(0);
}

//==============================================================================
//!	@fn		Action
//!	@brief	�����֐�
//!	@param	CSackBase *sack		�R�f�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void FallingStateBase::Action(CSackBase* sack)
{
	MidairStateBase::Action(sack);
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CSackBase *sack		�R�f�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void FallingStateBase::PostAction(CSackBase* sack)
{

	//���ɉ��ɂ���������AnormalState�ɂ���
	if (HitManager::CheckStage(sack->m_hitDown))
	{
		sack->SetImpulseY(0.0f);
		sack->CleanNumbers();
		sack->SetState(SACK_NORMAL);
	}
	else if (HitManager::CheckHit(sack->m_hitDown, GAMEHIT_TYPE::HIT_SACK))
	{
		sack->SetImpulseY(0.0f);
		sack->SetState(SACK_NORMAL);
	}

	MidairStateBase::PostAction(sack);

	if (sack->GetParent() == nullptr) return;
	if (sack->GetParent()->GetState()->GetStateName() != SACK_NORMAL)	return;

	if (CalculateDistance(sack->GetHookPos(), sack->GetParent()->GetHookPos()) > ROPE_LENGHT &&
		sack->GetRopePullAngle() > 0.0f)
	{
		sack->ResetPositionY();
		sack->SetImpulseY(0);
		
			sack->SetState(SACK_NORMAL);
		
		return;
	}

}

//******************************************************************************
//	End of file.
//******************************************************************************