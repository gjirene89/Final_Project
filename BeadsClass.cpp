//*****************************************************************************
//!	@file	CBeads.cpp
//!	@brief	丸いオブジェクトのクラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "BeadsClass.h"
# include "HitSphereClass.h"
# include "HitManager.h"
# include "Macros.h"
# include "MathUtility.h"
# include "ShaderManager.h"
//# include "Debug.h"

//-----------------------------------------------------------------------------
//	マクロ定数
//-----------------------------------------------------------------------------

//==============================================================================
//	グローバル変数
//==============================================================================
CModel* CBeads::m_beadModel = nullptr;

//==============================================================================
//!	@fn		CBeads
//!	@brief	玉のコンストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CBeads::CBeads(void) : CGameObjectBase(GOBJ_BEAD)
{
	m_gravForce = 0;

	m_isAngleLocked = false;
	m_angle = 0.0f;
	m_k = SPRING_COEFFICIENT;
	m_lenght = BEAD_LENGHT;
	
	m_pHit = new CHit_Sphere(BEAD_RADIUS, GAMEHIT_TYPE::HIT_BEAD, this);
	//D3DXMatrixIdentity(&LocalMat);
}

//==============================================================================
//!	@fn		~CBeads
//!	@brief	玉のデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CBeads::~CBeads(void)
{
	if (m_pHit != nullptr)	delete m_pHit;
}

//==============================================================================
//!	@fn		Init
//!	@brief	玉の初期化関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void CBeads::Initialize(XMMATRIX& parent)
{
	XMMATRIX rotMat, transMat;
	m_isLocked = false;

	//初期化
	m_velocity = m_accel = { 0.0f, 0.0f, 0.0f };
	m_pullForce = m_resForce = { 0.0f, 0.0f, 0.0f };


	transMat = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	rotMat = XMMatrixRotationX(XMConvertToRadians(m_angle));

	//D3DXMatrixRotationX(&rotMat, D3DXToRadian(angle));

	//m_LocalMat = transMat * rotMat;

	m_matrix = transMat * rotMat * parent;
//	m_matrix = totalMat;
}

//==============================================================================
//!	@fn		SetHit
//!	@brief	当たり判定の情報を更新する
//!	@param	なし
//!	@retval	なし
//==============================================================================
void CBeads::SetHit(void)
{
	m_pHit->UpdatePosition(GetWorldPos());
	HitManager::AddHit(m_pHit);
}

//==============================================================================
//!	@fn		Render
//!	@brief	玉を描画する
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CBeads::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light)
{
	//C3DObject::Render();

	//if (CDebug::displayAxis && !CDebug::GetIsHidden())
		//RenderAxis();
//	CalculateWorldMatrix(m_matrix, m_rotation.x, m_rotation.y, m_rotation.z);
//	worldMatrix = worldMatrix * m_matrix;
	m_beadModel->Render(deviceContext);
	CShaderManager::getInstance().RenderColorShader(deviceContext, m_beadModel->GetIndexCount(), m_matrix, viewMatrix, projectionMatrix, XMFLOAT4(1.0, 0.0, 0.0, 1.0));
	//CShaderManager::getInstance().RenderSpecularShader(deviceContext, m_beadModel->GetIndexCount(),
	//	m_matrix, viewMatrix, projectionMatrix,
	//	COLOR, light->GetDirection(), light->GetAmbientColor(), light->GetDiffuseColor(),
	//	cameraPosition,
	//	light->GetSpecularColor(), light->GetSpecularPower());

}

//==============================================================================
//!	@fn		Action
//!	@brief	玉の処理関数
//!	@param	D3DXMATRIX　totalMat		蹴鞠の変換行列
//!	@retval	なし
//==============================================================================
void CBeads::Action(XMMATRIX& parent)
{
	XMFLOAT3 newOrient;
	XMFLOAT4X4 parentMatrix, myMatrix;
	XMMATRIX worldMat;
	float dist;

	XMStoreFloat4x4(&parentMatrix, parent);
	XMStoreFloat4x4(&myMatrix, m_matrix);

	if (m_isAngleLocked)
	{
//		XMMATRIX tempMat = totalMat * m_LocalMat;

		dist = CalculateDistance({ parentMatrix._41, parentMatrix._42, parentMatrix._43 }, { myMatrix._41, myMatrix._42, myMatrix._43 }, newOrient);
		//dist -= BEAD_LENGHT;

		float distX = (dist * newOrient.x) - (m_lenght * myMatrix._31);
		float distY = (dist * newOrient.y) - (m_lenght * myMatrix._32);
		float distZ = (dist * newOrient.z) - (m_lenght * myMatrix._33);

		m_springForce.x = -m_k * distX;
		m_springForce.y = -m_k * distY;
		m_springForce.z = -m_k * distZ;

	}
	else
	{
		dist = CalculateDistance({ parentMatrix._41, parentMatrix._42, parentMatrix._43 }, { myMatrix._41, myMatrix._42, myMatrix._43 }, newOrient);
		dist -= m_lenght;

		//if (dist < lenght / 2.0f) dist = lenght / 2.0f;
		//if (dist > lenght * 2.0f) dist = lenght * 2.0f;

		m_springForce.x = -m_k * dist * newOrient.x;
		m_springForce.y = -m_k * dist * newOrient.y;
		m_springForce.z = -m_k * dist * newOrient.z;

	}
	
	if (m_isLocked) return;

	CalcResForce();

	//加速度を求める
	if (BEAD_MASS == 0)
		m_accel.x = m_accel.y = m_accel.z = 0;
	else
	{
		m_accel.x = m_resForce.x / BEAD_MASS;
		m_accel.y = m_resForce.y / BEAD_MASS;
		m_accel.z = m_resForce.z / BEAD_MASS;
	}
	//速度を足す
	m_velocity.x += m_accel.x / 60.0f;
	m_velocity.y += m_accel.y / 60.0f;
	m_velocity.z += m_accel.z / 60.0f;

	//速度を遅くする
	m_velocity.x -= m_velocity.x * AIR_FRICTION;
	m_velocity.y -= m_velocity.y * AIR_FRICTION;
	m_velocity.z -= m_velocity.z * AIR_FRICTION;

	//動きを止まる
	if (m_velocity.x < 0.01 && m_velocity.x > -0.01f)
		m_velocity.x = 0;

	if (m_velocity.y < 0.01 && m_velocity.y > -0.01f)
		m_velocity.y = 0;

	if (m_velocity.z < 0.01 && m_velocity.z > -0.01f)
		m_velocity.z = 0;

	//D3DXVECTOR3 pos = GetWorldPos();

	myMatrix._41 += m_velocity.x;
	myMatrix._42 += m_velocity.y;
	myMatrix._43 += m_velocity.z;

	parent = m_matrix = XMLoadFloat4x4(&myMatrix);

	SetHit();

}

//==============================================================================
//!	@fn		PostAction
//!	@brief	玉の後処理関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void CBeads::PostAction(void)
{
	if (HitManager::CheckStage(m_pHit))
	{
	//	matrix._41 -= velocity.x;
		//matrix._42 -= velocity.y;
	}

	//合力を求める
	//CalcResForce();
}

XMFLOAT3 CBeads::GetResForce(void)
{
	return m_springForce;
}

void CBeads::SetOppositeForce(XMFLOAT3 force)
{
	m_pullForce.x = -force.x; //* 0.8;
	m_pullForce.y = -force.y; //* 0.8f;
	m_pullForce.z = -force.z;
}

void CBeads::SetSpringForce(XMFLOAT3 force)
{
	m_springForce = force;
}

void CBeads::SetLocalPosition(float posX, float posY, float posZ)
{
	m_position.x = posX;
	m_position.y = posY;
	m_position.z = posZ;
}

void CBeads::CalcResForce(void)
{
	//重力の力を求める
	m_gravForce = GRAVITY * BEAD_MASS;

	//合力を求める
	m_resForce.x = m_pullForce.x + m_springForce.x;
	m_resForce.y = m_pullForce.y + m_gravForce + m_springForce.y;
	m_resForce.z = m_pullForce.z + m_springForce.z;

	if (m_resForce.x > 10)
		m_resForce.x = 10;

	if (m_resForce.y > 10)
		m_resForce.y = 10;

	if (m_resForce.z > 10)
		m_resForce.z = 10;

	if (m_resForce.x < -10)
		m_resForce.x = -10;

	if (m_resForce.y < -10)
		m_resForce.y = -10;

	if (m_resForce.z < -10)
		m_resForce.z = -10;
}

void CBeads::LockBead(XMFLOAT3 hookPos)
{
	m_isLocked = true;
	SetPosition(hookPos.x, hookPos.y, hookPos.z);
	//SetDiffuse({ 1.0f, 1.0f, 0.0f, 1.0f });
}

void CBeads::LockAngle(float angle)
{
	m_isAngleLocked = true;
	m_angle = angle;
	m_k = SPRING_COEFFICIENT * 1.5;
	//lenght = 3;

}

void CBeads::UnLockBead(void)
{
	m_isLocked = false;
	//SetDiffuse({ 1.0f, 0.0f, 0.0f, 1.0f });


}

void CBeads::UpdateAngle(XMFLOAT3 orientation_)
{
	//if (!isAngleLocked) return;

	//D3DXMATRIX tempMat, rotMat;
	//D3DXMatrixIdentity(&tempMat);
	//tempMat._31 = orientation_.x;
	//tempMat._32 = orientation_.y;
	//tempMat._33 = orientation_.z;

	//D3DXMatrixRotationZ(&rotMat, D3DXToRadian(angle));

	//tempMat = tempMat * rotMat;

	//orientation.x = tempMat._31;
	//orientation.y = tempMat._32;
	//orientation.z = tempMat._33;

	//D3DXVec3Normalize(&orientation, &orientation);
}


bool CBeads::InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;

	if (m_beadModel) return true;

	//********************//
	// 　紐についている玉　 //
	//********************//
	m_beadModel = new CModel;
	if (!m_beadModel)
	{
		return false;
	}

	result = m_beadModel->Initialize(device, "Resources/Model/bead.txt");
	if (!result)
	{
		return false;
	}

	return true;
}

void CBeads::Shutdown(void)
{
	if (m_beadModel != nullptr)
	{
		m_beadModel->Shutdown();
		delete m_beadModel;
		m_beadModel = nullptr;
	}

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************