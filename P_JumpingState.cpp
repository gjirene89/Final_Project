//*****************************************************************************
//!	@file	JumpingState.h
//!	@brief	�v���C���[�̃W�����v��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "P_JumpingState.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	�J�n�֐�
//!	@param	CSackBase *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void JumpingState::Enter(CSackBase* player)
{
	//��ɉ����Ȃ���΁A�W�����v�֐����Ăяo��
	if (!HitManager::CheckStage(player->m_hitUp) &&
		HitManager::CheckHit(player->m_hitUp, GAMEHIT_TYPE::HIT_SACK) == nullptr)
	{
		player->Jump();
		player->StartAnimation(CSackBase::MODEL_JUMP, 10);
		MidairState::Enter(player);
	}
}

//==============================================================================
//!	@fn		Action
//!	@brief	�����֐�
//!	@param	CSackBase *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void JumpingState::Action(CSackBase* player)
{
	MidairState::Action(player);
	
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CSackBase *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void JumpingState::PostAction(CSackBase* player)
{
	//�����n�߂邩�A��ɉ����Ɠ���������AfallingState�ɂ���
	if (player->GetImpulse().y < 0||
		HitManager::CheckStage(player->m_hitUp) ||
		HitManager::CheckHit(player->m_hitUp, GAMEHIT_TYPE::HIT_SACK))
	{
		player->SetState(SACK_FALL);
		return;
	}

	MidairState::PostAction(player);
	
}


//******************************************************************************
//	End of file.
//******************************************************************************