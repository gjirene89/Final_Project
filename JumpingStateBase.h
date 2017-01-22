//*****************************************************************************
//!	@file	JumpingStateBase.h
//!	@brief	�R�f�̃W�����v�̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_JUMPING_STATE_BASE__
#define __GM31_JUMPING_STATE_BASE__

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "MidairStateBase.h"

//=============================================================================
//!	@class	JumpingStateBase
//!	@brief �R�f�̃W�����v�̊�{��ԃN���X
//=============================================================================
class JumpingStateBase : public MidairStateBase
{
public:
	JumpingStateBase() :MidairStateBase(SACK_JUMP){};
	//void Enter(CSackBase* sack);			//�J�n�֐�
	void Action(CSackBase* sack);			//�����֐�
	void PostAction(CSackBase* sack);		//�㏈���֐�

	char* RenderDebug(void){ return "State : Jumping"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************