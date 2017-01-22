//*****************************************************************************
//!	@file	DashingStateBase.h
//!	@brief	�R�f�̃_�b�V���̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_DASHING_STATE_BASE__
#define __GM31_DASHING_STATE_BASE__

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "SackStateBase.h"

//=============================================================================
//!	@class	DashingStateBase
//!	@brief �R�f�̃_�b�V���̊�{��ԃN���X
//=============================================================================
class DashingStateBase : public SackStateBase
{
public:
	DashingStateBase() : SackStateBase(SACK_DASH){};
	void Enter(CSackBase* sack);			//�J�n�֐�
	void Action(CSackBase* sack);			//�����֐�
	void PostAction(CSackBase* sack);		//�㏈���֐�

	char* RenderDebug(void){ return "State : Dash"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************