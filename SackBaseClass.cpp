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
int CSackBase::noSack = 0;

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
	noId = ++noSack;

	//色設定
	//InitMaterial();

	//位置の初期化
	initPosition = { posX * BLOCK_SIZE, posY * BLOCK_SIZE + SACK_RADIUS, 0.0f };
	position = oldPosition = initPosition;

	//rope = nullptr;
	orientation = { 0,0,0 };

	//当たり判定
	hitCenter = new CHit_Box(SACK_RADIUS * 2.5, SACK_RADIUS * 2, SACK_RADIUS * 2, GAMEHIT_TYPE::HIT_SACK, this);
	hitLeft = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitRight = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitUp = new CHit_Box(SACK_RADIUS, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitDown = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitRightOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitLeftOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitUpOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
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
	if (hitCenter != nullptr)		delete hitCenter;
	if (hitRight != nullptr)		delete hitRight;
	if (hitLeft != nullptr)		delete hitLeft;
	if (hitDown != nullptr)		delete hitDown;
	if (hitUp != nullptr)		delete hitUp;
	if (hitRightOut != nullptr)		delete hitRightOut;
	if (hitLeftOut != nullptr)		delete hitLeftOut;
}

//==============================================================================
//!	@fn		Init
//!	@brief	蹴鞠の初期化関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Initialize(void)
{
	//位置の初期化
	position = oldPosition = initPosition;
	impulse = { 0, 0, 0 };

	m_matrix = XMMatrixRotationY(initAngle);
	//D3DXMatrixRotationY(&matrix, initAngle);

	XMFLOAT4X4 tempMatrix;

	XMStoreFloat4x4(&tempMatrix, m_matrix);

	//向いている方向
	orientation.x = tempMatrix._11;
	orientation.y = tempMatrix._12;
	orientation.z = tempMatrix._13;

	UpdateDisplacement();
	//状態の初期化
	state_ = state_->GetState(SackStateBase::SACK_NORMAL);
	//親をヌルにする
	parent = nullptr;
	child_ = nullptr;

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
	oldPosition = position;
	oldImpulse = impulse;

	//現在の状態の処理を呼び出す
	state_->Action(this);

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
//!	@fn		Render
//!	@brief	蹴鞠の描画関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	if (!m_model)
		return;

	CalculateWorldMatrix(worldMatrix);
	m_model->Render(deviceContext);

	CShaderManager::getInstance().RenderTextureShader(deviceContext, m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_model->GetColorTexture());

	//if (rope != nullptr) rope->Render();

	//RenderDebug();


	//C3DObject::Render();

	/*
	if (CDebug::displayAxis && !CDebug::GetIsHidden())
		RenderAxis();
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
	state_->PostAction(this);
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
	state_ = state_->GetState(SackStateBase::SACK_MOVE);

	impulse.x = MOVE_FORCE;
	impulse.y = JUMP_FORCE;

	if (HitManager::CheckStage(hitRightOut))
	{
		impulse.y = CLIMB_FORCE;
		return;
	}

	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(hitRightOut, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr && tempObj != parent)
	{
		impulse.y = CLIMB_FORCE;
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
	state_ = state_->GetState(SackStateBase::SACK_MOVE);

	impulse.x = -MOVE_FORCE;
	impulse.y = JUMP_FORCE;

	if (HitManager::CheckStage(hitLeftOut))
	{
		impulse.y = CLIMB_FORCE;
		return;
	}

	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(hitLeftOut, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr && tempObj != parent)
	{
		impulse.y = CLIMB_FORCE;
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
	state_ = state_->GetState(SackStateBase::SACK_JUMP);
	impulse.x = 0;
	impulse.y = CLIMB_FORCE;
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
	if (parent == nullptr) return;

	float angle = CalculateAngle(position, parent->GetWorldPos());
	float force = GetRopePullForce();
	SackStateBase::SACK_STATE state = parent->GetState()->GetStateName();

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
		if (CalculateDistance(position, parent->GetWorldPos()) > SACK_RADIUS * 3.0f)
		{
			if (angle > 50.0f && angle < 120.f)
				Jump();
			else
				MoveRight();
		}
		break;

	case SackStateBase::SACK_NORMAL:
	case SackStateBase::SACK_MOVE:
		if ((CalculateDistance(position, parent->GetWorldPos()) > SACK_RADIUS * 3.0f &&
			parent->GetImpulse().x > 0 && angle < 70.0f) ||
			(CalculateDistance(position, parent->GetWorldPos()) > SACK_RADIUS * 3.0f &&
				parent->GetImpulse().x > 0 && angle < 90.0f))
			MoveRight();
		break;

	case SackStateBase::SACK_DASH:
		if (force > 40.0f)
		{
			SetState(SackStateBase::SACK_DASH);
			impulse.x = DASH_FORCE;
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
	if (parent != nullptr)	return;

	CSackBase* sack = (CSackBase*)HitManager::CheckHit(hitUpOut, GAMEHIT_TYPE::HIT_SACK);

	if (sack == nullptr)	return;

	if (sack->GetStringDir() == hookDir && sack->child_ == nullptr)
	{
		parent = sack;
		parent->child_ = this;
	}
}

void CSackBase::ClearChain(void)
{
	if (stringDir == SACK_DIR_NONE)	return;

	//parent->rope->ClearLock();
	parent->child_ = nullptr;
	parent = nullptr;
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
	if (impulse.x > FRICTION)
		impulse.x -= FRICTION;

	else if (impulse.x < -FRICTION)
		impulse.x += FRICTION;

	else impulse.x = 0;
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
	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(hitRight, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		if (tempObj->GetState()->GetStateName() == SackStateBase::SACK_DASH)
		{
			impulse.x = -DASH_FORCE;
			state_ = state_->GetState(SackStateBase::SACK_DASH);
		}
		return;
	}

	//左からぶっつかる場合
	tempObj = (CSackBase*)HitManager::CheckHit(hitLeft, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		if (tempObj->GetState()->GetStateName() == SackStateBase::SACK_DASH)
		{
			impulse.x = DASH_FORCE;
			state_ = state_->GetState(SackStateBase::SACK_DASH);
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
void CSackBase::LeaveWall(void)
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
//!	@fn		CleanNumbers
//!	@brief	位置をステージにスナップする関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CSackBase::CleanNumbers(void)
{
	CStage::CleanNumbers(nullptr, &position.y);
	position.y += SACK_RADIUS;
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
	position.x = oldPosition.x;
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
	position.y = oldPosition.y;
}

//==============================================================================
//!	@fn		GetParent
//!	@brief	親を戻す
//!	@param	なし
//!	@retval	C3DObject*  親へのポインタ
//==============================================================================
CSackBase* CSackBase::GetParent(void)
{
	return parent;
}

//==============================================================================
//!	@fn		GetImpulse
//!	@brief	弾みを戻す関数
//!	@param	なし
//!	@retval	D3DXVECTOR3	oldImpulse		オブジェクトの弾み
//==============================================================================
XMFLOAT3 CSackBase::GetImpulse(void)
{
	return oldImpulse;
}

//==============================================================================
//!	@fn		GetRopePullForce
//!	@brief	引っ張られる力
//!	@param	なし
//!	@retval	float	力
//==============================================================================
float CSackBase::GetRopePullForce(void)
{
	if (parent == nullptr)
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
	if (parent == nullptr)
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
	return stringDir;
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
	return looking;
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
	return hookDir;
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
	impulse.x += impulseX;
	impulse.y += impulseY;
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
	impulse.x = impulseX;
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
	impulse.y = impulseY;
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
	state_ = state_->GetState(stateName);

	//開始関数を呼び出す
	state_->Enter(this);
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
	position.y += impulse.y / 15.0f;
	position.x += impulse.x / 15.0f;

	//マトリックスの更新
	m_positionX = position.x;
	m_positionY = position.y;
	m_positionZ = position.z;

}


//==============================================================================
//!	@fn		UpdateHit
//!	@brief	当たり判定の設定関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void CSackBase::UpdateHit(void)
{
	hitCenter->UpdatePosition(position);
	hitLeft->UpdatePosition({ position.x - SACK_RADIUS, position.y, position.z });
	hitRight->UpdatePosition({ position.x + SACK_RADIUS, position.y, position.z });
	hitUp->UpdatePosition({ position.x, position.y + SACK_RADIUS, position.z });
	hitDown->UpdatePosition({ position.x, position.y - SACK_RADIUS, position.z });
	hitRightOut->UpdatePosition({ position.x + SACK_RADIUS * 2, position.y, position.z });
	hitLeftOut->UpdatePosition({ position.x - SACK_RADIUS * 2, position.y, position.z });
	hitUpOut->UpdatePosition({ position.x, position.y + SACK_RADIUS * 2, position.z });

	HitManager::AddHit(hitCenter);
	HitManager::AddHit(hitRight);
	HitManager::AddHit(hitLeft);
	HitManager::AddHit(hitUp);
	HitManager::AddHit(hitDown);
	HitManager::AddHit(hitRightOut);
	HitManager::AddHit(hitLeftOut);
	HitManager::AddHit(hitUpOut);

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
	return state_;
}

XMFLOAT3 CSackBase::GetHookPos(void)
{
	XMMATRIX  hookMatrix, transMatrix, rotMatrix;
	XMFLOAT4X4 hookMatTemp;

	hookMatrix = XMMatrixTranslation(0, SACK_RADIUS, 7);
	transMatrix = XMMatrixTranslation(position.x, position.y, position.z);
	rotMatrix = XMMatrixRotationY(initAngle);

	hookMatrix = hookMatrix * rotMatrix * transMatrix;

	XMStoreFloat4x4(&hookMatTemp, hookMatrix);

	return{ hookMatTemp._41, hookMatTemp._42, hookMatTemp._43 };
}
//******************************************************************************
//	End of file.
//******************************************************************************
