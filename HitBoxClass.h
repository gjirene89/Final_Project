//******************************************************************************
//	HitBoxClass.h
//  箱のあたり判定クラス
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************

#ifndef __HIT_BOX_H__
#define __HIT_BOX_H__

//==============================================================================
//		インクルード
//==============================================================================
# include "HitBaseClass.h"
# include "HitSphereClass.h"
//# include "CDirectxGraphics.h"
//# include "C3DObject.h"

//==============================================================================
//	クラス名		CHit_Box
//==============================================================================
class CHit_Box : public CHit_Base
{

public:
	CHit_Box(float sizeX, float sizeY, float sizeZ, GAMEHIT_TYPE type, CGameObjectBase* entity);
	~CHit_Box(void);

	void Render(void);

	XMFLOAT3 GetDimension(void);

	CGameObjectBase* CheckHit(CHit_Base *pHit, GAMEHIT_TYPE objType);
	CGameObjectBase* CheckBoxHit(CHit_Base *pBoxHit);
	CGameObjectBase* CheckSphereHit(CHit_Base *pSphereHit);

	bool CheckStage(void);
private:

	XMFLOAT3			 m_dimension;			//サイズ
												//	static C3DObject	*m_box;

};

#endif