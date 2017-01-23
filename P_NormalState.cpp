//*****************************************************************************
//!	@file	NormalState.h
//!	@brief	プレイヤーの普通状態クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "P_NormalState.h"
//# include "input.h"

//==============================================================================
//!	@fn		Enter
//!	@brief	開始関数
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void NormalState::Enter(CSackBase* player)
{
	//player->SetMesh(ModelManager::GetModel(ModelManager::MODEL_PLAYER_NORMAL));
}

//==============================================================================
//!	@fn		Input
//!	@brief	入力関数
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void NormalState::Input(CInput* input, CSackBase* player)
{
	
	//右へ移動
	if (input->IsRightPressed())
	{
		player->SetState(SACK_MOVE);
		player->MoveRight();
	}

	//左へ移動
	if (input->IsLeftPressed())
	{
		player->SetState(SACK_MOVE);
		player->MoveLeft();
	}
	//ジャンプ
	if (input->IsUpPressed())		player->SetState(SACK_JUMP);

	//紐を振り回す
	if (input->IsFlipTriggered())		player->SetState(SACK_FLIP);

	//ダッシュー
	if (input->IsDashTriggered())		player->SetState(SACK_DASH);
	
}

//==============================================================================
//!	@fn		Action
//!	@brief	処理関数
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void NormalState::Action(CSackBase* player)
{
	//スピードを落とす関数を呼び出す
	player->Slide();
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	後処理関数
//!	@param	CSackBase *player		プレイヤーのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void NormalState::PostAction(CSackBase* player)
{
	//下に何もなければ、落下させる
	if (!HitManager::CheckStage(player->m_hitDown) && HitManager::CheckHit(player->m_hitDown, GAMEHIT_TYPE::HIT_SACK) == nullptr)
		player->SetState(SACK_FALL);

	if (HitManager::CheckStage(player->m_hitLeft) ||
		HitManager::CheckStage(player->m_hitRight) ||
		HitManager::CheckHit(player->m_hitLeft, GAMEHIT_TYPE::HIT_SACK) ||
		HitManager::CheckHit(player->m_hitRight, GAMEHIT_TYPE::HIT_SACK))
	{
		player->SetImpulseX(0);
		player->ResetPositionX();
		//	player->SetState(CPlayer::normalState);
	}
}


//******************************************************************************
//	End of file.
//******************************************************************************