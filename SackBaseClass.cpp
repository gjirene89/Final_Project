//************************************************************************//
//	SackBaseClass.cpp
//	2017-01-16
//	Irene Gersenowies
//************************************************************************//

//==============================================================================
//		インクルード
//==============================================================================
# include "SackBaseClass.h"
# include "SackStateBaseHeaders.h"
# include "Macros.h"
# include "HitBoxClass.h"
# include "HitSphereClass.h"
# include "ShaderManagerClass.h"
# include "HitManager.h"
# include "MathUtility.h"
# include "StageClass.h"
//# include "CDirectxGraphics.h"
//# include "CStage.h"
//# include "CHit_Sphere.h"
//# include "CHit_Box.h"
//# include "Debug.h"
//# include "CPlayer.h"
//# include "mathutil.h"



//==============================================================================
//	グローバル変数
//==============================================================================
int CSackBase::m_noSack = 0;
CModel* CSackBase::m_body = nullptr;
CModel* CSackBase::m_hook = nullptr;

//==============================================================================
//!	@fn		CSackBase
//!	@brief	蹴鞠べースのコンストラクタ
//!	@param	float posX		X軸の位置
//!	@param	float posY		Y軸の位置
//!	@retval	なし
//! @note
//==============================================================================
CSackBase::CSackBase(float posX, float posY, GAMEOBJTYPE gObj) : CGameObjectBase(gObj)
{
	m_noId = ++m_noSack;

	//色設定
	//InitMaterial();

	//位置の初期化
	m_initPosition = { posX * BLOCK_SIZE, posY * BLOCK_SIZE + SACK_RADIUS, 0.0f };
	m_position = m_oldPosition = m_initPosition;

	//rope = nullptr;
	m_orientation = { 0,0,0 };

	//当たり判定
	m_hitCenter = new CHit_Box(SACK_RADIUS * 2.5, SACK_RADIUS * 2, SACK_RADIUS * 2, GAMEHIT_TYPE::HIT_SACK, this);
	m_hitLeft = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitRight = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitUp = new CHit_Box(SACK_RADIUS, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitDown = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitRightOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitLeftOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitUpOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
}

//==============================================================================
//!	@fn		～CSackBase
//!	@brief	蹴鞠ベースのデストラクタ
//!	@param	なし
//!	@retval	なし
//==============================================================================
CSackBase::~CSackBase()
{
	//if (rope != nullptr)	delete rope;

	//当たり判定のポインタを解放する
	if (m_hitCenter		!= nullptr)		delete m_hitCenter;
	if (m_hitRight		!= nullptr)		delete m_hitRight;
	if (m_hitLeft		!= nullptr)		delete m_hitLeft;
	if (m_hitDown		!= nullptr)		delete m_hitDown;
	if (m_hitUp			!= nullptr)		delete m_hitUp;
	if (m_hitRightOut	!= nullptr)		delete m_hitRightOut;
	if (m_hitLeftOut	!= nullptr)		delete m_hitLeftOut;
}

bool CSackBase::InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;

	//**************//
	// 　蹴鞠の体　　	//
	//**************//
	m_body = new CModel;
	if (!m_body)
	{
		return false;
	}

	result = m_body->Initialize(device, "Resources/Model/sack.txt");
	if (!result)
	{
		return false;
	}

	m_body->LoadColorMap(device, deviceContext, "Resources/Texture/sackColor.tga");
	m_body->LoadBumpMap(device, deviceContext, "Resources/Texture/sackNormal.tga");

	//****************//
	// 　蹴鞠のフック	  //
	//****************//

	m_hook = new CModel;
	if (!m_hook)
	{
		return false;
	}

	result = m_hook->Initialize(device, "Resources/Model/hook.txt");
	if (!result)
	{
		return false;
	}

	return true;
}

void CSackBase::Shutdown(void)
{
	if (m_body != nullptr)
	{
		m_body->Shutdown();
		delete m_body;
		m_body = nullptr;
	}

	if (m_hook != nullptr)
	{
		m_hook->Shutdown();
		delete m_hook;
		m_hook = nullptr;
	}

	return;
}

//==============================================================================
//!	@fn		Initialize
//!	@brief	蹴鞠の初期化関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Initialize(void)
{
	//位置の初期化
	m_position = m_oldPosition = m_initPosition;
	m_impulse = { 0, 0, 0 };

	switch (m_looking)
	{
	case SACK_DIR_LEFT:
		m_initAngle = -LOOK_ANGLE;
		break;

	case SACK_DIR_RIGHT:
		m_initAngle = LOOK_ANGLE;
		break;
	}


	m_orientation = { cos(m_initAngle), 0.0f, -sin(m_initAngle) };

	m_matrix = XMMatrixRotationY(m_initAngle);
	//D3DXMatrixRotationY(&matrix, initAngle);

	UpdateDisplacement();
	//状態の初期化
	m_state = m_state->GetState(SackStateBase::SACK_NORMAL);
	//親をヌルにする
	m_parent = nullptr;
	m_child = nullptr;

//	if (rope != nullptr)	rope->Init(matrix);
}

//==============================================================================
//!	@fn		Action
//!	@brief	蹴鞠の処理関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Action(void)
{
	//元の値をコピーする
	m_oldPosition = m_position;
	m_oldImpulse = m_impulse;

	//現在の状態の処理を呼び出す
	m_state->Action(this);

	//移動
	UpdateDisplacement();

	//当たり判定データ更新
	UpdateHit();
	/*
	if (rope != nullptr)
		rope->Action(matrix);
		
	if (child_ != nullptr)
		rope->LockEnd(child_->GetHookPos());
*/
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	蹴鞠の後処理
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::PostAction(void)
{
	//if (rope != nullptr) rope->PostAction();
	m_state->PostAction(this);
}

//==============================================================================
//!	@fn		MoveRight
//!	@brief	右へ移動
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::MoveRight(void)
{
	m_state = m_state->GetState(SackStateBase::SACK_MOVE);

	m_impulse.x = MOVE_FORCE;
	m_impulse.y = JUMP_FORCE;

	if (HitManager::CheckStage(m_hitRightOut))
	{
		m_impulse.y = CLIMB_FORCE;
		return;
	}

	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(m_hitRightOut, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr && tempObj != m_parent)
	{
		m_impulse.y = CLIMB_FORCE;
	}
}

//==============================================================================
//!	@fn		MoveLeft
//!	@brief	右へ移動
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::MoveLeft(void)
{
	m_state = m_state->GetState(SackStateBase::SACK_MOVE);

	m_impulse.x = -MOVE_FORCE;
	m_impulse.y = JUMP_FORCE;

	if (HitManager::CheckStage(m_hitLeftOut))
	{
		m_impulse.y = CLIMB_FORCE;
		return;
	}

	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(m_hitLeftOut, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr && tempObj != m_parent)
	{
		m_impulse.y = CLIMB_FORCE;
	}

}

//==============================================================================
//!	@fn		Jump
//!	@brief	ジャンプ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Jump(void)
{
	m_state = m_state->GetState(SackStateBase::SACK_JUMP);
	m_impulse.x = 0;
	m_impulse.y = CLIMB_FORCE;
}

//==============================================================================
//!	@fn		Pull
//!	@brief	繋がっている場合、引っ張られる
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Pull(void)
{
	if (m_parent == nullptr) return;

	float angle = CalculateAngle(m_position, m_parent->GetWorldPos());
	float force = GetRopePullForce();
	SackStateBase::SACK_STATE state = m_parent->GetState()->GetStateName();

	if (angle < -90.0f || angle > 110.0f)
	{
		ClearChain();
		return;
	}

	//if (CalculateDistance(position, parent->GetWorldPos()) < ROPE_LENGHT)	return;

	//switch (hookDir)
	//{
	//case SACK_DIR_RIGHT:
	//	break;

	//case SACK_DIR_LEFT:
	//	if (state == SackStateBase::SACK_DASH)
	//	{
	//		SetState(SackStateBase::SACK_DASH);
	//		impulse.x = DASH_FORCE;
	//		return;
	//	}
	//	if (angle > 70.0f && angle < 100.f)	Jump();
	//	else MoveRight();
	//	break;
	//}


	switch (state)
	{
	case SackStateBase::SACK_JUMP:
		if (CalculateDistance(m_position, m_parent->GetWorldPos()) > SACK_RADIUS * 3.0f)
		{
			if (angle > 50.0f && angle < 120.f)
				Jump();
			else
				MoveRight();
		}
		break;

	case SackStateBase::SACK_NORMAL:
	case SackStateBase::SACK_MOVE:
		if ((CalculateDistance(m_position, m_parent->GetWorldPos()) > SACK_RADIUS * 3.0f &&
			m_parent->GetImpulse().x > 0 && angle < 70.0f) ||
			(CalculateDistance(m_position, m_parent->GetWorldPos()) > SACK_RADIUS * 3.0f &&
				m_parent->GetImpulse().x > 0 && angle < 90.0f))
			MoveRight();
		break;

	case SackStateBase::SACK_DASH:
		if (force > 40.0f)
		{
			SetState(SackStateBase::SACK_DASH);
			m_impulse.x = DASH_FORCE;
		}
		break;
	}
}

//==============================================================================
//!	@fn		Chain
//!	@brief	蹴鞠を繋がる関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Chain(void)
{
	if (m_parent != nullptr)	return;

	CSackBase* sack = (CSackBase*)HitManager::CheckHit(m_hitUpOut, GAMEHIT_TYPE::HIT_SACK);

	if (sack == nullptr)	return;

	if (sack->GetStringDir() == m_hookDir && sack->m_child == nullptr)
	{
		m_parent = sack;
		m_parent->m_child = this;
	}
}

void CSackBase::ClearChain(void)
{
	if (m_stringDir == SACK_DIR_NONE)	return;

	//parent->rope->ClearLock();
	m_parent->m_child = nullptr;
	m_parent = nullptr;
}

//==============================================================================
//!	@fn		Slide
//!	@brief	床の上に滑る
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Slide(void)
{
	if (m_impulse.x > FRICTION)
		m_impulse.x -= FRICTION;

	else if (m_impulse.x < -FRICTION)
		m_impulse.x += FRICTION;

	else m_impulse.x = 0;
}

//==============================================================================
//!	@fn		Dash
//!	@brief	ダッシュー関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Dash(void)
{
	//右からぶっつかったら
	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(m_hitRight, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		if (tempObj->GetState()->GetStateName() == SackStateBase::SACK_DASH)
		{
			m_impulse.x = -DASH_FORCE;
			m_state = m_state->GetState(SackStateBase::SACK_DASH);
		}
		return;
	}

	//左からぶっつかる場合
	tempObj = (CSackBase*)HitManager::CheckHit(m_hitLeft, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		if (tempObj->GetState()->GetStateName() == SackStateBase::SACK_DASH)
		{
			m_impulse.x = DASH_FORCE;
			m_state = m_state->GetState(SackStateBase::SACK_DASH);
		}
		return;
	}

}
//==============================================================================
//!	@fn		HitWall
//!	@brief	壁と当たるとき
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::HitWall(void)
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
void CSackBase::LeaveWall(void)
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
//!	@fn		CleanNumbers
//!	@brief	位置をステージにスナップする関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::CleanNumbers(void)
{
	CStage::CleanNumbers(nullptr, &m_position.y);
	m_position.y += SACK_RADIUS;
}

//==============================================================================
//!	@fn		ResetPositionX
//!	@brief	X軸の位置を元の値に戻す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::ResetPositionX(void)
{
	m_position.x = m_oldPosition.x;
}

//==============================================================================
//!	@fn		ResetPositionY
//!	@brief	Y軸の位置を元の値に戻す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::ResetPositionY(void)
{
	m_position.y = m_oldPosition.y;
}

//==============================================================================
//!	@fn		GetParent
//!	@brief	親を戻す
//!	@param	なし
//!	@retval	C3DObject*  親へのポインタ
//==============================================================================
CSackBase* CSackBase::GetParent(void)
{
	return m_parent;
}

//==============================================================================
//!	@fn		GetImpulse
//!	@brief	弾みを戻す関数
//!	@param	なし
//!	@retval	D3DXVECTOR3	oldImpulse		オブジェクトの弾み
//==============================================================================
XMFLOAT3 CSackBase::GetImpulse(void)
{
	return m_oldImpulse;
}

//==============================================================================
//!	@fn		GetRopePullForce
//!	@brief	引っ張られる力
//!	@param	なし
//!	@retval	float	力
//==============================================================================
float CSackBase::GetRopePullForce(void)
{
	if (m_parent == nullptr)
		return 0;
	//return parent->rope->GetPullForce();
	return 0;
}

//==============================================================================
//!	@fn		GetRopePullAngle
//!	@brief	引っ張られた角度
//!	@param	なし
//!	@retval	float	角度（ラジアン）
//==============================================================================
float CSackBase::GetRopePullAngle(void)
{
	if (m_parent == nullptr)
		return 0;

	//return parent->rope->GetPullAngle();
	return 0;
}

//==============================================================================
//!	@fn		GetStringDir
//!	@brief	紐の向きを返す関数
//!	@param	なし
//!	@retval	SACK_DIR		紐の向き
//!	@note	
//==============================================================================
CSackBase::SACK_DIR CSackBase::GetStringDir(void)
{
	return m_stringDir;
}

//==============================================================================
//!	@fn		GetLookingDir
//!	@brief	向いている方向を返す関数
//!	@param	なし
//!	@retval	SACK_DIR		向いている方向
//!	@note	
//==============================================================================
CSackBase::SACK_DIR CSackBase::GetLookingDir(void)
{
	return m_looking;
}

//==============================================================================
//!	@fn		GetHookDir
//!	@brief	フックの向きを返す関数
//!	@param	なし
//!	@retval	SACK_DIR		フックの向き
//!	@note	
//==============================================================================
CSackBase::SACK_DIR CSackBase::GetHookDir(void)
{
	return m_hookDir;
}
//==============================================================================
//!	@fn		AddImpulse
//!	@brief	弾みを増やす関数
//!	@param	float impulseX		x軸の弾み
//!	@param	float impulseY		y軸の弾み
//!	@retval	なし
//==============================================================================
void CSackBase::AddImpulse(float impulseX, float impulseY)
{
	m_impulse.x += impulseX;
	m_impulse.y += impulseY;
}

//==============================================================================
//!	@fn		SetImpulseX
//!	@brief	X軸の移動力を設定する
//!	@param	float impulseX		x軸の力
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::SetImpulseX(float impulseX)
{
	m_impulse.x = impulseX;
}

//==============================================================================
//!	@fn		SetImpulseY
//!	@brief	Y軸の移動力を設定する
//!	@param	float impulseY		y軸の力
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::SetImpulseY(float impulseY)
{
	m_impulse.y = impulseY;
}

//==============================================================================
//!	@fn		SetState
//!	@brief	状態を設定する
//!	@param	PlayerState* state		状態へのポインタ
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::SetState(SackStateBase::SACK_STATE stateName)
{
	m_state = m_state->GetState(stateName);

	//開始関数を呼び出す
	m_state->Enter(this);
}

//==============================================================================
//!	@fn		CreateMesh
//!	@brief　蹴鞠のメッシュを作る関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::CreateMesh(void)
{
	//仮のメッシュの作成
	//D3DXCreateBox(CDirectXGraphics::GetDXDevice(), SACK_RADIUS * 2, SACK_RADIUS * 2, SACK_RADIUS * 2, &mesh, nullptr);
	//D3DXCreateSphere(CDirectXGraphics::GetDXDevice(), SACK_RADIUS, 20, 20, &mesh, nullptr);

}

//==============================================================================
//!	@fn		UpdateDisplacement
//!	@brief　移動更新
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::UpdateDisplacement(void)
{
	//フレームのスピードを落とす
	m_position.y += m_impulse.y / 15.0f;
	m_position.x += m_impulse.x / 15.0f;

	//マトリックスの更新
	m_positionX = m_position.x;
	m_positionY = m_position.y;
	m_positionZ = m_position.z;

}


//==============================================================================
//!	@fn		UpdateHit
//!	@brief	当たり判定の設定関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void CSackBase::UpdateHit(void)
{
	m_hitCenter->UpdatePosition(m_position);
	m_hitLeft->UpdatePosition(    { m_position.x - SACK_RADIUS,     m_position.y,                   m_position.z });
	m_hitRight->UpdatePosition(   { m_position.x + SACK_RADIUS,     m_position.y,                   m_position.z });
	m_hitUp->UpdatePosition(      { m_position.x,                   m_position.y + SACK_RADIUS,     m_position.z });
	m_hitDown->UpdatePosition(    { m_position.x,                   m_position.y - SACK_RADIUS,     m_position.z });
	m_hitRightOut->UpdatePosition({ m_position.x + SACK_RADIUS * 2, m_position.y,                   m_position.z });
	m_hitLeftOut->UpdatePosition( { m_position.x - SACK_RADIUS * 2, m_position.y,                   m_position.z });
	m_hitUpOut->UpdatePosition(   { m_position.x,                   m_position.y + SACK_RADIUS * 2, m_position.z });

	HitManager::AddHit(m_hitCenter);
	HitManager::AddHit(m_hitRight);
	HitManager::AddHit(m_hitLeft);
	HitManager::AddHit(m_hitUp);
	HitManager::AddHit(m_hitDown);
	HitManager::AddHit(m_hitRightOut);
	HitManager::AddHit(m_hitLeftOut);
	HitManager::AddHit(m_hitUpOut);

}

//==============================================================================
//!	@fn		RenderDebug
//!	@brief	デバッグ情報を描画する関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::RenderDebug(void)
{
	/*
	if (CDebug::GetIsHidden() || !CDebug::displayStats)	return;

	int posX = 300 * (noId - 1);
	int posY = 0;

	char text[256];

	CDebug::GetFont()->DrawTextA(posX, posY, nameId);

	CDebug::GetFont()->DrawTextA(posX, posY + 30, state_->RenderDebug());

	sprintf_s(text, "Position X : %f", position.x);
	CDebug::GetFont()->DrawTextA(posX, posY + 60, text);

	sprintf_s(text, "Position Y : %f", position.y);
	CDebug::GetFont()->DrawTextA(posX, posY + 90, text);

	if (parent != nullptr)
	{
		CDebug::GetFont()->DrawTextA(posX, posY + 120, "isChained : true");
		sprintf_s(text, "PullForce : %f", GetRopePullForce());
		CDebug::GetFont()->DrawTextA(posX, posY + 150, text);
		sprintf_s(text, "PullAngle(deg) : %.0f", CalculateAngle(position, parent->GetWorldPos()));
		CDebug::GetFont()->DrawTextA(posX, posY + 180, text);
	}
	else
		CDebug::GetFont()->DrawTextA(posX, posY + 120, "isChained : false");
		*/
}

SackStateBase* CSackBase::GetState(void)
{
	return m_state;
}

XMFLOAT3 CSackBase::GetHookPos(void)
{
	XMMATRIX  hookMatrix, transMatrix, rotMatrix;
	XMFLOAT4X4 hookMatTemp;

	hookMatrix = XMMatrixTranslation(0, SACK_RADIUS, 7);
	transMatrix = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	rotMatrix = XMMatrixRotationY(m_initAngle);

	hookMatrix = hookMatrix * rotMatrix * transMatrix;

	XMStoreFloat4x4(&hookMatTemp, hookMatrix);

	return{ hookMatTemp._41, hookMatTemp._42, hookMatTemp._43 };
}
//******************************************************************************
//	End of file.
//******************************************************************************
