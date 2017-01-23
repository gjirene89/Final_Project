//*****************************************************************************
//!	@file	NormalState.h
//!	@brief	プレイヤーの普通状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_NORMAL_STATE__
#define __GM31_NORMAL_STATE__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "PlayerState.h"

//=============================================================================
//!	@class	NormalState
//!	@brief プレイヤーの普通状態クラス
//=============================================================================
class NormalState : public PlayerState
{
public:
	NormalState() : PlayerState(SACK_NORMAL){};
	void Enter(CSackBase* player);
	void Input(CInput* input, CSackBase* player);			//入力関数
	void Action(CSackBase* player);			//処理関数
	void PostAction(CSackBase* player);		//後処理関数

	char* RenderDebug(void){ return "State : Normal"; };
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************