//************************************************************************//
//	TextureShaderClass.cpp
//	2016-11-09
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "TextureShaderClass.h"

//==============================================================================
//  関数名        CTextureShader	
//  説明          CTextureShaderクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CTextureShader::CTextureShader()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_UVRepeatBuffer = 0;
	m_samplerState = 0;
}

//==============================================================================
//  関数名        CTextureShader	
//  説明          CTextureShaderクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CTextureShader& other			CTextureShaderのインスタンス
//	戻り値
//          なし
//==============================================================================
CTextureShader::CTextureShader(const CTextureShader& other)
{
	//空
}

//==============================================================================
//  関数名        ～CTextureShader	
//  説明          CTextureShaderクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CTextureShader::~CTextureShader()
{
	//空
}

//==============================================================================
//  関数名        Initialize
//  説明          シェーダーの初期関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11Device*         device           デバイスへのポインタ
//          HWND                  hwnd             ウインドウ ハンドル
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CTextureShader::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeShader(device, hwnd, L"Resources/Shader/Texture.vs", L"Resources/Shader/Texture.ps");
	if (!result)
	{
		return false;
	}

	return true;
}

//==============================================================================
//  関数名		 Shutdown	
//  説明			 シェーダーの解放を呼び出す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CTextureShader::Shutdown()
{
	ShutdownShader();

	return;
}

//==============================================================================
//  関数名		 Render	
//  説明			 Colorシェーダーの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*       deviceContext		デバイスコンテキストへのポインタ
//          int                        indexCount           モデルのインデックスデータ
//          XMMATRIX                   worldMatrix          ワールドマトリックス
//          XMMATRIX                   viewMatrix           ビューマトリックス
//          XMMATRIX                   projectionMatrix     プロジェクションマトリックス
//          ID3D11ShaderResourceView*  texture              テクスチャ
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CTextureShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, CTexture::TextureData textureData)
{
	bool result;

	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, textureData);
	if (!result)
	{
		return false;
	}

	RenderShader(deviceContext, indexCount);

	return true;
}

//==============================================================================
//  関数名        InitializeShader
//  説明          シェーダーの初期化
//------------------------------------------------------------------------------
//	引数
//          ID3D11Device*           device         デバイスへのポインタ
//          HWND                    hwnd           ウインドウハンドル
//          WCHAR*                  vsFilename     頂点シェーダー ファイル名へのポインタ
//          WCHAR*                  psFilename     ピクセルシェーダー ファイル名へのポインタ
//	戻り値
//			bool	                true 成功　　　 false 失敗
//==============================================================================
bool CTextureShader::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC uvRepeatBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	//ポインタの初期化
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//頂点シェーダーをコンパイルする
	result = D3DCompileFromFile(vsFilename, nullptr, nullptr, "TextureVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			//エラーメッセージを出力する
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else
		{
			//ファイルが見つからないという報告を出す
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	//ピクセルシェーダーをコンパイルする
	result = D3DCompileFromFile(psFilename, nullptr, nullptr, "TexturePixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			//エラーメッセージを出力する
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else
		{
			//ファイルが見つからないという報告を出す
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}
		return false;
	}

	//頂点シェーダーを生成する
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	//ピクセルシェーダーを生成する
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	//頂点シェーダーのデータ設定
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "TEXCOORD";
	polygonLayout[2].SemanticIndex = 1;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 1;
	polygonLayout[2].AlignedByteOffset = 0;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[2].InstanceDataStepRate = 1;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//頂点データのインプットレイアウト作成
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	//バッファデータを解放する
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	//頂点シェーダーのバッファの設定
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	//バッファへのポインタを取得
	result = device->CreateBuffer(&matrixBufferDesc, nullptr, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//UV座標の繰り返しデータを頂点シェーダーのバッファの設定
	uvRepeatBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	uvRepeatBufferDesc.ByteWidth = sizeof(UVRepeatBufferType);
	uvRepeatBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	uvRepeatBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	uvRepeatBufferDesc.MiscFlags = 0;
	uvRepeatBufferDesc.StructureByteStride = 0;

	//バッファへのポインタを取得
	result = device->CreateBuffer(&uvRepeatBufferDesc, nullptr, &m_UVRepeatBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//テクスチャサンプラーの設定
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//バッファへのポインタを取得
	result = device->CreateSamplerState(&samplerDesc, &m_samplerState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//==============================================================================
//  関数名        ShutdownShader
//  説明          シェーダー解放関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CTextureShader::ShutdownShader()
{
	if (m_UVRepeatBuffer)
	{
		m_UVRepeatBuffer->Release();
		m_UVRepeatBuffer = 0;
	}

	if (m_samplerState)
	{
		m_samplerState->Release();
		m_samplerState = 0;
	}

	if(m_matrixBuffer)
	{ 
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
	
	return;
}

//==============================================================================
//  関数名        OutputShaderErrorMessage
//  説明          シェーダーのコンパイルエラーを出力する関数
//------------------------------------------------------------------------------
//	引数
//          ID3D10Blob*      errorMessage        エラーメッセージへのポインタ
//          HWND             hwnd                ウインドウハンドル
//          WCHAR*           shaderFilename      シェーダーファイル名へのポインタ
//	戻り値
//          なし
//==============================================================================
void CTextureShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long long bufferSize, i;
	ofstream fout;

	compileErrors = (char*)(errorMessage->GetBufferPointer());
	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}
	fout.close();

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

//==============================================================================
//  関数名        SetShaderParameters
//  説明          シェーダーパラメータを設定する関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*        deviceContext        デバイスコンテキストへのポインタ
//          XMMATRIX                    worldMatrix          ワールド マトリックス
//          XMMATRIX                    viewMatrix           ビュー マトリックス
//          XMMATRIX                    projectionMatrix     プロジェクション マトリックス
//          ID3D11ShaderResourceView*   texture              テクスチャ
//	戻り値
//			bool	                    true 成功　　　       false 失敗
//==============================================================================
bool CTextureShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, CTexture::TextureData textureData)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	UVRepeatBufferType* dataPtr2;
	unsigned int bufferNumber;

	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	//------------------------------------------
	//  マトリックスデータを頂点バッファにセットする
	//------------------------------------------

	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr = (MatrixBufferType*)mappedResource.pData;

	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	deviceContext->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	//------------------------------------------
	//  UV座標の繰り返しを頂点バッファにセットする
	//------------------------------------------
	result = deviceContext->Map(m_UVRepeatBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr2 = (UVRepeatBufferType*)mappedResource.pData;

	dataPtr2->uRepeat = textureData.uRepeat;
	dataPtr2->vRepeat = textureData.vRepeat;
	dataPtr2->padding = {0,0};

	deviceContext->Unmap(m_UVRepeatBuffer, 0);

	bufferNumber = 1;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_UVRepeatBuffer);

	//テクスチャをピクセルシェーダーにロードする
	deviceContext->PSSetShaderResources(0, 1, &textureData.texture);

	return true;
}

//==============================================================================
//  関数名        RenderShader
//  説明          シェーダーの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*       deviceContext        デバイスコンテキストへのポインタ
//          int                        indexCount           モデルのインデックスデータ
//	戻り値
//          なし
//==============================================================================
void CTextureShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	deviceContext->DrawIndexed(indexCount, 0, 0);
	
	return;
}



