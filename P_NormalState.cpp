//*****************************************************************************
//!	@file	NormalState.h
//!	@brief	�v���C���[�̕��ʏ�ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "P_NormalState.h"
//# include "input.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	�J�n�֐�
//!	@param	CSackBase *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void NormalState::Enter(CSackBase* player)
{
	//player->SetMesh(ModelManager::GetModel(ModelManager::MODEL_PLAYER_NORMAL));
}

//==============================================================================
//!	@fn		Input
//!	@brief	���͊֐�
//!	@param	CSackBase *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void NormalState::Input(CInput* input, CSackBase* player)
{
	
	//�E�ֈړ�
	if (input->IsRightPressed())
	{
		player->SetState(SACK_MOVE);
		player->MoveRight();
	}

	//���ֈړ�
	if (input->IsLeftPressed())
	{
		player->SetState(SACK_MOVE);
		player->MoveLeft();
	}
	//�W�����v
	if (input->IsUpPressed())		player->SetState(SACK_JUMP);

	//�R��U���
	if (input->IsFlipTriggered())		player->SetState(SACK_FLIP);

	//�_�b�V���[
	if (input->IsDashTriggered())		player->SetState(SACK_DASH);
	
}

//==============================================================================
//!	@fn		Action
//!	@brief	�����֐�
//!	@param	CSackBase *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void NormalState::Action(CSackBase* player)
{
	//�X�s�[�h�𗎂Ƃ��֐����Ăяo��
	player->Slide();
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CSackBase *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void NormalState::PostAction(CSackBase* player)
{
	//���ɉ����Ȃ���΁A����������
	if (!HitManager::CheckStage(player->m_hitDown) && HitManager::CheckHit(player->m_hitDown, GAMEHIT_TYPE::HIT_SACK) == nullptr)
		player->SetState(SACK_FALL);

	if (HitManager::CheckStage(player->m_hitLeft) ||
		HitManager::CheckStage(player->m_hitRight) ||
		HitManager::CheckHit(player->m_hitLeft, GAMEHIT_TYPE::HIT_SACK) ||
		HitManager::CheckHit(player->m_hitRight, GAMEHIT_TYPE::HIT_SACK))
	{
		player->SetImpulseX(0);
		player->ResetPositionX();
		//	player->SetState(CPlayer::normalState);
	}
}


//******************************************************************************
//	End of file.
//******************************************************************************