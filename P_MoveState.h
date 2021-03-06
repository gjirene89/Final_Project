//*****************************************************************************
//!	@file	MoveState.h
//!	@brief	プレイヤーの移動状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_MOVE_STATE__
#define __GM31_MOVE_STATE__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "P_MidairState.h"

//=============================================================================
//!	@class	MoveState
//!	@brief プレイヤーの移動状態クラス
//=============================================================================
class MoveState : public MidairState
{
public:
	MoveState() : MidairState(SACK_MOVE){};
	void Enter(CSackBase* player);			//開始関数
	void PostAction(CSackBase* player);		//後処理関数

	char* RenderDebug(void){ return "State : Move"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************