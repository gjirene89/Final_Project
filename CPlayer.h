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
# include "CSackBase.h"
# include "CHit_Base.h"
# include "CRope.h"

//=============================================================================
//!	@class	CPlayer
//!	@brief プレイヤー
//=============================================================================
class CPlayer : public CSackBase
{
public:	
	
	CPlayer(float posX, float posY);			//コンストラクタ
	~CPlayer(void);								//デストラクタ
	
	void Init		(void);						//初期化関数
	void Input		(void);						//入力関数
	void Action		(void);						//処理関数
	void PostAction	(void);						//後処理関数

	void MoveRight	(void);						//右へ移動
	void MoveLeft	(void);						//左へ移動
	void FlipString	(void);						//紐を振り回す
	void Dash		(void);						//ダッシュ
	void HitWall	(void);						//壁とぶっつかる
	void LeaveWall	(void);						//壁から離れる

private:

	D3DXQUATERNION	quaternion;			//クオータニオン

	void UpdateRotation		(void);		//回転の更新
};

#endif // !__GM31_CPLAYER__

//******************************************************************************
//	End of file.
//******************************************************************************