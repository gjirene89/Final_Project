//*****************************************************************************
//!	@file	NormalStateBase.h
//!	@brief	蹴鞠の普通の基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "NormalStateBase.h"
# include "CSackBase.h"
# include "input.h"
# include "CPlayer.h"
# include "mathutil.h"

//==============================================================================
//!	@fn		Action
//!	@brief	処理関数
//!	@param	CSackBase *sack		蹴鞠のポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void NormalStateBase::Action(CSackBase* sack)
{
	//スピードを落とす関数を呼び出す
	sack->Slide();

}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CSackBase *sack		蹴鞠のポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void NormalStateBase::PostAction(CSackBase* sack)
{
	//下に何もなければ、落下させる
	if (!HitManager::CheckStage(sack->hitDown) &&
		HitManager::CheckHit(sack->hitDown, GAMEHIT_TYPE::HIT_SACK) == nullptr)
	{
		if (sack->GetParent() == nullptr)
		{
			sack->SetState(SACK_FALL);
		}
		else if (CalculateDistance(sack->GetWorldPos(), sack->GetParent()->GetWorldPos()) < SACK_RADIUS * 2.0f ||
			CalculateAngle(sack->GetWorldPos(), sack->GetParent()->GetWorldPos()) < 0.0f)
		{
			sack->SetState(SACK_FALL);
		}
	}

	//何かとぶつかったら、動きが止まる
	if (HitManager::CheckStage(sack->hitLeft) ||
		HitManager::CheckStage(sack->hitRight) ||
		HitManager::CheckHit(sack->hitLeft, GAMEHIT_TYPE::HIT_SACK) ||
		HitManager::CheckHit(sack->hitRight, GAMEHIT_TYPE::HIT_SACK))
	{
		sack->SetImpulseX(0);
		sack->ResetPositionX();
	}

	//他の蹴鞠が上に乗っているをチェックする
	sack->Chain();

	//親があれば、蹴鞠を引っ張る
	sack->Pull();

	//ぶつかられたら、動く
	sack->Dash();
}


//******************************************************************************
//	End of file.
//******************************************************************************