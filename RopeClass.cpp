//*****************************************************************************
//!	@file	CRope.h
//!	@brief	紐オブジェクト
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "RopeClass.h"
//# include "CDirectxGraphics.h"
# include "Macros.h"
# include "HitBoxClass.h"
# include "HitManager.h"
# include "MathUtility.h"
//# include "Debug.h"

//-----------------------------------------------------------------------------
//	マクロ定数
//-----------------------------------------------------------------------------


//==============================================================================
//!	@fn		CRope
//!	@brief	紐のコンストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CRope::CRope(XMFLOAT3 hinge) : CGameObjectBase(GAMEOBJTYPE::GOBJ_BEAD)
{
	//InitMaterial();
	//SetDiffuse({ 1.0f, 0.0f, 0.0f, 1.0f });
	//D3DXCreateSphere(CDirectXGraphics::GetDXDevice(), BEAD_SIZE, 8, 8, &mesh, nullptr);

	m_hinge = hinge;

	m_beads = new CBeads[BEAD_NO];

	for (int seg = 0; seg < BEAD_NO; seg++)
	{
		m_beads[seg].SetLocalPosition(0.0f, 0.0f, BEAD_LENGHT);
	}

	m_beads[0].LockAngle(-90);
	m_beads[1].LockAngle(-60);
	m_beads[2].LockAngle(-30);

	//isHooked = false;
	
}

//==============================================================================
//!	@fn		~CRope
//!	@brief	紐のデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CRope::~CRope(void)
{
	delete[] m_beads;
	//delete[] rope;
}

void CRope::Initialize(XMMATRIX parent)
{
//	isHooked = false;

	m_matrix = XMMatrixTranslation(m_hinge.x, m_hinge.y, m_hinge.z);
	//D3DXMatrixTranslation(&matrix, hinge.x, hinge.y, hinge.y);

	//D3DXMatrixRotationY(&rotY, D3DXToRadian(90));
	m_matrix = m_matrix * parent;

	//各部分の初期化
	XMMATRIX	totalMat = m_matrix;
	for (int seg = 0; seg < BEAD_NO; seg++)
		m_beads[seg].Initialize(totalMat);

	
}

void CRope::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light)

{
	//C3DObject::Render();

	//if (CDebug::displayAxis && !CDebug::GetIsHidden())
	//	RenderAxis();

	//各部分の描画関数
	for (int seg = 0; seg < BEAD_NO; seg++)
		m_beads[seg].Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix, cameraPosition, light);

}


void CRope::Action(XMMATRIX parent)
{
	m_matrix = XMMatrixTranslation(m_hinge.x, m_hinge.y, m_hinge.z);
	//D3DXMatrixIdentity(&m_matrix);
	//D3DXMatrixTranslation(&m_matrix, m_hinge.x, m_hinge.y, m_hinge.y);
	m_matrix = m_matrix * parent;
	
	XMMATRIX totalMat = m_matrix;

	//各部分の処理関数
	for (int seg = 0; seg < BEAD_NO; seg++)
	{
		//beads[seg].UpdateAngle();
		m_beads[seg].Action(totalMat);
	}
}

void CRope::PostAction(void)
{
	//各部分の後処理関数を呼び出す
	for (int seg = 0; seg < BEAD_NO; seg++)
		m_beads[seg].PostAction();
	
	//各部分の反対力を設定する
	for (int seg = BEAD_NO - 2; seg >= 0; seg--)
		m_beads[seg].SetOppositeForce(m_beads[seg + 1].GetResForce());
}

//void CRope::UpdatePosition(D3DXMATRIX position)
//{
//	D3DXMATRIX	totalMat;
//	D3DXMatrixIdentity(&totalMat);
//	D3DXMatrixTranslation(&totalMat, hinge.x, hinge.y, hinge.z);
//
//	//D3DXMatrixRotationY(&rotY, D3DXToRadian(90));
//	totalMat = totalMat * position;
//}

void CRope::LockEnd(XMFLOAT3 hookPos)
{
	m_beads[BEAD_NO - 1].LockBead(hookPos);
}

void CRope::ClearLock(void)
{
	m_beads[BEAD_NO - 1].UnLockBead();
}

float CRope::GetPullForce(void)
{
	return CalculateDistance({ 0.0f, 0.0f, 0.0f }, m_beads[BEAD_NO - 1].GetResForce());
}

float CRope::GetPullAngle(void)
{
	float angle = CalculateAngle({ 1.0f, 0.0f, 0.0f }, m_beads[BEAD_NO - 1].GetResForce());
	 
	angle = XMConvertToDegrees(angle);
	return angle;
	
}

bool CRope::InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;
	for (int beadsNo = 0; beadsNo < BEAD_NO; beadsNo++)
	{
		result = m_beads[beadsNo].InitializeObject(device, deviceContext);
		if (!result)
		{
			return false;
		}
			
	}

	return true;
}

void CRope::Shutdown(void)
{
	for (int beadsNo = 0; beadsNo < BEAD_NO; beadsNo++)
	{
		m_beads[beadsNo].Shutdown();
	}
	return;
}
//******************************************************************************
//	End of file.
//******************************************************************************