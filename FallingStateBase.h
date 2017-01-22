//*****************************************************************************
//!	@file	FallingStateBase.h
//!	@brief	蹴鞠の落下の基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_FALLING_STATE_BASE__
#define __GM31_FALLING_STATE_BASE__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "MidairStateBase.h"

//=============================================================================
//!	@class	FallingStateBase
//!	@brief  蹴鞠の落下の基本状態クラス
//=============================================================================
class FallingStateBase : public MidairStateBase
{
public:
	FallingStateBase() :MidairStateBase(SACK_FALL){};
	void Enter(CSackBase* sack);			//開始関数
	void Action(CSackBase* sack);			//処理関数
	void PostAction(CSackBase* sack);		//後処理関数

	char* RenderDebug(void){ return "State : Falling"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************