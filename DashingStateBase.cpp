//*****************************************************************************
//!	@file	DashingStateBase.cpp
//!	@brief	蹴鞠のダッシュの基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "DashingStateBase.h"
# include "CSackBase.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CSackBase *sack		蹴鞠のポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void DashingStateBase::Enter(CSackBase* sack)
{
	//ダッシュー関数を呼び出す
	sack->Dash();
}

//==============================================================================
//!	@fn		Action
//!	@brief	処理関数
//!	@param	CSackBase *sack		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void DashingStateBase::Action(CSackBase* sack)
{
	//Ｘ軸のスピードを減らす
	sack->Slide();
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CSackBase *sack		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void DashingStateBase::PostAction(CSackBase* sack)
{
	//動けなくなったら、normalStateに戻す
	if (sack->GetImpulse().x == 0)
		sack->SetState(SACK_NORMAL);

	if (sack->GetImpulse().x > 0)
	{
		if (HitManager::CheckStage(sack->hitRight) ||
			HitManager::CheckHit(sack->hitRight, GAMEHIT_TYPE::HIT_SACK))
		{
			sack->SetImpulseX(0);
			sack->ResetPositionX();
			sack->SetState(SACK_NORMAL);
		}
	}

	if (sack->GetImpulse().x < 0)
	{
		if (HitManager::CheckStage(sack->hitLeft) ||
			HitManager::CheckHit(sack->hitLeft, GAMEHIT_TYPE::HIT_SACK))
		{
			sack->SetImpulseX(0);
			sack->ResetPositionX();
			sack->SetState(SACK_NORMAL);
		}
	}
}



//******************************************************************************
//	End of file.
//******************************************************************************