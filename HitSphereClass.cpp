//******************************************************************************
//	HitSphereClass.cpp
//  球のあたり判定クラス
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************

# include "HitSphereClass.h"
# include "HitBoxClass.h"
# include "MathUtility.h"
# include "StageClass.h"

//C3DObject* CHit_Sphere::sphere;

//==============================================================================
//!	@fn		CHitSphere
//!	@brief	球のあたり判定のコンストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CHit_Sphere::CHit_Sphere(float radius, GAMEHIT_TYPE type, CGameObjectBase* entity) : CHit_Base(type)
{
	m_entity = entity;
	m_radius = radius;

	/*
	if (sphere == nullptr)
	{
	sphere = new C3DObject(GAMEOBJTYPE::GOBJ_BOUNDS);
	sphere->InitMaterial();
	sphere->SetDiffuse(color);

	LPD3DXMESH tempMesh;
	D3DXCreateSphere(CDirectXGraphics::GetDXDevice(), 1, 10, 10, &tempMesh, nullptr);
	sphere->SetMesh(tempMesh);
	}
	*/
}

//==============================================================================
//!	@fn		~CHitSphere
//!	@brief	球のあたり判定のデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CHit_Sphere::~CHit_Sphere()
{
	/*
	if (sphere != nullptr)
	delete sphere;
	*/
}

void CHit_Sphere::Render()
{
	if (!m_isVisible) return;

	/*
	sphere->SetDiffuse(color);
	sphere->SetSize({radius,radius,radius});
	sphere->SetPosition(position);
	sphere->Render();
	*/
}

CGameObjectBase* CHit_Sphere::CheckHit(CHit_Base *pHit, GAMEHIT_TYPE gObjType)
{
	if (pHit == this || pHit->GetHitType() != gObjType || pHit->GetEntity() == m_entity)
		return nullptr;

	return pHit->CheckSphereHit(this);

}

CGameObjectBase* CHit_Sphere::CheckSphereHit(CHit_Base *pSphereHit)
{
	XMFLOAT3 hitPos = pSphereHit->GetPosition();

	if (CalculateDistance(hitPos, m_position) < ((CHit_Sphere*)pSphereHit)->GetRadius() + m_radius)
		return m_entity;

	return nullptr;

}


CGameObjectBase* CHit_Sphere::CheckBoxHit(CHit_Base *pBoxHit)
{
	XMFLOAT3 hitPos = pBoxHit->GetPosition();
	XMFLOAT3 hitDim = ((CHit_Box*)pBoxHit)->GetDimension();

	if (hitPos.x + hitDim.x / 2.0f < m_position.x - m_radius) return nullptr;
	if (hitPos.x - hitDim.x / 2.0f > m_position.x + m_radius) return nullptr;

	if (hitPos.y + hitDim.y / 2.0f < m_position.y - m_radius) return nullptr;
	if (hitPos.y - hitDim.y / 2.0f > m_position.y + m_radius) return nullptr;

	if (hitPos.z + hitDim.z / 2.0f < m_position.z - m_radius) return nullptr;
	if (hitPos.z - hitDim.z / 2.0f > m_position.z + m_radius) return nullptr;

	return m_entity;
}

bool CHit_Sphere::CheckStage(void)
{
	float maxX, maxY;// maxZ;
	float minX, minY;// minZ;

	maxX = m_position.x + m_radius;
	maxY = m_position.y + m_radius;
	//	maxZ = position.z + radius;

	minX = m_position.x - m_radius;
	minY = m_position.y - m_radius;
	//	minZ = position.z - radius;

	if (CStage::isThereBlock(minX, minY))	return true;
	if (CStage::isThereBlock(minX, maxY))	return true;
	if (CStage::isThereBlock(maxX, minY))	return true;
	if (CStage::isThereBlock(maxX, maxY))	return true;

	return false;
}

float CHit_Sphere::GetRadius(void)
{
	return m_radius;
}
//******************************************************************************
//	End of file.
//******************************************************************************