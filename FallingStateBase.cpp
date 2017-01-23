//*****************************************************************************
//!	@file	FallingStateBase.h
//!	@brief	R‹f‚Ì—Ž‰º‚ÌŠî–{ó‘ÔƒNƒ‰ƒX
//!	@note	
//!	@author	ƒCƒŒƒl@ƒwƒ‹ƒZƒmƒEƒCƒX
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ƒwƒbƒ_|
//-----------------------------------------------------------------------------
# include "FallingStateBase.h"
# include "SackBaseClass.h"
# include "MathUtility.h"
# include "HitManager.h"
# include "Macros.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	ŠJŽnŠÖ”
//!	@param	CSackBase *sack		R‹f‚Ìƒ|ƒCƒ“ƒ^
//!	@retval	‚È‚µ
//!	@note	
//==============================================================================
void FallingStateBase::Enter(CSackBase* sack)
{
	sack->SetImpulseY(0);
}

//==============================================================================
//!	@fn		Action
//!	@brief	ˆ—ŠÖ”
//!	@param	CSackBase *sack		R‹f‚Ìƒ|ƒCƒ“ƒ^
//!	@retval	‚È‚µ
//!	@note	
//==============================================================================
void FallingStateBase::Action(CSackBase* sack)
{
	MidairStateBase::Action(sack);
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	Œãˆ—ŠÖ”
//!	@param	CSackBase *sack		R‹f‚Ìƒ|ƒCƒ“ƒ^
//!	@retval	‚È‚µ
//!	@note	
//==============================================================================
void FallingStateBase::PostAction(CSackBase* sack)
{

	//‰º‚É‰½‚É‚ª‚ ‚Á‚½‚çAnormalState‚É‚·‚é
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