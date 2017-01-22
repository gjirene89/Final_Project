//*****************************************************************************
//!	@file	SackStateBase.h
//!	@brief	蹴鞠の基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_SACK_STATE_BASE__
#define __GM31_SACK_STATE_BASE__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
//# include "CSackBase.h"
//# include "input.h"
# include <stdio.h>
//# include "CSackBase.h"

class CSackBase;

//=============================================================================
//!	@class	SackStateBase
//!	@brief 蹴鞠の状態ベースクラス
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
	virtual ~SackStateBase();								//デストラクタ

	virtual SackStateBase* GetState(SACK_STATE stateName);
	SACK_STATE GetStateName(void) { return stateName; };

	virtual void Enter(CSackBase* sack) {};					//開始関数
	virtual void Input(CSackBase* sack) {};					//入力関数
	virtual void Action(CSackBase* sack) {};					//処理関数
	virtual void PostAction(CSackBase* sack) {};				//後処理関数

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