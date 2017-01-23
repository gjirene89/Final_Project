//************************************************************************//
//	SackBaseClass.h
//	2017-01-16
//	Irene Gersenowies
//************************************************************************//

#ifndef __SACK_BASE_H__
#define __SACK_BASE_H__

//==============================================================================
//		インクルード
//==============================================================================
# include "GameObjectBase.h"
# include "SackStateBase.h"
# include "HitBaseClass.h"
# include "ModelClass.h"
//# include "CXFile.h"
//# include "CDebugFont.h"
//# include "HitManager.h"
//# include "Macros.h"
//# include "Debug.h"
//# include "CRope.h"
//# include "ModelManager.h"
//# include "TextureManager.h"

//==============================================================================
//	マクロ定数
//==============================================================================
# define LOOK_ANGLE	(-30.0f * XM_PI / 180.0f)


//==============================================================================
//	クラス名		CSacksBase
//==============================================================================
class CSackBase : public CGameObjectBase
{
public:
	//プレイヤーの向き
	enum SACK_DIR
	{
		SACK_DIR_LEFT,
		SACK_DIR_RIGHT,
		SACK_DIR_NONE
	};


	//あたり判定
	CHit_Base	*m_hitCenter;						//中心
	CHit_Base	*m_hitLeft;						//左
	CHit_Base	*m_hitRight;						//右
	CHit_Base	*m_hitUp;							//上
	CHit_Base	*m_hitDown;						//下
	CHit_Base	*m_hitRightOut;					//右（ジャンプ用）
	CHit_Base	*m_hitLeftOut;					//左（ジャンプ用）
	CHit_Base	*m_hitUpOut;						//上（連結用）

	CSackBase	*m_child;				//ついている蹴鞠


	~CSackBase(void);							//デストラクタ

	virtual void Initialize(void);							//初期化関数
	virtual void Action(void);							//処理関数
	virtual void Input(CInput* input){};							//入力関数
	virtual void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)=0;							//描画関数
	virtual void PostAction(void);						//後処理関数

	virtual void MoveRight(void);						//右へ移動
	virtual void MoveLeft(void);						//左へ移動
	void Jump(void);							//ジャンプ
	void Pull(void);							//引っ張られる
	void Chain(void);							//連結する
	void Slide(void);							//床上にずべて減速する
	virtual void Dash(void);					//ダッシュ
	virtual void HitWall(void);					//壁と当たる
	virtual void LeaveWall(void);				//壁から離れる
	void CleanNumbers(void);					//ステージにスナップする

	void ResetPositionX(void);					//X位置の値をOldの値に戻す
	void ResetPositionY(void);					//Y位置の値をOldの値に戻す

	CSackBase* GetParent(void);					//親を戻す
	XMFLOAT3 GetImpulse(void);				//弾みの値を戻す関数
	SACK_DIR GetStringDir(void);				//紐の向きを返す関数
	SACK_DIR GetLookingDir(void);				//向いている向きを戻す
	SACK_DIR GetHookDir(void);					//フックの向きを戻す
	float GetRopePullForce(void);					//紐の引っ張る力
	float GetRopePullAngle(void);
	SackStateBase* GetState(void);					//状態を戻す
	XMFLOAT3 GetHookPos(void);

	void AddImpulse(float impulseX, float impulseY);	//弾みの値を増やす関数
	void SetImpulseX(float impulseX);				//X軸の弾みをセットする
	void SetImpulseY(float impulseX);				//Y軸の弾みをセットする
	void SetState(SackStateBase::SACK_STATE stateName);		//状態をセットする

protected:

	static int     m_noSack;

	static CModel* m_body;
	static CModel* m_hook;

	int            m_noId;
	char           m_nameId[256];


	//CRope *rope;
	SackStateBase* m_state;

	//位置
	XMFLOAT3		m_initPosition;		//初期位置
	XMFLOAT3		m_position;			//現在位置
	XMFLOAT3		m_oldPosition;		//前フレームの位置

	float			m_initAngle;		//初期向いている方向
	XMFLOAT3		m_orientation;		//向いている角度

	XMFLOAT3		m_impulse;			//現在の移動力
	XMFLOAT3		m_oldImpulse;			//前フレームの移動力

	SACK_DIR		m_stringDir;			//紐の向き
	SACK_DIR		m_looking;			//向いている方向
	SACK_DIR		m_hookDir;			//フックの向き
	CSackBase*      m_parent;			//つながっている蹴鞠

	CSackBase(float posX, float posY, GAMEOBJTYPE gObj);	//コンストラクタ
	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown(void);

	void CreateMesh(void);				//メッシュの生成関数
	void UpdateDisplacement(void);		//位置を更新する
	void UpdateHit(void);				//あたり判定の更新関数
	void ClearChain(void);

	virtual void RenderDebug(void);				//デバッグ表示関数
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************