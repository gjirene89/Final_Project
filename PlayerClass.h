//*****************************************************************************
//!	@file	CPlayer.h
//!	@brief	プレイヤーのヘッダの集まり
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_CPLAYER__
#define __GM31_CPLAYER__

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
# include "SackBaseClass.h"
# include "HitBaseClass.h"
//# include "CRope.h"

//=============================================================================
//!	@class	CPlayer
//!	@brief プレイヤー
//=============================================================================
class CPlayer : public CSackBase
{
public:	
	
	CPlayer(float posX, float posY);			//コンストラクタ
	~CPlayer(void);								//デストラクタ
	
	void Initialize	(void);						//初期化関数
	void Input		(CInput* input);						//入力関数
	void Action		(void);						//処理関数
	void Render		(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light);
	void PostAction	(void);						//後処理関数

	void MoveRight	(void);						//右へ移動
	void MoveLeft	(void);						//左へ移動
	void FlipString	(void);						//紐を振り回す
	void Dash		(void);						//ダッシュ
	void HitWall	(void);						//壁とぶっつかる
	void LeaveWall	(void);						//壁から離れる

private:

	XMVECTOR		m_quaternion;			//クオータニオン

	void UpdateRotation		(void);		//回転の更新
};

#endif // !__GM31_CPLAYER__

//******************************************************************************
//	End of file.
//******************************************************************************