//*****************************************************************************
//!	@file	MoveState.h
//!	@brief	�v���C���[�̈ړ���ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "P_MoveState.h"
//# include "input.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	�J�n�֐�
//!	@param	CPlayer *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void MoveState::Enter(CSackBase* player)
{
	player->StartAnimation(CSackBase::MODEL_MOVE_JUMP, 10);

	MidairState::Enter(player);

	/*
	//���֓�����
	if (GetKeyboardPress(DIK_A))
	{
		player->MoveLeft();
		return;
	}

	//�E�֓�����
	if (GetKeyboardPress(DIK_D))
	{
		player->MoveRight();
		return;
	}
	*/
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CPlayer *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void MoveState::PostAction(CSackBase* player)
{
	//�����n�߂邩�A��ɉ����Ɠ���������AfallingState�ɂ���
	if (player->GetImpulse().y < 0 ||
		HitManager::CheckStage(player->m_hitUpOut) ||
		HitManager::CheckHit(player->m_hitUpOut, GAMEHIT_TYPE::HIT_SACK) != nullptr)
	{
		player->SetState(SACK_FALL);
	}

	MidairState::PostAction(player);
	
}


//******************************************************************************
//	End of file.
//******************************************************************************