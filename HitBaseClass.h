//************************************************************************//
//	HitBaseClass.cpp
//  あたり判定クラスのベース
//	2017-01-16
//	Irene Gersenowies
//************************************************************************//

#ifndef __HIT_BASE_H__
#define __HIT_BASE_H__

//==============================================================================
//		インクルード
//==============================================================================
#include "GameObjectBase.h"

//==============================================================================
//	マクロ定数
//==============================================================================
# define MAX_HIT            1000

# define COLOR_HLIGHT		{10.0f, 10.0f, 0.0f, 0.3f}
# define COLOR_NORMAL		{1.0f, 1.0f, 1.0f, 0.3f}

enum GAMEHIT_TYPE
{
	HIT_NONE,
	HIT_SUPPORT,			//あたり判定
	HIT_PLAYER,				//プレイヤー
	HIT_SACK,
	HIT_GOAL,				//ゴール
	HIT_BEAD,

	HIT_MAX									//オブジェクトの種類の最大数
};

//==============================================================================
//	クラス名		CSacksBase
//==============================================================================
class CHit_Base
{
protected:
	CGameObjectBase*			m_entity;				//ゲームオブジェクト
	GAMEHIT_TYPE				m_type;					//オブジェクトの種類
	XMFLOAT3					m_position;				//位置
	bool						m_isVisible;			//描画するかどうかフラグ
	bool						m_isHit;				//当たっているかどうか
	D3DCOLORVALUE				m_color;				//色


public:
	CHit_Base(void);
	CHit_Base(GAMEHIT_TYPE type);
	CHit_Base(const CHit_Base& other);
	~CHit_Base(void);

	void Initialize(void);
	void UpdatePosition(XMFLOAT3 position);
	void Highlight(void);

	GAMEHIT_TYPE GetHitType(void);
	XMFLOAT3 GetPosition(void);
	CGameObjectBase* GetEntity(void);

	virtual void Render() = 0;
	virtual CGameObjectBase* CheckHit(CHit_Base *pHit, GAMEHIT_TYPE objType) = 0;
	virtual CGameObjectBase* CheckBoxHit(CHit_Base *pBoxHit) = 0;
	virtual CGameObjectBase* CheckSphereHit(CHit_Base *pSphereHit) = 0;
	virtual bool CheckStage(void) = 0;
};

#endif
