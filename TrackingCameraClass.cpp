//************************************************************************//
//	TrackingCameraClass.cpp
//	2017-01-30
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//   インクルード
//=======================================================================//
#include "TrackingCameraClass.h"
#include "MathUtility.h"

//=======================================================================//
//   マクロ定数
//=======================================================================//
# define CAMERA_THRESHOLD (10.0f)

//==============================================================================
//  関数名        CTrackingCamera	
//  説明          追跡カメラクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CTrackingCamera::CTrackingCamera() : CCamera()
{
	m_velocity = { 0.0f, 0.0f, 0.0f };

	m_Target = nullptr;
}

//==============================================================================
//  関数名        CTrackingCamera	
//  説明          追跡カメラクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CTrackingCamera& other			CTrackingCameraのインスタンス
//	戻り値
//          なし
//==============================================================================
CTrackingCamera::CTrackingCamera(const CTrackingCamera& other)
{
	//空
}

//==============================================================================
//  関数名        ～CTrackingCamera	
//  説明          追跡カメラクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CTrackingCamera::~CTrackingCamera()
{
	m_Target = nullptr;
}

void CTrackingCamera::Initialize()
{
	if (!m_Target) return;

	XMFLOAT3 targetPos;
	targetPos = m_Target->GetWorldPos();

	m_velocity = { 0.0f, 0.0f, 0.0f };

	m_fPosX = m_targetX = targetPos.x;
	m_fPosY = m_targetY = targetPos.y;
	m_targetZ = m_fPosZ;
	
}

//==============================================================================
//  関数名        Action
//  説明			追跡カメラの処理関数
//------------------------------------------------------------------------------
//	引数
//			なし
//	戻り値
//          なし
//==============================================================================
void CTrackingCamera::Action()
{
	if (!m_Target)	return;

	UpdateTargetPosition();

	m_fPosX = m_targetX;
	//UpdateCameraPosition();
}

void CTrackingCamera::UpdateTargetPosition()
{
	XMFLOAT3 targetPos;

	targetPos = m_Target->GetWorldPos();

	m_targetX = targetPos.x;
	m_targetY = targetPos.y;
	m_targetZ = targetPos.z;

}

void CTrackingCamera::UpdateCameraPosition()
{
	float dist, k;
	XMFLOAT3 force, orientation;

	k = 1.0f;

	dist = CalculateDistance({ m_fPosX, m_fPosY, 0.0f }, { m_targetX, m_targetY, 0.0f }, orientation);
	dist -= CAMERA_THRESHOLD;

	if (dist > 0.0f)
	{
  		force.x = -k * dist * orientation.x;
		force.y = -k * dist * orientation.y;
		force.z = -k * dist * orientation.z;
		
		//速度を足す
		m_velocity.x += force.x / 60.0f;
		m_velocity.y += force.y / 60.0f;
		m_velocity.z += force.z / 60.0f;
		
		//動きを止まる
		if (m_velocity.x < 0.01 && m_velocity.x > -0.01f)
			m_velocity.x = 0;
		
		if (m_velocity.y < 0.01 && m_velocity.y > -0.01f)
			m_velocity.y = 0;
		
		if (m_velocity.z < 0.01 && m_velocity.z > -0.01f)
			m_velocity.z = 0;
		
		m_fPosX += m_velocity.x;
		m_fPosY += m_velocity.y;
	//	m_fPosZ += m_velocity.z;

	}
	else
	{
		m_velocity.x -= 0.1f;
		m_velocity.y -= 0.1f;
		m_velocity.z -= 0.1f;

		if (m_velocity.x < 0.01 && m_velocity.x > -0.01f)
			m_velocity.x = 0;

		if (m_velocity.y < 0.01 && m_velocity.y > -0.01f)
			m_velocity.y = 0;

		if (m_velocity.z < 0.01 && m_velocity.z > -0.01f)
			m_velocity.z = 0;
	}
}

//==============================================================================
//  関数名       SetTarget
//  説明			追跡カメラのターゲットをセット
//------------------------------------------------------------------------------
//	引数
//			CGameObjectBase*		ターゲットのポインタ
//	戻り値
//          なし
//==============================================================================
void CTrackingCamera::SetTarget(CGameObjectBase* target)
{
	m_Target = target;
}