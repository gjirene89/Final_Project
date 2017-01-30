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
//# include "input.h"
# include "MathUtility.h"
//# include "Debug.h"
# include "Macros.h"
# include "HitManager.h"
# include "ShaderManager.h"

# include "PlayerClass.h"
# include "SackBaseClass.h"
# include "PlayerStateHeader.h"
# include "StageClass.h"
# include "HitSphereClass.h"
# include "SceneManager.h"
# include "SackStateBase.h"

//-----------------------------------------------------------------------------
//	マクロ定数
//-----------------------------------------------------------------------------
# define ROT_SPEED	XM_PI/40.0f

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
	strcpy_s(m_nameId, "Player");

	//クオアタニオンの初期化
	m_quaternion = XMQuaternionIdentity();

	//色設定
	//SetDiffuse({1.0f,0.0f,0.0f,1.0f});

	//メッシュ生成
	//CreateMesh();
	//LoadXFile("assets/xFiles/Player/sack.x");
	//mesh = ModelManager::GetModel(ModelManager::MODEL_PLAYER_NORMAL);
	//texture = TexManager::GetTexture(TexManager::TEX_PLAYER_COLOR);

	//当たり判定
//	hitCenter	= new CHit_Sphere(PLAYER_RADIUS, GAMEHIT_TYPE::HIT_PLAYER, this);

	m_rope = new CRope(XMFLOAT3( 0, SACK_RADIUS, 2 ));
	m_hookDir = SACK_DIR_NONE;
	m_state = new PlayerState();
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
void CPlayer::Initialize(void)
{
	//D3DXQuaternionRotationMatrix(&quaternion, &matrix);

	m_looking = SACK_DIR_RIGHT;
	m_stringDir = SACK_DIR_LEFT;

	CSackBase::Initialize();
	
	m_quaternion = XMQuaternionRotationMatrix(m_matrix);
}

//==============================================================================
//!	@fn		Input
//!	@brief	プレイヤーの入力関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::Input(CInput* input)
{
	//現在の状態の入力を呼び出す
	m_state->Input(input, this);
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
	m_animBody->InterpolateModels();

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
/*	if (HitManager::CheckHit(m_hitCenter, GAMEHIT_TYPE::HIT_GOAL))
		SceneManager::StageClear();
	*/
	CSackBase::PostAction();

}

//==============================================================================
//!	@fn		Render
//!	@brief	蹴鞠の描画関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CPlayer::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light)
{
	if (!m_body)
		return;

	CalculateWorldMatrix(m_matrix, m_quaternion);
	
	m_body->Render(deviceContext,m_animBody->GetVertexBuffer(deviceContext));
	//CShaderManager::getInstance().RenderTextureShader(deviceContext, m_body->GetIndexCount(), m_matrix, viewMatrix, projectionMatrix, m_colorTexture->GetTextureData());
	
	CShaderManager::getInstance().RenderSpecularShader(deviceContext, m_body->GetIndexCount(), 
		m_matrix, viewMatrix, projectionMatrix, 
		m_colorTexture->GetTextureData(),light->GetDirection(), light->GetAmbientColor(), light->GetDiffuseColor(),
		cameraPosition, light->GetSpecularColor(), light->GetSpecularPower());

	//m_hook->Render(deviceContext);
	//CShaderManager::getInstance().RenderSpecularShader(deviceContext, m_hook->GetIndexCount(), m_matrix, viewMatrix, projectionMatrix, XMFLOAT4(1.0f,1.0f,0.0f,1.0f));
	
	m_rope->Render(deviceContext,m_matrix,viewMatrix,projectionMatrix, cameraPosition, light);
	//if (m_rope != nullptr) m_rope->Render();
	//RenderDebug();

	/*
	if (CDebug::displayAxis && !CDebug::GetIsHidden())
	RenderAxis();
	*/
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
	m_looking = SACK_DIR_RIGHT;
	m_stringDir = SACK_DIR_LEFT;

	m_orientation = { cos(m_initAngle), 0.0f, -sin(m_initAngle) };

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
	m_looking = SACK_DIR_LEFT;
	m_stringDir = SACK_DIR_RIGHT;
	m_orientation = { cos(-m_initAngle), 0.0f, -sin(-m_initAngle) };

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
	switch (m_stringDir)
	{
	case SACK_DIR_LEFT:
		m_stringDir = SACK_DIR_RIGHT;
		break;

	case SACK_DIR_RIGHT:
		m_stringDir = SACK_DIR_LEFT;
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
	switch (m_looking)
	{
	case SACK_DIR_RIGHT:
		if (!HitManager::CheckStage(m_hitRight))
			m_impulse.x = DASH_FORCE;
		break;

	case SACK_DIR_LEFT:
		if (!HitManager::CheckStage(m_hitLeft))
			m_impulse.x = -DASH_FORCE;
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
	if (abs(m_impulse.x) < 1.0f)
		LeaveWall();
	else
	{
		switch (m_looking)
		{
		case SACK_DIR_LEFT:
			if (HitManager::CheckStage(m_hitLeft) || HitManager::CheckHit(m_hitLeft, GAMEHIT_TYPE::HIT_SACK))
			{
				ResetPositionX();
			}
			break;

		case SACK_DIR_RIGHT:
			if (HitManager::CheckStage(m_hitRight) || HitManager::CheckHit(m_hitRight, GAMEHIT_TYPE::HIT_SACK))
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
	if (HitManager::CheckStage(m_hitCenter) || HitManager::CheckHit(m_hitCenter, GAMEHIT_TYPE::HIT_SACK))
	{
		if (HitManager::CheckStage(m_hitRight) || HitManager::CheckHit(m_hitRight, GAMEHIT_TYPE::HIT_SACK))
			m_position.x -= 0.25f;
		else if (HitManager::CheckStage(m_hitLeft) || HitManager::CheckHit(m_hitLeft, GAMEHIT_TYPE::HIT_SACK))
			m_position.x += 0.25f;
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
	XMVECTOR rotX, orientX, targetQt, mulQuat;
	float d, angleDiff;

	rotX = XMLoadFloat3(&GetRotX());
	orientX = XMLoadFloat3(&m_orientation);

	//クオータニオンを求める
	targetQt = RotationArc(rotX, orientX, d);
	
	//角度を求める
	angleDiff = acos(d);

	if (angleDiff == 0) return;
	targetQt = RotationArc(rotX, orientX, d);
	mulQuat = XMQuaternionMultiply(m_quaternion, targetQt);

	//現在の角度を目的の角度に合わせていく
	if (ROT_SPEED >= angleDiff)	
		m_quaternion = mulQuat;
	else
	{
		float t = ROT_SPEED / angleDiff;
		m_quaternion = XMQuaternionSlerp(m_quaternion, mulQuat, t);
	}
	
	//クオータニオンをマトリックスにセット
	//m_matrix = XMMatrixRotationQuaternion(m_quaternion);
	//D3DXMatrixRotationQuaternion(&matrix, &quaternion);
}

//******************************************************************************
//	End of file.
//******************************************************************************
