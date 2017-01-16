//*****************************************************************************
//!	@file	CPlayer.h
//!	@brief	プレイヤークラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
# include <stdio.h>
# include "input.h"
# include "mathutil.h"
# include "Debug.h"
# include "Macros.h"
# include "HitManager.h"

# include "CPlayer.h"
# include "CSackBase.h"
# include "PlayerStateHeader.h"
# include "CStage.h"
# include "CHit_Sphere.h"
# include "SceneManager.h"
# include "SackStateBase.h"

//-----------------------------------------------------------------------------
//	マクロ定数
//-----------------------------------------------------------------------------
# define LOOK_ANGLE	(-75 * D3DX_PI / 180.0f)
# define ROT_SPEED	D3DX_PI/20.0f

//-----------------------------------------------------------------------------
//	グローバル変数
//-----------------------------------------------------------------------------

//==============================================================================
//!	@fn		CPlayer
//!	@brief	プレイヤーのコンストラクタ
//!	@param	float posX		位置　x軸
//!	@param	float posY		位置　y軸
//!	@retval	なし
//!	@note	
//==============================================================================
CPlayer::CPlayer(float posX, float posY) : CSackBase(posX, posY, GAMEOBJTYPE::GOBJ_PLAYER)
{
	strcpy_s(nameId, "Player");

	//クオアタニオンの初期化
	D3DXQuaternionIdentity(&quaternion);

	//色設定
	SetDiffuse({1.0f,0.0f,0.0f,1.0f});

	//メッシュ生成
	//CreateMesh();
	//LoadXFile("assets/xFiles/Player/sack.x");
	mesh = ModelManager::GetModel(ModelManager::MODEL_PLAYER_NORMAL);
	texture = TexManager::GetTexture(TexManager::TEX_PLAYER_COLOR);

	//当たり判定
//	hitCenter	= new CHit_Sphere(PLAYER_RADIUS, GAMEHIT_TYPE::HIT_PLAYER, this);

	rope = new CRope(D3DXVECTOR3( 0, SACK_RADIUS, 2 ));
	hookDir = SACK_DIR_NONE;
	state_ = new PlayerState();
}

//==============================================================================
//!	@fn		~CPlayer
//!	@brief	プレイヤーのデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CPlayer::~CPlayer(void)
{
	//今は空
}

//==============================================================================
//!	@fn		Init
//!	@brief	プレイヤーの初期化関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::Init(void)
{
	D3DXQuaternionRotationMatrix(&quaternion, &matrix);

	looking = SACK_DIR_RIGHT;
	stringDir = SACK_DIR_LEFT;

	CSackBase::Init();
}

//==============================================================================
//!	@fn		Input
//!	@brief	プレイヤーの入力関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::Input(void)
{
	//現在の状態の入力を呼び出す
	state_->Input(this);
}

//==============================================================================
//!	@fn		Action
//!	@brief	プレイヤーの処理関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::Action(void)
{


	//向いている方向の更新
	UpdateRotation();

	CSackBase::Action();
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	プレイヤーの後処理
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::PostAction(void)
{
	if (HitManager::CheckHit(hitCenter, GAMEHIT_TYPE::HIT_GOAL))
		SceneManager::StageClear();
	
	CSackBase::PostAction();

}

//==============================================================================
//!	@fn		MoveRight
//!	@brief	右へ移動
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::MoveRight(void)
{
	looking = SACK_DIR_RIGHT;
	stringDir = SACK_DIR_LEFT;
	orientation = { cos(LOOK_ANGLE), 0.0f, -sin(LOOK_ANGLE) };

	CSackBase::MoveRight();
		
}

//==============================================================================
//!	@fn		MoveLeft
//!	@brief	右へ移動
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::MoveLeft(void)
{
	looking = SACK_DIR_LEFT;
	stringDir = SACK_DIR_RIGHT;
	orientation = { cos(-LOOK_ANGLE), 0.0f, -sin(-LOOK_ANGLE) };

	CSackBase::MoveLeft();
}

//==============================================================================
//!	@fn		FlipString
//!	@brief	紐の向きを逆にする
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::FlipString(void)
{
	switch (stringDir)
	{
	case SACK_DIR_LEFT:
		stringDir = SACK_DIR_RIGHT;
		break;

	case SACK_DIR_RIGHT:
		stringDir = SACK_DIR_LEFT;
		break;
	}
}

//==============================================================================
//!	@fn		Dash
//!	@brief	ダッシュ開始関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::Dash(void)
{
	//向きに合わせてダッシュを開始する　（となりに壁があると、ダッシュを実行しない
	switch (looking)
	{
	case SACK_DIR_RIGHT:
		if (!HitManager::CheckStage(hitRight))
			impulse.x = DASH_FORCE;
		break;

	case SACK_DIR_LEFT:
		if (!HitManager::CheckStage(hitLeft))
			impulse.x = -DASH_FORCE;
		break;
	}
}

//==============================================================================
//!	@fn		HitWall
//!	@brief	壁と当たるとき
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::HitWall(void)
{
	//壁にはまっている場合
	if (abs(impulse.x) < 1.0f)
		LeaveWall();
	else
	{
		switch (looking)
		{
		case SACK_DIR_LEFT:
			if (HitManager::CheckStage(hitLeft) || HitManager::CheckHit(hitLeft, GAMEHIT_TYPE::HIT_SACK))
			{
				ResetPositionX();
			}
			break;

		case SACK_DIR_RIGHT:
			if (HitManager::CheckStage(hitRight) || HitManager::CheckHit(hitRight, GAMEHIT_TYPE::HIT_SACK))
			{
				ResetPositionX();
			}
			break;
		}
	}
}

//==============================================================================
//!	@fn		LeaveWall
//!	@brief	壁にはまったら、壁から出す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::LeaveWall(void)
{
	if (HitManager::CheckStage(hitCenter) || HitManager::CheckHit(hitCenter, GAMEHIT_TYPE::HIT_SACK))
	{
		if (HitManager::CheckStage(hitRight) || HitManager::CheckHit(hitRight, GAMEHIT_TYPE::HIT_SACK))
			position.x -= 0.25f;
		else if (HitManager::CheckStage(hitLeft) || HitManager::CheckHit(hitLeft, GAMEHIT_TYPE::HIT_SACK))
			position.x += 0.25f;
	}
}



//==============================================================================
//!	@fn		UpdateRotation
//!	@brief　回転更新
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::UpdateRotation(void)
{
	//向きが変わっていない場合、何もしない
	if (GetRotX() == orientation)	return;

	//クオータニオンを求める
	float d = 0;
	D3DXQUATERNION targetQt = RotationArc(GetRotX(), orientation, d);

	//角度を求める
	float angleDiff = acos(d);

	//現在の角度を目的の角度に合わせていく
	if (ROT_SPEED >= angleDiff)		quaternion = quaternion * targetQt;
	else
	{
		float t = ROT_SPEED / angleDiff;
		D3DXQuaternionSlerp(&quaternion, &quaternion, &(quaternion * targetQt), t);
	}
	
	//クオータニオンをマトリックスにセット
	D3DXMatrixRotationQuaternion(&matrix, &quaternion);
}

//******************************************************************************
//	End of file.
//******************************************************************************
