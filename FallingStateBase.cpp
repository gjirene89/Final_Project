//*****************************************************************************
//!	@file	FallingStateBase.h
//!	@brief	蹴鞠の落下の基本状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダ−
//-----------------------------------------------------------------------------
# include "FallingStateBase.h"
# include "SackBaseClass.h"
# include "MathUtility.h"
# include "HitManager.h"
# include "Macros.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CSackBase *sack		蹴鞠のポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void FallingStateBase::Enter(CSackBase* sack)
{
	sack->SetImpulseY(0);
}

//==============================================================================
//!	@fn		Action
//!	@brief	処理関数
//!	@param	CSackBase *sack		蹴鞠のポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void FallingStateBase::Action(CSackBase* sack)
{
	MidairStateBase::Action(sack);
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CSackBase *sack		蹴鞠のポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void FallingStateBase::PostAction(CSackBase* sack)
{

	//下に何にがあったら、normalStateにする
	if (HitManager::CheckStage(sack->m_hitDown))
	{
		sack->SetImpulseY(0.0f);
		sack->CleanNumbers();
		sack->SetState(SACK_NORMAL);
	}
	else if (HitManager::CheckHit(sack->m_hitDown, GAMEHIT_TYPE::HIT_SACK))
	{
		sack->SetImpulseY(0.0f);
		sack->SetState(SACK_NORMAL);
	}

	MidairStateBase::PostAction(sack);

	if (sack->GetParent() == nullptr) return;
	if (sack->GetParent()->GetState()->GetStateName() != SACK_NORMAL)	return;

	if (CalculateDistance(sack->GetHookPos(), sack->GetParent()->GetHookPos()) > ROPE_LENGHT &&
		sack->GetRopePullAngle() > 0.0f)
	{
		sack->ResetPositionY();
		sack->SetImpulseY(0);
		
			sack->SetState(SACK_NORMAL);
		
		return;
	}

}

//******************************************************************************
//	End of file.
//******************************************************************************