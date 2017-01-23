//*****************************************************************************
//!	@file	SackStateBase.h
//!	@brief	�R�f�̊�{��ԃN���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_SACK_STATE_BASE__
#define __GM31_SACK_STATE_BASE__

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
//# include "CSackBase.h"
# include "InputClass.h"
# include <stdio.h>

class CSackBase;

//=======================================================================//
//	�N���X��		SackStateBase
//=======================================================================//
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

	SackStateBase(void);
	SackStateBase(const SackStateBase& other) {};
	SackStateBase(SACK_STATE state) { m_stateName = state; };
	virtual ~SackStateBase(void);								//�f�X�g���N�^

	virtual SackStateBase* GetState(SACK_STATE stateName);
	SACK_STATE GetStateName(void) { return m_stateName; };

	virtual void Enter(CSackBase* sack) {};					//�J�n�֐�
	virtual void Input(CInput* input, CSackBase* sack) {};					//���͊֐�
	virtual void Action(CSackBase* sack) {};					//�����֐�
	virtual void PostAction(CSackBase* sack) {};				//�㏈���֐�

	virtual char* RenderDebug(void) { return "State : None"; };

protected:

	SACK_STATE m_stateName;

private:

	static SackStateBase* m_normalState;
	static SackStateBase* m_fallingState;
	static SackStateBase* m_dashState;
	static SackStateBase* m_moveState;
	static SackStateBase* m_jumpState;
	
	static bool m_isInitialized;

};

#endif
//******************************************************************************
//	End of file.
//******************************************************************************