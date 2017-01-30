//************************************************************************//
//	SpecularShaderClass.h
//	2016-12-08
//	Irene Gersenowies
//************************************************************************//

#ifndef __SPECULAR_SHADER_CLASS_H_
#define __SPECULAR_SHADER_CLASS_H_

//=======================================================================//
//		インクルード
//=======================================================================//
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
using namespace DirectX;
using namespace std;

#include "TextureClass.h"

//=======================================================================//
//	クラス名		CSpecularShader
//=======================================================================//
class CSpecularShader
{
private: 
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float specularPower;
		XMFLOAT4 specularColor;
	};

public:
	CSpecularShader(void);
	CSpecularShader(const CSpecularShader& other);
	~CSpecularShader(void);

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown(void);
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, 
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, 
		CTexture::TextureData texture,
		XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor,
		XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader(void);
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* filename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, 
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, 
		CTexture::TextureData texture,
		XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor,
		XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;

	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_cameraBuffer;
	ID3D11Buffer* m_lightBuffer;
};

#endif
