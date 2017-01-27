//************************************************************************//
//	RopeClass.h
//	2017-01-23
//	Irene Gersenowies
//************************************************************************//

#ifndef __GM31_ROPE__
#define __GM31_ROPE__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
//# include "C3DObject.h"
#include "GameObjectBase.h"
# include "HitBaseClass.h"
# include "BeadsClass.h"
# include "Macros.h"

//-----------------------------------------------------------------------------
//	マクロ定数
//-----------------------------------------------------------------------------


//=============================================================================
//!	@class	CRope
//!	@brief 紐クラス
//=============================================================================
class CRope : public CGameObjectBase
{
public:

	CRope() {};
	CRope(XMFLOAT3 hinge);		//コンストラクタ
	CRope(const CRope& other) {};
	~CRope(void);						//デストラクタ

	void Initialize(XMMATRIX parent);
	void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void Action(XMMATRIX parent);
	void PostAction(void);

	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown(void);

	void LockEnd(XMFLOAT3 hookPos);
	void ClearLock(void);
	float GetPullForce(void);
	float GetPullAngle(void);


private:

	CBeads* m_beads;
	XMFLOAT3 m_hinge;

	//void UpdatePosition(XMMATRIX parent);

};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************