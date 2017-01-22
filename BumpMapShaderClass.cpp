//************************************************************************//
//	BumpMapShaderClass.h
//	2016-11-11
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "BumpMapShaderClass.h"

//==============================================================================
//  関数名        CBumpMapShader	
//  説明          CBumpMapShaderクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CBumpMapShader::CBumpMapShader()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_lightBuffer = 0;
	m_sampleState = 0;
}

//==============================================================================
//  関数名        CBumpMapShader	
//  説明          CBumpMapShaderクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CBumpMapShader& other			CBumpMapShaderのインスタンス
//	戻り値
//          なし
//==============================================================================
CBumpMapShader::CBumpMapShader(const CBumpMapShader& other)
{
	//空
}

//==============================================================================
//  関数名        ～CBumpMapShader	
//  説明          CBumpMapShaderクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CBumpMapShader::~CBumpMapShader()
{
	//空
}

//==============================================================================
//  関数名        Initialize
//  説明          BumpMapシェーダーの初期関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11Device*         device           デバイスへのポインタ
//          HWND                  hwnd             ウインドウ ハンドル
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CBumpMapShader::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeShader(device, hwnd, L"Resources/Shader/BumpMap.vs", L"Resources/Shader/BumpMap.ps");
	if (!result)
	{
		return false;
	}

	return true;
}

//==============================================================================
//  関数名		 Shutdown	
//  説明			 BumpMapシェーダーの解放を呼び出す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CBumpMapShader::Shutdown()
{
	ShutdownShader();

	return;
}

//==============================================================================
//  関数名		 Render	
//  説明			 BumpMapシェーダーの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*       deviceContext		デバイスコンテキストへのポインタ
//          int                        indexCount           モデルのインデックスデータ
//          XMMATRIX                   worldMatrix          ワールドマトリックス
//          XMMATRIX                   viewMatrix           ビューマトリックス
//          XMMATRIX                   projectionMatrix     プロジェクションマトリックス
//          ID3D11ShaderResourceView*  colorTexture         テクスチャ
//          ID3D11ShaderResourceView*  normalTexture        法線テクスチャ
//          XMFLOAT3                   lightDirection       光線向き
//          XMFLOAT4                   diffuseColor		    光色
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CBumpMapShader::Render(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData colorTexture, CTexture::TextureData normalTexture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
	bool result;

	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuseColor);
	if (!result)
	{
		return false;
	}

	RenderShader(deviceContext, indexCount);

	return true;
}

//==============================================================================
//  関数名        InitializeShader
//  説明          BumpMapシェーダーの初期化
//------------------------------------------------------------------------------
//	引数
//          ID3D11Device*           device         デバイスへのポインタ
//          HWND                    hwnd           ウインドウハンドル
//          WCHAR*                  vsFilename     頂点シェーダー ファイル名へのポインタ
//          WCHAR*                  psFilename     ピクセルシェーダー ファイル名へのポインタ
//	戻り値
//			bool	                true 成功　　　 false 失敗
//==============================================================================
bool CBumpMapShader::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[5];
	unsigned int numElements;

	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	//ポインタの初期化
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//頂点シェーダーをコンパイルする
	result = D3DCompileFromFile(vsFilename, nullptr, nullptr, "BumpMapVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);

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
	result = D3DCompileFromFile(psFilename, nullptr, nullptr, "BumpMapPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
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

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	polygonLayout[3].SemanticName = "TANGENT";
	polygonLayout[3].SemanticIndex = 0;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[3].InputSlot = 0;
	polygonLayout[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[3].InstanceDataStepRate = 0;

	polygonLayout[4].SemanticName = "BINORMAL";
	polygonLayout[4].SemanticIndex = 0;
	polygonLayout[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[4].InputSlot = 0;
	polygonLayout[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[4].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[4].InstanceDataStepRate = 0;

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

	//バッファーへのポインタを取得
	result = device->CreateBuffer(&matrixBufferDesc, nullptr, &m_matrixBuffer);
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
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	//ライトのバッファ設定
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	//バッファへのポインタを取得
	result = device->CreateBuffer(&lightBufferDesc, nullptr, &m_lightBuffer);
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
void CBumpMapShader::ShutdownShader()
{
	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = 0;
	}

	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	if (m_matrixBuffer)
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
void CBumpMapShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
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
//          ID3D11ShaderResourceView*   colorTexture         テクスチャ
//          ID3D11ShaderResourceView*   normalTexture        法線テクスチャ
//          XMFLOAT3                    lightDirection       光線向き
//          XMFLOAT4                    diffuseColor         光色
//	戻り値
//			bool	                    true 成功　　　       false 失敗
//==============================================================================
bool CBumpMapShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData colorTexture, CTexture::TextureData normalTexture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;
	LightBufferType* dataPtr2;

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
	//  光の情報をピクセルバッファにセットする
	//------------------------------------------

	result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr2 = (LightBufferType*)mappedResource.pData;
	dataPtr2->diffuseColor = diffuseColor;
	dataPtr2->lightDirection = lightDirection;

	deviceContext->Unmap(m_lightBuffer, 0);
	bufferNumber = 0;
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	//テクスチャをピクセルシェーダーにロードする
	deviceContext->PSSetShaderResources(0, 1, &colorTexture.texture);
	deviceContext->PSSetShaderResources(1, 1, &normalTexture.texture);


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
void CBumpMapShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}



