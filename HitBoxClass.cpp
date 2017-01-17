//*****************************************************************************
//!	@file	CHit_Sphere.cpp
//!	@brief	球のあたり判定の関数群
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

# include "HitBoxClass.h"
//# include "mathutil.h"
# include "StageClass.h"

//C3DObject* CHit_Box::box;

//==============================================================================
//!	@fn		CHit_Box
//!	@brief	箱のあたり判定のコンストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CHit_Box::CHit_Box(float sizeX, float sizeY, float sizeZ, GAMEHIT_TYPE type, CGameObjectBase* entity) : CHit_Base(type)
{
	m_entity = entity;
	m_dimension = {sizeX, sizeY, sizeZ};

	/*
	if (box == nullptr)
	{
		box = new C3DObject(GAMEOBJTYPE::GOBJ_BOUNDS);
		box->InitMaterial();
		box->SetDiffuse(color);

		LPD3DXMESH tempMesh;
		D3DXCreateBox(CDirectXGraphics::GetDXDevice(), 1, 1, 1, &tempMesh, nullptr);
		box->SetMesh(tempMesh);
	}
	*/
}

//==============================================================================
//!	@fn		~CHit_Box
//!	@brief	箱のあたり判定のデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CHit_Box::~CHit_Box()
{
	/*
	if (box != nullptr)
		delete box;
	*/
}

void CHit_Box::Render()
{
	if (!m_isVisible) return;
	
	/*
	box->SetDiffuse(color);
	box->SetSize(dimension);
	box->SetPosition(position);
	box->Render();
	*/
}

CGameObjectBase* CHit_Box::CheckHit(CHit_Base *pHit, GAMEHIT_TYPE gObjType)
{
	if (pHit == this || pHit->GetHitType() != gObjType || pHit->GetEntity() == m_entity)
		return nullptr;

	return pHit->CheckBoxHit(this);
	
}

CGameObjectBase* CHit_Box::CheckBoxHit(CHit_Base *pBoxHit)
{
	XMFLOAT3 hitPos = pBoxHit->GetPosition();
	XMFLOAT3 hitDim = ((CHit_Box*)pBoxHit)->GetDimension();

	if (hitPos.x + hitDim.x / 2.0f < m_position.x - m_dimension.x / 2.0f) return nullptr;
	if (hitPos.x - hitDim.x / 2.0f > m_position.x + m_dimension.x / 2.0f) return nullptr;

	if (hitPos.y + hitDim.y / 2.0f < m_position.y - m_dimension.y / 2.0f) return nullptr;
	if (hitPos.y - hitDim.y / 2.0f > m_position.y + m_dimension.y / 2.0f) return nullptr;

	if (hitPos.z + hitDim.z / 2.0f < m_position.z - m_dimension.z / 2.0f) return nullptr;
	if (hitPos.z - hitDim.z / 2.0f > m_position.z + m_dimension.z / 2.0f) return nullptr;

	return m_entity;
}


CGameObjectBase* CHit_Box::CheckSphereHit(CHit_Base *pSphereHit)
{
	XMFLOAT3 hitPos = pSphereHit->GetPosition();
	float radius = ((CHit_Sphere*)pSphereHit)->GetRadius();

	if (hitPos.x + radius < m_position.x - m_dimension.x / 2.0f) return nullptr;
	if (hitPos.x - radius > m_position.x + m_dimension.x / 2.0f) return nullptr;

	if (hitPos.y + radius < m_position.y - m_dimension.y / 2.0f) return nullptr;
	if (hitPos.y - radius > m_position.y + m_dimension.y / 2.0f) return nullptr;

	if (hitPos.z + radius < m_position.z - m_dimension.z / 2.0f) return nullptr;
	if (hitPos.z - radius > m_position.z + m_dimension.z / 2.0f) return nullptr;

	return m_entity;
}

bool CHit_Box::CheckStage()
{
	float maxX, maxY;// maxZ;
	float minX, minY;// minZ;

	maxX = m_position.x + m_dimension.x / 2.0f;
	maxY = m_position.y + m_dimension.y / 2.0f;
//	maxZ = position.z + dimension.z / 2.0f;

	minX = m_position.x - m_dimension.x / 2.0f;
	minY = m_position.y - m_dimension.y / 2.0f;
//	minZ = position.z - dimension.z / 2.0f;

	if (CStage::isThereBlock(minX, minY))	return true;
	if (CStage::isThereBlock(minX, maxY))	return true;
	if (CStage::isThereBlock(maxX, minY))	return true;
	if (CStage::isThereBlock(maxX, maxY))	return true;

	return false;
}

XMFLOAT3 CHit_Box::GetDimension(void)
{
	return m_dimension;
}
//******************************************************************************
//	End of file.
//******************************************************************************