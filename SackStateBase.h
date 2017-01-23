//*****************************************************************************
//!	@file	SackStateBase.h
//!	@brief	蹴鞠の基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_SACK_STATE_BASE__
#define __GM31_SACK_STATE_BASE__

//=======================================================================//
//		インクルード
//=======================================================================//
//# include "CSackBase.h"
# include "InputClass.h"
# include <stdio.h>

class CSackBase;

//=======================================================================//
//	クラス名		SackStateBase
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
	virtual ~SackStateBase(void);								//デストラクタ

	virtual SackStateBase* GetState(SACK_STATE stateName);
	SACK_STATE GetStateName(void) { return m_stateName; };

	virtual void Enter(CSackBase* sack) {};					//開始関数
	virtual void Input(CInput* input, CSackBase* sack) {};					//入力関数
	virtual void Action(CSackBase* sack) {};					//処理関数
	virtual void PostAction(CSackBase* sack) {};				//後処理関数

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