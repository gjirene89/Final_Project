//************************************************************************//
//	ColorShaderClass.h
//	2016-11-08
//	2016-12-04 revisited
//	Irene Gersenowies
//************************************************************************//

#ifndef __COLOR_SHADER_CLASS_H_
#define __COLOR_SHADER_CLASS_H_

//=======================================================================//
//		インクルード
//=======================================================================//
# include <d3d11.h>
# include <d3dcompiler.h>
# include <DirectXMath.h>
# include <fstream>
using namespace DirectX;
using namespace std;

//=======================================================================//
//	クラス名		CColorShader
//=======================================================================//
class CColorShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct ColorBufferType
	{
		XMFLOAT4 color;
	};

public:
	CColorShader(void);
	CColorShader(const CColorShader& other);
	~CColorShader(void);

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown(void);
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT4 vertexColor);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader(void);
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT4 vertexColor);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_colorBuffer;
};

#endif // ! __COLOR_SHADER_CLASS_H_

//******************************************************************************
//	End of file.
//******************************************************************************