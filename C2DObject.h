//*****************************************************************************
//!	@file	C2DObject.h
//!	@brief	2Dゲームオブジェクトクラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

#ifndef __GM31_2DOBJECT__
#define __GM31_2DOBJECT__

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
#include "GameObjectBase.h"
#include "AnimationSupport.h"
#include "CDirectxGraphics.h"

//=============================================================================
//!	@class	C2DObject
//!	@brief	2Dゲームオブジェクトのベース
//=============================================================================
class C2DObject : public CGameObjectBase
{
protected:
	TLVERTEX2D	vertex[4];		//四角形
	DWORD		color;			//色
	POINT		center;			//位置
	POINT		dimension;		//大きさ
	POINT		angle;			//角度
	ANIMEUV		animInfo;		//アニメ情報

public:
	C2DObject(float PosX, float PosY, float Width, float Height, D3DCOLOR color);				//コンストラクタ
	~C2DObject();				//デストラクタ

	void Input(void);
	void Init(void);			//初期化関数
	void Action(void);			//処理関数
	void Render(void);			//描画関数
	void PostAction(void);		//後処理関数

	void CalcVertex(void);		//頂点の情報を計算する関数

	void SetSize(float fWidth, float fHeight);		//大きさをセットする関数
	void SetColor(D3DCOLOR color);					//色をセットする関数
	void SetCenter(float fPosX, float fPosY);		//位置をセットする関数


};


#endif