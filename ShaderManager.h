//************************************************************************//
//	ShaderManagerClass.h
//	2016-12-05
//	Irene Gersenowies
//************************************************************************//

#ifndef __SHADER_MANAGER_CLASS_H__
#define __SHADER_MANAGER_CLASS_H__

//=======================================================================//
//		インクルード
//=======================================================================//
#include "D3DClass.h"
#include "TextureClass.h"

#include "ColorShaderClass.h"
#include "TextureShaderClass.h"
#include "BumpMapShaderClass.h"
#include "SpecularShaderClass.h"

/*	
#include "ClothShaderClass.h"
#include "ShadowShaderClass.h"
#include "DepthShaderClass.h"
#include "HorizontalBlurShaderClass.h"
#include "VerticalBlurShaderClass.h"
#include "SoftShadowShaderClass.h"
*/
//=======================================================================//
//	クラス名		CShaderManager
//=======================================================================//
class CShaderManager
{
public:
	static CShaderManager& getInstance();
	~CShaderManager(void);

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown(void);

	bool RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		XMFLOAT4 vertexColor);
	
	bool RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, 
		CTexture::TextureData textureData);
	
	bool RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		CTexture::TextureData colorTexture, CTexture::TextureData normalTexture,
		XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor);
	
	bool RenderSpecularShader(ID3D11DeviceContext* deviceContext, int indexCount, 
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, 
		CTexture::TextureData textureData,
		XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor,
		XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower);

/*
	bool RenderClothShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		CTexture::TextureData colorTexture, CTexture::TextureData normalTexture,
		XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
		XMFLOAT3 cameraPosition);

	bool RenderShadowShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		XMMATRIX lightViewMatrix, XMMATRIX lightProjectionMatrix,
		CTexture::TextureData colorTexture, ID3D11ShaderResourceView* depthMapTexture,
		XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor);

	bool RenderDepthShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);

	bool RenderVerticalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		ID3D11ShaderResourceView* texture, float screenHeight);

	bool RenderHorizontalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		ID3D11ShaderResourceView* texture, float screenWidth);

	bool RenderSoftShadowShader(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		CTexture::TextureData colorTexture, ID3D11ShaderResourceView* shadowTexture,
		XMFLOAT3 lightPosition, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor);
		*/

private:
	CShaderManager(void);
	CShaderManager(const CShaderManager& other);
	CShaderManager& operator=(const CShaderManager& other) {};

	CColorShader* m_ColorShader;	
	CTextureShader* m_TextureShader;
	CBumpMapShader* m_BumpMapShader;
	CSpecularShader* m_SpecularShader;

	/*
	CClothShader* m_ClothShader;
	CShadowShader* m_ShadowShader;
	CSoftShadowShader* m_SoftShadowShader;
	CDepthShader* m_DepthShader;
	CVerticalBlurShader* m_VerticalBlurShader;
	CHorizontalBlurShader* m_HorizontalBlurShader;
	*/
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************