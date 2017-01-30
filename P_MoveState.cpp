//*****************************************************************************
//!	@file	MoveState.h
//!	@brief	プレイヤーの移動状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "P_MoveState.h"
//# include "input.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CPlayer *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void MoveState::Enter(CSackBase* player)
{
	player->StartAnimation(CSackBase::MODEL_MOVE_JUMP, 10);

	MidairState::Enter(player);

	/*
	//左へ動かす
	if (GetKeyboardPress(DIK_A))
	{
		player->MoveLeft();
		return;
	}

	//右へ動かす
	if (GetKeyboardPress(DIK_D))
	{
		player->MoveRight();
		return;
	}
	*/
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CPlayer *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void MoveState::PostAction(CSackBase* player)
{
	//落ち始めるか、上に何かと当たったら、fallingStateにする
	if (player->GetImpulse().y < 0 ||
		HitManager::CheckStage(player->m_hitUpOut) ||
		HitManager::CheckHit(player->m_hitUpOut, GAMEHIT_TYPE::HIT_SACK) != nullptr)
	{
		player->SetState(SACK_FALL);
	}

	MidairState::PostAction(player);
	
}


//******************************************************************************
//	End of file.
//******************************************************************************