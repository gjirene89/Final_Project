//*****************************************************************************
//!	@file	DashingState.h
//!	@brief	�v���C���[�̃_�b�V����ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_DASHING_STATE__
#define __GM31_DASHING_STATE__

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "PlayerState.h"

//=============================================================================
//!	@class	DashingState
//!	@brief �v���C���[�̃_�b�V����ԃN���X
//=============================================================================
class DashingState : public PlayerState
{
public:
	DashingState() : PlayerState(SACK_DASH){};
	void Enter(CSackBase* player);			//�J�n�֐�
	void Action(CSackBase* player);			//�����֐�
	void PostAction(CSackBase* player);		//�㏈���֐�

	char* RenderDebug(void){ return "State : Dash"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************