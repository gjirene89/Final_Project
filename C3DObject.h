//*****************************************************************************
//!	@file	C3DGameObject.h
//!	@brief	3Dゲームオブジェクトクラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_C3DOBJECT__
#define __GM31_C3DOBJECT__

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
#include	"GameObjectBase.h"

//=============================================================================
//!	@class	C3DObject
//!	@brief	3Dゲームオブジェクトのベース
//=============================================================================
class C3DObject : public CGameObjectBase
{
protected:
	D3DXMATRIX			matrix;					//変換行列
	D3DXVECTOR3			WorldPos;				//ワールドの位置
	D3DXVECTOR3			LocPos;					//ローカルの位置
	LPD3DXMESH			mesh;					// メッシュインターフェイス
	D3DMATERIAL9		*material;				//マテリアル

public:
	C3DObject(GAMEOBJTYPE gameObjType);			//コンストラクタ
	~C3DObject(void);							//デストラクタ

	void RenderAxis(void);						//３軸の描画関数
	void RenderWithAxis(void);					//３軸付きの描画関数
	//void RenderWithBS(void);					//バウンディングスフィア付きの描画

	inline virtual void Input(void);			//入力関数
	inline virtual void Init(void);				//初期化関数
	inline virtual void Action(void);			//処理関数
	inline virtual void Render(void);			//描画関数
	inline virtual void PostAction(void);		//後処理関数
	
	void InitMaterial(void);							//マテリアルの初期化関数

	void SetMatrix(D3DXMATRIX newMatrix);		//マトリックスの情報をセットする関数
	void SetPosition(D3DXVECTOR3 position);		//位置を設定する関数
	void SetMesh(LPD3DXMESH mesh);
	void SetSize(D3DXVECTOR3 size);

	//マテリアル
	void SetDiffuse(D3DCOLORVALUE diffuse);				//拡散色の設定関数
	void SetAmbient(D3DCOLORVALUE ambient);				//環境色の設定関数
	void SetSpecular(D3DCOLORVALUE specular);			//反射色の設定関数
	void SetEmissive(D3DCOLORVALUE emissive);			//発行色の設定関数

	

	LPD3DXMESH GetMesh(void);					//メッシュを渡す関数
	D3DXVECTOR3 GetRotX(void);					//オブジェクトのX軸回転を戻す関数
	D3DXVECTOR3 GetRotY(void);					//オブジェクトのY軸回転を戻す関数
	D3DXVECTOR3 GetRotZ(void);					//オブジェクトのZ軸回転を戻す関数
	D3DXVECTOR3 GetLocPos(void);				//オブジェクトのローカル座標を戻す関数
	D3DXVECTOR3 GetWorldPos(void);				//オブジェクトのワールド座標を戻す関数
	D3DXMATRIX  GetMatrix(void);				//オブジェクトの変換行列を戻す関数

};

#endif
//******************************************************************************
//	End of file.
//******************************************************************************