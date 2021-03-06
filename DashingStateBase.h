//*****************************************************************************
//!	@file	DashingStateBase.h
//!	@brief	蹴鞠のダッシュの基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_DASHING_STATE_BASE__
#define __GM31_DASHING_STATE_BASE__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "SackStateBase.h"

//=============================================================================
//!	@class	DashingStateBase
//!	@brief 蹴鞠のダッシュの基本状態クラス
//=============================================================================
class DashingStateBase : public SackStateBase
{
public:
	DashingStateBase() : SackStateBase(SACK_DASH){};
	void Enter(CSackBase* sack);			//開始関数
	void Action(CSackBase* sack);			//処理関数
	void PostAction(CSackBase* sack);		//後処理関数

	char* RenderDebug(void){ return "State : Dash"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************