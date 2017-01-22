//*****************************************************************************
//!	@file	SackStateBase.h
//!	@brief	�R�f�̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_SACK_STATE_BASE__
#define __GM31_SACK_STATE_BASE__

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
//# include "CSackBase.h"
//# include "input.h"
# include <stdio.h>
//# include "CSackBase.h"

class CSackBase;

//=============================================================================
//!	@class	SackStateBase
//!	@brief �R�f�̏�ԃx�[�X�N���X
//=============================================================================
class SackStateBase
{

public:

	enum SACK_STATE
	{
		SACK_NORMAL,
		SACK_FALL,
		SACK_DASH,
		SACK_JUMP,
		SACK_MOVE,
		SACK_FLIP,

		SACK_STATE_MAX

	};

	SackStateBase() {};
	SackStateBase(SACK_STATE state) { stateName = state; };
	virtual ~SackStateBase();								//�f�X�g���N�^

	virtual SackStateBase* GetState(SACK_STATE stateName);
	SACK_STATE GetStateName(void) { return stateName; };

	virtual void Enter(CSackBase* sack) {};					//�J�n�֐�
	virtual void Input(CSackBase* sack) {};					//���͊֐�
	virtual void Action(CSackBase* sack) {};					//�����֐�
	virtual void PostAction(CSackBase* sack) {};				//�㏈���֐�

	virtual char* RenderDebug(void) { return "State : None"; };

protected:

	SACK_STATE stateName;

private:

	static SackStateBase* normalState;
	static SackStateBase* fallingState;
	static SackStateBase* dashState;
	static SackStateBase* moveState;
	static SackStateBase* jumpState;

	void InitializeStates();
	static bool isInitialized;
};

#endif
//******************************************************************************
//	End of file.
//******************************************************************************