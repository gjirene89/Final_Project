//*****************************************************************************
//!	@file	MoveStateBase.h
//!	@brief	�R�f�̈ړ��̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "MoveStateBase.h"
# include "SackBaseClass.h"
# include "HitManager.h"
//# include "input.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	�J�n�֐�
//!	@param	CSackBase *sack		�R�f�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void MoveStateBase::Enter(CSackBase* sack)
{

}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CSackBase *sack		�R�f�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void MoveStateBase::PostAction(CSackBase* sack)
{
	//�����n�߂邩�A��ɉ����Ɠ���������AfallingState�ɂ���
	if (sack->GetImpulse().y < 0 ||
		HitManager::CheckStage(sack->m_hitUp) ||
		HitManager::CheckHit(sack->m_hitUp, GAMEHIT_TYPE::HIT_SACK) != nullptr)
	{
		sack->SetState(SACK_FALL);
	}

	MidairStateBase::PostAction(sack);
}


//******************************************************************************
//	End of file.
//******************************************************************************