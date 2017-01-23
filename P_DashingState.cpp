//*****************************************************************************
//!	@file	DashingState.cpp
//!	@brief	�v���C���[�̃_�b�V����ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "P_DashingState.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	�J�n�֐�
//!	@param	CPlayer *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void DashingState::Enter(CSackBase* player)
{
	//�_�b�V���[�֐����Ăяo��
	player->Dash();
}

//==============================================================================
//!	@fn		Action
//!	@brief	�����֐�
//!	@param	CPlayer *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void DashingState::Action(CSackBase* player)
{
	//�w���̃X�s�[�h�����炷
	player->Slide();
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CPlayer *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void DashingState::PostAction(CSackBase* player)
{
	//�����Ȃ��Ȃ�����AnormalState�ɖ߂�
	if (player->GetImpulse().x == 0)
	{
		player->SetState(SACK_NORMAL);
		return;
	}
	//�ǂƓ���������~�܂�
	if (HitManager::CheckStage(player->m_hitLeft) ||
		HitManager::CheckStage(player->m_hitRight) )
	{
		player->SetImpulseX(0);
		player->ResetPositionX();
		player->SetState(SACK_NORMAL);
		return;
	}

	//�R�f�Ɠ���������A�����o��
	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(player->m_hitLeft, GAMEHIT_TYPE::HIT_SACK);

	if (tempObj!=nullptr)
	{
		tempObj->SetImpulseX(-DASH_FORCE);
		tempObj->SetState(SackStateBase::SACK_DASH);
		player->SetImpulseX(0);
		player->ResetPositionX();
		player->SetState(SACK_NORMAL);
		
		return;
	}

	tempObj = (CSackBase*)HitManager::CheckHit(player->m_hitRight, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		tempObj->SetImpulseX(DASH_FORCE);
		tempObj->SetState(SackStateBase::SACK_DASH);
		player->SetImpulseX(0);
		player->ResetPositionX();
		player->SetState(SACK_NORMAL);
		
		return;
	}

}



//******************************************************************************
//	End of file.
//******************************************************************************