//*****************************************************************************
//!	@file	JumpingStateBase.h
//!	@brief	蹴鞠のジャンプの基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "JumpingStateBase.h"
# include "CSackBase.h"

//==============================================================================
//!	@fn		Action
//!	@brief	処理関数
//!	@param	CSackBase*	sack		蹴鞠へのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void JumpingStateBase::Action(CSackBase* sack)
{
	MidairStateBase::Action(sack);
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CSackBase*	sack		蹴鞠へのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void JumpingStateBase::PostAction(CSackBase* sack)
{
	//落ち始めるか、上に何かと当たったら、fallingStateにする
	if (sack->GetImpulse().y < 0 ||
		HitManager::CheckStage(sack->hitUp) ||
		HitManager::CheckHit(sack->hitUp, GAMEHIT_TYPE::HIT_SACK) != nullptr)
	{
		sack->SetState(SACK_FALL);
		return;
	}

	MidairStateBase::PostAction(sack);

}


//******************************************************************************
//	End of file.
//******************************************************************************