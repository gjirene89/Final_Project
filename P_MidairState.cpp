//*****************************************************************************
//!	@file	S_MidairState.h
//!	@brief	プレイヤーの空中状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダ−
//-----------------------------------------------------------------------------
# include "P_MidairState.h"


//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void MidairState::Enter(CSackBase* player)
{

}

//==============================================================================
//!	@fn		Action
//!	@brief	プレイヤーの空中状態の処理
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void MidairState::Action(CSackBase* player)
{
	player->AddImpulse(0, GRAVITY / 15.0f);
	if (player->GetImpulse().y < -JUMP_FORCE)
		player->SetImpulseX(0.0f);
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	プレイヤーの空中状態の後処理
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void MidairState::PostAction(CSackBase* player)
{
	player->HitWall();
}

//******************************************************************************
//	End of file.
//******************************************************************************