//*****************************************************************************
//!	@file	JumpingState.h
//!	@brief	プレイヤーのジャンプ状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "P_JumpingState.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void JumpingState::Enter(CSackBase* player)
{
	//上に何もなければ、ジャンプ関数を呼び出す
	if (!HitManager::CheckStage(player->m_hitUp) &&
		HitManager::CheckHit(player->m_hitUp, GAMEHIT_TYPE::HIT_SACK) == nullptr)
	{
		player->Jump();
		player->StartAnimation(CSackBase::MODEL_JUMP, 10);
		MidairState::Enter(player);
	}
}

//==============================================================================
//!	@fn		Action
//!	@brief	処理関数
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void JumpingState::Action(CSackBase* player)
{
	MidairState::Action(player);
	
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void JumpingState::PostAction(CSackBase* player)
{
	//落ち始めるか、上に何かと当たったら、fallingStateにする
	if (player->GetImpulse().y < 0||
		HitManager::CheckStage(player->m_hitUp) ||
		HitManager::CheckHit(player->m_hitUp, GAMEHIT_TYPE::HIT_SACK))
	{
		player->SetState(SACK_FALL);
		return;
	}

	MidairState::PostAction(player);
	
}


//******************************************************************************
//	End of file.
//******************************************************************************