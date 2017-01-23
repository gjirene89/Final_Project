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
# include "SackBaseClass.h"
//# include "input.h"
# include "PlayerClass.h"
# include "MathUtility.h"
# include "HitManager.h"
# include "Macros.h"

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
	if (!HitManager::CheckStage(sack->m_hitDown) &&
		HitManager::CheckHit(sack->m_hitDown, GAMEHIT_TYPE::HIT_SACK) == nullptr)
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
	if (HitManager::CheckStage(sack->m_hitLeft) ||
		HitManager::CheckStage(sack->m_hitRight) ||
		HitManager::CheckHit(sack->m_hitLeft, GAMEHIT_TYPE::HIT_SACK) ||
		HitManager::CheckHit(sack->m_hitRight, GAMEHIT_TYPE::HIT_SACK))
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