//******************************************************************************
//	HitSphereClass.h
//  球のあたり判定クラス
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************

#ifndef __HIT_SPHERE_H__
#define __HIT_SPHERE_H__

//==============================================================================
//		インクルード
//==============================================================================
//# include "CDirectxGraphics.h"
# include "HitBaseClass.h"
//# include "CHit_Box.h"
//# include "C3DObject.h"

//==============================================================================
//	クラス名		CHit_Sphere
//==============================================================================
class CHit_Sphere : public CHit_Base
{
public:
	CHit_Sphere(float radius_, GAMEHIT_TYPE type, CGameObjectBase* entity);
	~CHit_Sphere(void);

	void Render(void);

	float GetRadius(void);

	CGameObjectBase* CheckHit(CHit_Base *pHit, GAMEHIT_TYPE objType);
	CGameObjectBase* CheckBoxHit(CHit_Base *pBoxHit);
	CGameObjectBase* CheckSphereHit(CHit_Base *pSphereHit);

	bool CheckStage();
private:

	float		m_radius;
	//static C3DObject	*sphere;

};

#endif