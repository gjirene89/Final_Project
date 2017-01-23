//*****************************************************************************
//!	@file	DashingState.cpp
//!	@brief	プレイヤーのダッシュ状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "P_DashingState.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CPlayer *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void DashingState::Enter(CSackBase* player)
{
	//ダッシュー関数を呼び出す
	player->Dash();
}

//==============================================================================
//!	@fn		Action
//!	@brief	処理関数
//!	@param	CPlayer *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void DashingState::Action(CSackBase* player)
{
	//Ｘ軸のスピードを減らす
	player->Slide();
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CPlayer *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void DashingState::PostAction(CSackBase* player)
{
	//動けなくなったら、normalStateに戻す
	if (player->GetImpulse().x == 0)
	{
		player->SetState(SACK_NORMAL);
		return;
	}
	//壁と当たったら止まる
	if (HitManager::CheckStage(player->m_hitLeft) ||
		HitManager::CheckStage(player->m_hitRight) )
	{
		player->SetImpulseX(0);
		player->ResetPositionX();
		player->SetState(SACK_NORMAL);
		return;
	}

	//蹴鞠と当たったら、押し出す
	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(player->m_hitLeft, GAMEHIT_TYPE::HIT_SACK);

	if (tempObj!=nullptr)
	{
		tempObj->SetImpulseX(-DASH_FORCE);
		tempObj->SetState(SackStateBase::SACK_DASH);
		player->SetImpulseX(0);
		player->ResetPositionX();
		player->SetState(SACK_NORMAL);
		
		return;
	}

	tempObj = (CSackBase*)HitManager::CheckHit(player->m_hitRight, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		tempObj->SetImpulseX(DASH_FORCE);
		tempObj->SetState(SackStateBase::SACK_DASH);
		player->SetImpulseX(0);
		player->ResetPositionX();
		player->SetState(SACK_NORMAL);
		
		return;
	}

}



//******************************************************************************
//	End of file.
//******************************************************************************