//*****************************************************************************
//!	@file	MoveStateBase.h
//!	@brief	蹴鞠の移動の基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "MoveStateBase.h"
# include "SackBaseClass.h"
# include "HitManager.h"
//# include "input.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CSackBase *sack		蹴鞠のポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void MoveStateBase::Enter(CSackBase* sack)
{

}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CSackBase *sack		蹴鞠のポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void MoveStateBase::PostAction(CSackBase* sack)
{
	//落ち始めるか、上に何かと当たったら、fallingStateにする
	if (sack->GetImpulse().y < 0 ||
		HitManager::CheckStage(sack->m_hitUp) ||
		HitManager::CheckHit(sack->m_hitUp, GAMEHIT_TYPE::HIT_SACK) != nullptr)
	{
		sack->SetState(SACK_FALL);
	}

	MidairStateBase::PostAction(sack);
}


//******************************************************************************
//	End of file.
//******************************************************************************