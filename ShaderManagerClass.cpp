//************************************************************************//
//	ShaderManagerClass.h
//	2016-12-05
//	Irene Gersenowies
//************************************************************************//

#include "ShaderManagerClass.h"

//==============================================================================
//  関数名        CShaderManager	
//  説明          CShaderManagerクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CShaderManager::CShaderManager()
{
	m_ColorShader = 0;
	m_TextureShader = 0;

	/*
	m_BumpMapShader = 0;
	m_ClothShader = 0;
	m_SpecularShader = 0;
	m_ShadowShader = 0;
	m_DepthShader = 0;
	m_VerticalBlurShader = 0;
	m_HorizontalBlurShader = 0;
	m_SoftShadowShader = 0;
	*/
}

//==============================================================================
//  関数名        CShaderManager	
//  説明          CShaderManagerクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CShaderManager& other			CShaderManagerのインスタンス
//	戻り値
//          なし
//==============================================================================
CShaderManager::CShaderManager(const CShaderManager& other)
{
	//空
}

//==============================================================================
//  関数名        ～CShaderManager	
//  説明          CShaderManagerクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CShaderManager::~CShaderManager()
{
	//空
}

//==============================================================================
//  関数名        Initialize
//  説明          ShaderManagerのシェーダー初期関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11Device*         device           デバイスへのポインタ
//          HWND                  hwnd			   ウインドウハンドル
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;
	

	//----------------------------
	//　　Colorシェーダー生成
	//----------------------------
	m_ColorShader = new CColorShader;
	if (!m_ColorShader)
	{
		return false;
	}

	result = m_ColorShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	//----------------------------
	//　　Textureシェーダー生成
	//----------------------------
	m_TextureShader = new CTextureShader;
	if (!m_TextureShader)
	{
		return false;
	}
	
	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}
/*
	//----------------------------
	//　　BumpMapシェーダー生成
	//----------------------------
	m_BumpMapShader = new CBumpMapShader;
	if (!m_BumpMapShader)
	{
		return false;
	}

	result = m_BumpMapShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not inititalize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//　　Clothシェーダー生成
	//----------------------------
	m_ClothShader = new CClothShader;
	if (!m_ClothShader)
	{
		return false;
	}

	result = m_ClothShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not inititalize the cloth shader object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//　　Clothシェーダー生成
	//----------------------------
	m_SpecularShader = new CSpecularShader;
	if (!m_SpecularShader)
	{
		return false;
	}

	result = m_SpecularShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular shader object.", L"Error", MB_OK);
		return false;
	}
	
	//----------------------------
	//　　Shadowシェーダー生成
	//----------------------------
	m_ShadowShader = new CShadowShader;
	if (!m_ShadowShader)
	{
		return false;
	}

	result = m_ShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//　　DephtMapシェーダー生成
	//----------------------------
	m_DepthShader = new CDepthShader;
	if (!m_DepthShader)
	{
		return false;
	}

	result = m_DepthShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;

	}

	//----------------------------
	//　　VerticalBlurシェーダー生成
	//----------------------------
	m_VerticalBlurShader = new CVerticalBlurShader;
	if (!m_VerticalBlurShader)
	{
		return false;
	}

	result = m_VerticalBlurShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur shader object.", L"Error", MB_OK);
		return false;

	}

	//----------------------------
	//　　HorizontalBlurシェーダー生成
	//----------------------------
	m_HorizontalBlurShader = new CHorizontalBlurShader;
	if (!m_HorizontalBlurShader)
	{
		return false;
	}

	result = m_HorizontalBlurShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Horizontal blur shader object.", L"Error", MB_OK);
		return false;

	}

	//----------------------------
	//　　SoftShadowシェーダー生成
	//----------------------------
	m_SoftShadowShader = new CSoftShadowShader;
	if (!m_SoftShadowShader)
	{
		return false;
	}

	result = m_SoftShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Horizontal blur shader object.", L"Error", MB_OK);
		return false;

	}
	*/
	return true;
}

//==============================================================================
//  関数名        Shutdown
//  説明          シェーダーの解放を呼び出す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CShaderManager::Shutdown()
{
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	/*
	if (m_SoftShadowShader)
	{
		m_SoftShadowShader->Shutdown();
		delete m_SoftShadowShader;
		m_SoftShadowShader = 0;
	}

	if (m_VerticalBlurShader)
	{
		m_VerticalBlurShader->Shutdown();
		delete m_VerticalBlurShader;
		m_VerticalBlurShader = 0;
	}

	if (m_HorizontalBlurShader)
	{
		m_HorizontalBlurShader->Shutdown();
		delete m_HorizontalBlurShader;
		m_HorizontalBlurShader = 0;
	}

	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	if (m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}

	if (m_ClothShader)
	{
		m_ClothShader->Shutdown();
		delete m_ClothShader;
		m_ClothShader = 0;
	}
	
	if (m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}
	
	if (m_SpecularShader)
	{
		m_SpecularShader->Shutdown();
		delete m_SpecularShader;
		m_SpecularShader = 0;
	}

	*/
	return;
}


//==============================================================================
//  関数名		 RenderColorShader	
//  説明			 色の描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          int                         indexCount           インデックス カウント
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//          XMFLOAT4                    vertexColor          頂点色
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT4 vertexColor)
{
	bool result;
	
	result = m_ColorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, vertexColor);
	if (!result)
	{
		return false;
	}
	
	return true;
}

//==============================================================================
//  関数名		 RenderTextureShader	
//  説明			 テクスチャの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          int                         indexCount           インデックス カウント
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//          ID3D11ShaderResourceView*   texture              テクスチャ
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData textureData)
{
	bool result;
	
	result = m_TextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureData);
	if (!result)
	{
		return false;
	}
	
	return true;
}
/*
//==============================================================================
//  関数名		 RenderBumpMapShader	
//  説明			 バンプマップの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          int                         indexCount           インデックス カウント
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//          ID3D11ShaderResourceView*   colorTexture         テクスチャ
//          ID3D11ShaderResourceView*   normalTexture        法線テクスチャ
//          XMFLOAT3                    lightDirection       光線向き
//          XMFLOAT4                    diffuseColor         光色
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData colorTexture, CTexture::TextureData normalTexture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
	bool result;
	
	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuseColor);
	if (!result)
	{
		return false;
	}
	
	return true;
}


//==============================================================================
//  関数名		 RenderSpecularShader	
//  説明			 鏡面の描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*       deviceContext		デバイスコンテキストへのポインタ
//          XMMATRIX                   worldMatrix          ワールドマトリックス
//          XMMATRIX                   viewMatrix           ビューマトリックス
//          XMMATRIX                   projectionMatrix     プロジェクションマトリックス
//          TextureData                textureData         テクスチャ
//          XMFLOAT3                   lightDirection       光の向き
//          XMFLOAT4                   ambientColor         環境色
//          XMFLOAT4                   diffuseColor         拡散色
//          XMFLOAT3                   cameraPosition       カメラ位置
//          XMFLOAT4                   specularColor        鏡面色
//          float                      specularPower        鏡面力
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderSpecularShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData textureData,
	XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor,
	XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower)
{
	bool result;
	
	result = m_SpecularShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureData, lightDirection, ambientColor, diffuseColor, cameraPosition, specularColor, specularPower);
	if (!result)
	{
		return false;
	}
	
	return true;
}

//==============================================================================
//  関数名        RenderClothShader	
//  説明	          Clothシェーダーの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          int                         indexCount           インデックス カウント
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//          ID3D11ShaderResourceView*   colorTexture         テクスチャ
//          ID3D11ShaderResourceView*   normalTexture        法線テクスチャ
//          XMFLOAT3                    lightDirection       光線向き
//          XMFLOAT4                    diffuseColor         光色
//          XMFLOAT4                    ambientColor         環境色
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderClothShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData colorTexture, CTexture::TextureData normalTexture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
	XMFLOAT3 cameraPosition)
{
	bool result;

	//Clothシェーダーで描画する
	result = m_ClothShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuseColor,ambientColor, cameraPosition);
	if (!result)
	{
		return false;
	}
}

//==============================================================================
//  関数名		 RenderShadowShader	
//  説明			 シャドーの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*       deviceContext		デバイスコンテキストへのポインタ
//          XMMATRIX                   worldMatrix          ワールドマトリックス
//          XMMATRIX                   viewMatrix           ビューマトリックス
//          XMMATRIX                   projectionMatrix     プロジェクションマトリックス
//          TextureData                textureData         テクスチャ
//          XMFLOAT3                   lightDirection       光の向き
//          XMFLOAT4                   ambientColor         環境色
//          XMFLOAT4                   diffuseColor         拡散色
//          XMFLOAT3                   cameraPosition       カメラ位置
//          XMFLOAT4                   specularColor        鏡面色
//          float                      specularPower        鏡面力
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderShadowShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	XMMATRIX lightViewMatrix, XMMATRIX lightProjectionMatrix,
	CTexture::TextureData colorTexture, ID3D11ShaderResourceView* depthMapTexture,
	XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	bool result;

	result = m_ShadowShader->Render(deviceContext, indexCount, 
		worldMatrix, viewMatrix, projectionMatrix, 
		lightViewMatrix, lightProjectionMatrix,
		colorTexture, depthMapTexture, 
		lightDirection, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	return true;
}


//==============================================================================
//  関数名		 RenderDepthShader	
//  説明			 色の描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          int                         indexCount           インデックス カウント
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderDepthShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	bool result;

	result = m_DepthShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

//==============================================================================
//  関数名		 RenderVerticalBlurShader	
//  説明			 横ぼかし
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          int                         indexCount           インデックス カウント
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//          ID3D11ShaderResourceView*   texture              テクスチャ
//          float                       screenHeight		 テクスチャサイズ
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderVerticalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float screenHeight)
{
	bool result;

	result = m_VerticalBlurShader->Render(deviceContext, indexCount, 
		worldMatrix, viewMatrix, projectionMatrix, texture, screenHeight);
	if (!result)
	{
		return false;
	}

	return true;

}

//==============================================================================
//  関数名		 RenderHorizontalBlurShader	
//  説明			縦ぼかし
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          int                         indexCount           インデックス カウント
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//          ID3D11ShaderResourceView*   texture              テクスチャ
//          float                       screenHeight		 テクスチャサイズ
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderHorizontalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float screenWidth)
{
	bool result;

	result = m_HorizontalBlurShader->Render(deviceContext, indexCount,
		worldMatrix, viewMatrix, projectionMatrix, texture, screenWidth);
	if (!result)
	{
		return false;
	}

	return true;

}


//==============================================================================
//  関数名		 RenderHorizontalBlurShader	
//  説明			縦ぼかし
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          int                         indexCount           インデックス カウント
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//          ID3D11ShaderResourceView*   texture              テクスチャ
//          float                       screenHeight		 テクスチャサイズ
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CShaderManager::RenderSoftShadowShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData colorTexture, ID3D11ShaderResourceView* shadowTexture,
	XMFLOAT3 lightPosition, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	bool result;

	result = m_SoftShadowShader->Render(deviceContext, indexCount,
		worldMatrix, viewMatrix, projectionMatrix, colorTexture, shadowTexture,
		lightPosition, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	return true;
}
*/

//******************************************************************************
//	End of file.
//******************************************************************************