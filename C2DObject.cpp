//*****************************************************************************
//!	@file	C2DObject.cpp
//!	@brief	2Dゲームオブジェクトクラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
#include	"C2DObject.h"
#include	"CDirectxGraphics.h"

//==============================================================================
//!	@fn		C2DObject
//!	@brief	2Dオブジェクトのコンストラクタ
//!	@param	float    PosX		X軸の位置
//!	@param	float    PosY		Y軸の位置
//!	@param	float    Width		幅
//!	@param	float    Height		高さ
//!	@param	D3DCOLOR Color		色
//!	@retval	なし
//!	@note	
//==============================================================================
C2DObject::C2DObject(float PosX, float PosY, float Width, float Height, D3DCOLOR color_) : CGameObjectBase(GAMEOBJTYPE::GOBJ_UI)
{
	//初期化
	center.x = PosX;
	center.y = PosY;
	dimension.x = Width;
	dimension.y = Height;
	color = color_;

	//UVの初期化
	animInfo.f_uvLeft		= 0.0f;
	animInfo.f_uvRight		= 1.0f;
	animInfo.f_uvTop		= 0.0f;
	animInfo.f_uvBottom		= 1.0f;
}

//==============================================================================
//!	@fn		~C2DObject
//!	@brief	2Dオブジェクトのデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
C2DObject::~C2DObject(void)
{
	//今は空
}

//==============================================================================
//!	@fn		Init
//!	@brief	2Dオブジェクトの初期化
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void C2DObject::Init(void)
{
	//頂点情報を求める
	CalcVertex();
}

//==============================================================================
//!	@fn		Input
//!	@brief	2Dゲームオブジェクの入力関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void C2DObject::Input(void)
{
	//今は空
}


//==============================================================================
//!	@fn		Render
//!	@brief	2Dオブジェクトの描画
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void C2DObject::Render(void)
{
	//隠している状態だったら、描画しない
	if (isHidden)
		return;

	//テクスチャをつける
	CDirectXGraphics::GetDXDevice()->SetTexture(0, texture);

	CDirectXGraphics::GetDXDevice()->SetFVF(FVF_TLVERTEX2D);
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//D3DCULL_CW,D3DCULL_CCW,D3DCULL_NONE determina que lado no va a ser renderizado

	//ライトを消す
	CDirectXGraphics::GetDXDevice()->LightEnable(0, FALSE);
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//描画命令(頂点データの転送+描画)
	CDirectXGraphics::GetDXDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(TLVERTEX2D));//調整　D3DPT_TRIANGLEFAN,1, の１のところを２に変える
	
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//ライトを点ける
	CDirectXGraphics::GetDXDevice()->LightEnable(0, TRUE);
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==============================================================================
//!	@fn		Action
//!	@brief	2Dオブジェクトの処理関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void C2DObject::Action(void)
{
	//今は空
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	2Dオブジェクトの後処理関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void C2DObject::PostAction(void)
{
	//今は空
}

//==============================================================================
//!	@fn		CalcVertex
//!	@brief	頂点とUV情報を求める
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void C2DObject::CalcVertex(void)
{
	//頂点情報を求める
	vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;					//rhwを1.0にする  
	vertex[0].diffuse = vertex[1].diffuse = vertex[2].diffuse = vertex[3].diffuse = color;	//頂点カラー	

	vertex[0].x = vertex[1].x = center.x - dimension.x / 2.0f;
	vertex[2].x = vertex[3].x = center.x + dimension.x / 2.0f;

	vertex[1].y = vertex[2].y = center.y - dimension.y / 2.0f;
	vertex[0].y = vertex[3].y = center.y + dimension.y / 2.0f;

	vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;

	//UVを設定する
	vertex[0].tu = vertex[1].tu = animInfo.f_uvLeft;
	vertex[2].tu = vertex[3].tu = animInfo.f_uvRight;

	vertex[0].tv = vertex[3].tv = animInfo.f_uvBottom;
	vertex[1].tv = vertex[2].tv = animInfo.f_uvTop;
}


//==============================================================================
//!	@fn		SetSize
//!	@brief	サイズをセットする
//!	@param	fWidth		幅
//! @param  fHeight		高さ
//!	@retval	なし
//==============================================================================
void C2DObject::SetSize(float fWidth, float fHeight)
{
	//xのサイズ
	dimension.x = fWidth;

	//yのサイズ
	dimension.y = fHeight;
}

//==============================================================================
//!	@fn		SetColor
//!	@brief	色をセットする関数
//!	@param	板ポリの色
//!	@retval	なし
//==============================================================================
void C2DObject::SetColor(D3DCOLOR newColor)
{
	//色をセットする
	color = newColor;
}

//==============================================================================
//!	@fn		SetCenter
//!	@brief	中心点をセット
//!	@param	fPosX	X座標
//!	@param	fPosY	Y座標
//!	@param	fPosZ	Z座標
//!	@retval	なし
//==============================================================================
void C2DObject::SetCenter(float fPosX, float fPosY)
{
	//位置をセットする
	center.x = fPosX;
	center.y = fPosY;
}
//******************************************************************************
//	End of file.
//******************************************************************************
