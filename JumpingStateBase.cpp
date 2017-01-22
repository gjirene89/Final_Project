//*****************************************************************************
//!	@file	JumpingStateBase.h
//!	@brief	�R�f�̃W�����v�̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "JumpingStateBase.h"
# include "CSackBase.h"

//==============================================================================
//!	@fn		Action
//!	@brief	�����֐�
//!	@param	CSackBase*	sack		�R�f�ւ̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void JumpingStateBase::Action(CSackBase* sack)
{
	MidairStateBase::Action(sack);
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CSackBase*	sack		�R�f�ւ̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void JumpingStateBase::PostAction(CSackBase* sack)
{
	//�����n�߂邩�A��ɉ����Ɠ���������AfallingState�ɂ���
	if (sack->GetImpulse().y < 0 ||
		HitManager::CheckStage(sack->hitUp) ||
		HitManager::CheckHit(sack->hitUp, GAMEHIT_TYPE::HIT_SACK) != nullptr)
	{
		sack->SetState(SACK_FALL);
		return;
	}

	MidairStateBase::PostAction(sack);

}


//******************************************************************************
//	End of file.
//******************************************************************************