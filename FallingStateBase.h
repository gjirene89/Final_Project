//*****************************************************************************
//!	@file	FallingStateBase.h
//!	@brief	�R�f�̗����̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_FALLING_STATE_BASE__
#define __GM31_FALLING_STATE_BASE__

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "MidairStateBase.h"

//=============================================================================
//!	@class	FallingStateBase
//!	@brief  �R�f�̗����̊�{��ԃN���X
//=============================================================================
class FallingStateBase : public MidairStateBase
{
public:
	FallingStateBase() :MidairStateBase(SACK_FALL){};
	void Enter(CSackBase* sack);			//�J�n�֐�
	void Action(CSackBase* sack);			//�����֐�
	void PostAction(CSackBase* sack);		//�㏈���֐�

	char* RenderDebug(void){ return "State : Falling"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************