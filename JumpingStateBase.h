//*****************************************************************************
//!	@file	JumpingStateBase.h
//!	@brief	蹴鞠のジャンプの基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_JUMPING_STATE_BASE__
#define __GM31_JUMPING_STATE_BASE__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "MidairStateBase.h"

//=============================================================================
//!	@class	JumpingStateBase
//!	@brief 蹴鞠のジャンプの基本状態クラス
//=============================================================================
class JumpingStateBase : public MidairStateBase
{
public:
	JumpingStateBase() :MidairStateBase(SACK_JUMP){};
	//void Enter(CSackBase* sack);			//開始関数
	void Action(CSackBase* sack);			//処理関数
	void PostAction(CSackBase* sack);		//後処理関数

	char* RenderDebug(void){ return "State : Jumping"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************