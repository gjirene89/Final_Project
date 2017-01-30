//************************************************************************//
//	BeadsClass.h
//	2017-01-23
//	Irene Gersenowies
//************************************************************************//

#ifndef __CBEADS_H__
#define __CBEADS_H__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
//# include "C3DObject.h"
# include "GameObjectBase.h"
# include "HitBaseClass.h"
# include "ModelClass.h"

//-----------------------------------------------------------------------------
//	マクロ定数
//-----------------------------------------------------------------------------
//# define	BLOCK_SIZE	10.0f

//=============================================================================
//!	@class	CBeads
//!	@brief ゴールクラス
//=============================================================================
class CBeads : public CGameObjectBase
{
public:

	CBeads();							//コンストラクタ
	CBeads(const CBeads& other) {};
	~CBeads(void);						//デストラクタ

	virtual void Initialize(XMMATRIX& parent);							//初期化関数
	virtual void Action(XMMATRIX& parent);							//処理関数
	virtual void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light);							//描画関数
	virtual void PostAction(void);						//後処理関数

	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown(void);

	XMFLOAT3 GetResForce(void);						//合力を戻す関数
	void SetOppositeForce(XMFLOAT3 pullForce);		//引っ張る力をセットする関数
	void SetSpringForce(XMFLOAT3 force);				//バネの力をセットする
	void SetLocalPosition(float posX, float posY, float posZ);				//ローカル位置をセットする

	void LockAngle(float angle);
	void UpdateAngle(XMFLOAT3 orientation);
	void LockBead(XMFLOAT3 hookPos);
	void UnLockBead(void);

private:
	
	float	m_k;
	float	m_lenght;
	float	m_angle;						//角度
	//D3DXVECTOR3 orientation;			//バネの向き
	bool	m_isLocked;					//位置が固定されているかどうか
	bool	m_isAngleLocked;
	//D3DXMATRIX	LocalMat;				//ローカル行列
//	XMMATRIX		m_LocalMat;
	CHit_Base* m_pHit;					//当たり判定

	float m_gravForce;					//重力
	XMFLOAT3 m_pullForce;				//引っ張る力
	XMFLOAT3 m_resForce;				//合力
	XMFLOAT3 m_springForce;			//バネの力

	XMFLOAT3 m_accel;					//加速度
	XMFLOAT3 m_velocity;				//速度
	
	static CModel* m_beadModel;			//玉のモデル

	void CalcResForce(void);			//合力を求める関数
	void SetHit(void);					//当たり判定の情報をセットする

};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************