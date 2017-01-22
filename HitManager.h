//*****************************************************************************
//!	@file	HitManager.h
//!	@brief	あたり判定用
//!	@note	
//!	@author　イレネ　ヘルセノウイス　ハソ
//*****************************************************************************

#ifndef __HIT_MANAGER__
#define __HIT_MANAGER__

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
//# include "BoundingSphere.h"
# include "GameObjectBase.h"
//# include "C3DObject.h"
# include "HitBaseClass.h"

//-----------------------------------------------------------------------------
//	マクロ数
//-----------------------------------------------------------------------------
# define	MAX_HIT_CNT		1000			//最大のあたり判定の件数

//=============================================================================
//!	@class	HitManager
//!	@brief	当たり判定の管理クラス
//=============================================================================
class HitManager
{
public:
	HitManager(void);
	~HitManager(void);

	void Init(void);
	void Reset(void);
	void Render(void);

	static void AddHit(CHit_Base *newObj);
	static CGameObjectBase* CheckHit(CHit_Base *pHit, GAMEHIT_TYPE objType);
	static bool CheckStage(CHit_Base *pHit);

private:

	bool	isVisible;						//あたり判定を描画するかどうか

	static int	nHitCnt;						//あたり判定の配列に入ってあるゲームオブジェクトの数
	static CHit_Base *hitList[MAX_HIT_CNT];	//あたり判定の配列

	void RenderDebug(void);

	
};


#endif