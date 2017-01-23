//*****************************************************************************
//!	@file	NormalState.h
//!	@brief	�v���C���[�̕��ʏ�ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_NORMAL_STATE__
#define __GM31_NORMAL_STATE__

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "PlayerState.h"

//=============================================================================
//!	@class	NormalState
//!	@brief �v���C���[�̕��ʏ�ԃN���X
//=============================================================================
class NormalState : public PlayerState
{
public:
	NormalState() : PlayerState(SACK_NORMAL){};
	void Enter(CSackBase* player);
	void Input(CInput* input, CSackBase* player);			//���͊֐�
	void Action(CSackBase* player);			//�����֐�
	void PostAction(CSackBase* player);		//�㏈���֐�

	char* RenderDebug(void){ return "State : Normal"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************