//*****************************************************************************
//!	@file	C3DGameObject.h
//!	@brief	3Dゲームオブジェクトクラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
#include	"C3DObject.h"
#include	"CDirectxGraphics.h"
#include	"mathutil.h"
#include	"Debug.h"

//==============================================================================
//!	@fn		C3DObject
//!	@brief	3Dゲームオブジェクトベースのコンストラクタ
//!	@param	3Dゲームオブジェクトの種類
//!	@retval	なし
//==============================================================================
C3DObject::C3DObject(GAMEOBJTYPE gameObjType) : CGameObjectBase(gameObjType)
{
	//変換行列の初期化
	D3DXMatrixIdentity(&matrix);
	texture = nullptr;
	mesh = nullptr;
	material = new D3DMATERIAL9;				//マテリアルの初期化
	
}

//==============================================================================
//!	@fn		～C3DObject
//!	@brief	3Dゲームオブジェクトベースのデストラクタ
//!	@param	なし
//!	@retval	なし
//==============================================================================
C3DObject::~C3DObject(void)
{	
	// マテリアルオブジェクトの解放
	if (material != nullptr)
	{	
		delete[] material;
		material = nullptr;
	}

	// メッシュ解放
	if (mesh != nullptr)
	{		
		mesh->Release();
		mesh = nullptr;
	}

	//テクスチャ解放
	if (texture != nullptr)
	{
		texture->Release();
		texture = nullptr;
	}
}

//==============================================================================
//!	@fn		Init
//!	@brief	3Dゲームオブジェクの初期化関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void C3DObject::Init(void)
{
	//今は空
}

//==============================================================================
//!	@fn		Input
//!	@brief	3Dゲームオブジェクの入力関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void C3DObject::Input(void)
{
	//今は空
}

//==============================================================================
//!	@fn		Action
//!	@brief	3Dゲームオブジェクの処理関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void C3DObject::Action(void)
{
	//今は空
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	3Dゲームオブジェクの後処理関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
void C3DObject::PostAction(void)
{
	//今は空
}

//==============================================================================
//!	@fn		Render
//!	@brief	3Dモデルを描画する
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void C3DObject::Render(void)
{
	if (mesh == nullptr || isHidden == true)
		return;

	CDirectXGraphics::GetDXDevice()->SetMaterial(material);
	CDirectXGraphics::GetDXDevice()->SetTexture(0, texture);
	CDirectXGraphics::GetDXDevice()->SetTransform(D3DTS_WORLD, &matrix);
	mesh->DrawSubset(0);

}

//==============================================================================
//!	@fn		RenderAxis
//!	@brief	3軸を描画する
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void C3DObject::RenderAxis(void)
{
	struct VERTEXDATA{
		float		x, y, z;
		D3DCOLOR	color;
	};

	// ３軸の頂点データ
	struct	VERTEXDATA	linevertices[6] = {
		-400, 0, 0, D3DCOLOR_XRGB(255, 0, 0),	// Ｘ軸始点 赤
		400, 0, 0, D3DCOLOR_XRGB(255, 0, 0),	// Ｘ軸終点 赤
		0, -400, 0, D3DCOLOR_XRGB(0, 255, 0),	// Ｙ軸始点 緑
		0, 400, 0, D3DCOLOR_XRGB(0, 255, 0),	// Ｙ軸終点 緑
		0, 0, -400, D3DCOLOR_XRGB(0, 0, 255),	// Ｚ軸始点 青
		0, 0, 400, D3DCOLOR_XRGB(0, 0, 255)		// Ｚ軸終点 青
	};

	CDirectXGraphics::GetDXDevice()->SetTexture(0,nullptr);
	CDirectXGraphics::GetDXDevice()->SetFVF(FVF_TLVERTEX3D);	// 頂点フォーマットをセット
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_LIGHTING, false);	//   光源計算オフ（光源計算を切るとDIFFUSE色がそのままでる）

	CDirectXGraphics::GetDXDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 3, &linevertices[0], sizeof(VERTEXDATA));	// ３軸を描画
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_LIGHTING, true);	//   光源計算ON
}

//==============================================================================
//!	@fn		RenderWithAxis
//!	@brief	Xファイル描画(3軸を描画する)
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void C3DObject::RenderWithAxis(void)
{
	//モデルの描画
	C3DObject::Render();
	//3軸の描画
	RenderAxis();
}

//==============================================================================
//!	@fn		GetMesh
//!	@brief	3Dゲームオブジェクのメッシュを戻す関数
//!	@param	なし
//!	@retval	LPD3DXMESH		オブジェクトのメッシュ
//==============================================================================
LPD3DXMESH C3DObject::GetMesh(void)
{
	return mesh;
}

void C3DObject::SetMesh(LPD3DXMESH mesh_)
{
	mesh = mesh_;
}

void C3DObject::SetSize(D3DXVECTOR3 size)
{
	SetSizeMatrix(matrix, size);
}

//==============================================================================
//!	@fn		GetRotX
//!	@brief	オブジェクトのX軸回転を戻す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetRotX(void)
{
	//変換行列からX軸回転の情報を戻す
	return{ matrix._11, matrix._12, matrix._13 };
}

//==============================================================================
//!	@fn		GetRotY
//!	@brief	オブジェクトのZ軸回転を戻す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetRotY(void)
{
	//変換行列からY軸回転の情報を戻す
	return{ matrix._21, matrix._22, matrix._23 };
}

//==============================================================================
//!	@fn		GetRotZ
//!	@brief	オブジェクトのZ軸回転を戻す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetRotZ(void)
{
	//変換行列からZ軸回転の情報を戻す
	return{ matrix._31, matrix._32, matrix._33 };
}

//==============================================================================
//!	@fn		GetLocPos
//!	@brief	オブジェクトのローラル座標を戻す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetLocPos(void)
{
	//変換行列からローカル座標の情報を戻す
	//return{ matrix._41, matrix._42, matrix._43 };
	return LocPos;
}

//==============================================================================
//!	@fn		GetWorldPos
//!	@brief	オブジェクトのワールド座標を戻す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetWorldPos(void)
{
	//ワールド座標を戻す
	return{ matrix._41, matrix._42, matrix._43 };
}

//==============================================================================
//!	@fn		GetMatrix
//!	@brief	オブジェクトの変換行列を戻す
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
D3DXMATRIX C3DObject::GetMatrix(void)
{
	//変換行列を戻す
	return matrix;
}

//==============================================================================
//!	@fn		SetMatrix
//!	@brief	マトリックスの情報のセット関数
//!	@param　D3DXMATRIX　matrix
//!	@retval	なし
//==============================================================================
void C3DObject::SetMatrix(D3DXMATRIX matrix_)
{
	matrix = matrix_;
}

//==============================================================================
//!	@fn		SetPosition
//!	@brief　オブジェクトの位置を設定する
//!	@param　D3DXVECTOR3 position
//!	@retval	なし
//==============================================================================
void C3DObject::SetPosition(D3DXVECTOR3 position)
{
	matrix._41 = position.x;
	matrix._42 = position.y;
	matrix._43 = position.z;
}

//==============================================================================
//!	@fn		InitMaterial
//!	@brief	マテリアルをデフォルト色にする
//!	@param　なし
//!	@retval	なし
//==============================================================================
void C3DObject::InitMaterial(void)
{
	if (material == nullptr)		material = new D3DMATERIAL9;				//マテリアルの初期化

	//マテリアルをデフォルト値にする
	material->Diffuse.r = 1.0f;
	material->Diffuse.g = 1.0f;
	material->Diffuse.b = 1.0f;
	material->Diffuse.a = 1.0f;

	material->Ambient.r = 0.0f;
	material->Ambient.g = 0.0f;
	material->Ambient.b = 0.0f;
	material->Ambient.a = 0.0f;

	material->Specular.r = 1.0f;
	material->Specular.g = 1.0f;
	material->Specular.b = 1.0f;
	material->Specular.a = 1.0f;

	material->Emissive.r = 0.0f;
	material->Emissive.g = 0.0f;
	material->Emissive.b = 0.0f;
	material->Emissive.a = 1.0f;
}

//==============================================================================
//!	@fn		SetDiffuse
//!	@brief	マテリアルを拡散色を設定する
//!	@param  D3DCOLORVALUE	color		拡散色
//!	@retval	なし
//==============================================================================
void C3DObject::SetDiffuse(D3DCOLORVALUE color)
{
	//拡散色を設定する
	material->Diffuse = color;
}

//==============================================================================
//!	@fn		SetAmbient
//!	@brief	マテリアルを拡散色を設定する
//!	@param  D3DCOLORVALUE	color		拡散色
//!	@retval	なし
//==============================================================================
void C3DObject::SetAmbient(D3DCOLORVALUE color)
{
	//環境色を設定する
	material->Ambient = color;
}

//==============================================================================
//!	@fn		SetSpecular
//!	@brief	マテリアルを拡散色を設定する
//!	@param  D3DCOLORVALUE	color		反射色
//!	@retval	なし
//==============================================================================
void C3DObject::SetSpecular(D3DCOLORVALUE color)
{
	//反射色を設定する
	material->Specular = color;
}

//==============================================================================
//!	@fn		SetEmissive
//!	@brief	マテリアルを拡散色を設定する
//!	@param  D3DCOLORVALUE	color		発光色
//!	@retval	なし
//==============================================================================
void C3DObject::SetEmissive(D3DCOLORVALUE color)
{
	//発行色を設定する
	material->Emissive = color;
}


//******************************************************************************
//	End of file.
//******************************************************************************