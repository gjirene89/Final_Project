//*****************************************************************************
//!	@file	FallingState.h
//!	@brief	�v���C���[�̗�����ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
# include "P_FallingState.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	�J�n�֐�
//!	@param	CPlayer *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void FallingState::Enter(CSackBase* player)
{
//	player->SetMesh(ModelManager::GetModel(ModelManager::MODEL_PLAYER_NORMAL));
//	player->SetImpulseX(0);
}

//==============================================================================
//!	@fn		Action
//!	@brief	�����֐�
//!	@param	CPlayer *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void FallingState::Action(CSackBase* player)
{

	MidairState::Action(player);
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�㏈���֐�
//!	@param	CPlayer *player		�v���C���[�̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void FallingState::PostAction(CSackBase* player)
{
	CSackBase *tempSack = (CSackBase*)HitManager::CheckHit(player->m_hitDown, GAMEHIT_TYPE::HIT_SACK);
	//���ɉ��ɂ���������AnormalState�ɂ���
	if (HitManager::CheckStage(player->m_hitDown))
	{
		//player->SetOldPositionY();
		player->SetImpulseY(0.0f);
		player->CleanNumbers();
		player->SetState(SACK_NORMAL);
	}
	else if (tempSack!=nullptr)
	{
		//player->SetOldPositionY();
		player->SetImpulseY(0.0f);
		if (tempSack->GetState()->GetStateName() == SACK_NORMAL )
			player->SetState(SACK_NORMAL);
	}

	MidairState::PostAction(player);
}

//******************************************************************************
//	End of file.
//******************************************************************************