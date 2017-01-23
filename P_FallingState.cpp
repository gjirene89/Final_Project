//*****************************************************************************
//!	@file	FallingState.h
//!	@brief	プレイヤーの落下状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
# include "P_FallingState.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CPlayer *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void FallingState::Enter(CSackBase* player)
{
//	player->SetMesh(ModelManager::GetModel(ModelManager::MODEL_PLAYER_NORMAL));
//	player->SetImpulseX(0);
}

//==============================================================================
//!	@fn		Action
//!	@brief	処理関数
//!	@param	CPlayer *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void FallingState::Action(CSackBase* player)
{

	MidairState::Action(player);
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CPlayer *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void FallingState::PostAction(CSackBase* player)
{
	CSackBase *tempSack = (CSackBase*)HitManager::CheckHit(player->m_hitDown, GAMEHIT_TYPE::HIT_SACK);
	//下に何にがあったら、normalStateにする
	if (HitManager::CheckStage(player->m_hitDown))
	{
		//player->SetOldPositionY();
		player->SetImpulseY(0.0f);
		player->CleanNumbers();
		player->SetState(SACK_NORMAL);
	}
	else if (tempSack!=nullptr)
	{
		//player->SetOldPositionY();
		player->SetImpulseY(0.0f);
		if (tempSack->GetState()->GetStateName() == SACK_NORMAL )
			player->SetState(SACK_NORMAL);
	}

	MidairState::PostAction(player);
}

//******************************************************************************
//	End of file.
//******************************************************************************