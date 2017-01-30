//************************************************************************//
//	SpecularShaderClass.cpp
//	2016-11-09
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "SpecularShaderClass.h"

//==============================================================================
//  関数名        CSpecularShader	
//  説明          CSpecularShaderクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CSpecularShader::CSpecularShader()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_sampleState = 0;
	m_matrixBuffer = 0;

	m_cameraBuffer = 0;
	m_lightBuffer = 0;
}

//==============================================================================
//  関数名        CSpecularShader	
//  説明          CSpecularShaderクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CSpecularShader& other			CSpecularShaderのインスタンス
//	戻り値
//          なし
//==============================================================================
CSpecularShader::CSpecularShader(const CSpecularShader& other)
{
	//空
}

//==============================================================================
//  関数名        ～CSpecularShader	
//  説明          CSpecularShaderクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CSpecularShader::~CSpecularShader()
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
bool CSpecularShader::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeShader(device, hwnd, L"Resources/Shader/Specular.vs", L"Resources/Shader/Specular.ps");
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
void CSpecularShader::Shutdown()
{
	ShutdownShader();

	return;
}

//==============================================================================
//  関数名		 Render	
//  説明			 シェーダーの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*       deviceContext		デバイスコンテキストへのポインタ
//          int                        indexCount           モデルのインデックスデータ
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
bool CSpecularShader::Render(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, 
	CTexture::TextureData textureData, 
	XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor,
	XMFLOAT3 cameraPosition,
	XMFLOAT4 specularColor, float specularPower)
{
	bool result;

	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, textureData, lightDirection, ambientColor, diffuseColor, cameraPosition, specularColor, specularPower);
	if(!result)
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
bool CSpecularShader::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC cameraBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc;

	//ポインタの初期化
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//頂点シェーダーをコンパイルする
	result = D3DCompileFromFile(vsFilename, nullptr, nullptr, "SpecularVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
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
	result = D3DCompileFromFile(psFilename, nullptr, nullptr, "SpecularPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
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

	//Create the texture sampler state
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

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

	//カメラバッファ設定
	cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.StructureByteStride = 0;

	//バッファへのポインタを取得
	result = device->CreateBuffer(&cameraBufferDesc, NULL, &m_cameraBuffer);
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
void CSpecularShader::ShutdownShader()
{
	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = 0;
	}

	if (m_cameraBuffer)
	{
		m_cameraBuffer->Release();
		m_cameraBuffer = 0;
	}

	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
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
void CSpecularShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout; 
	
	//Get a pointer to the error message text buffer
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	//Get the lenght of the message
	bufferSize = errorMessage->GetBufferSize();

	//Open a file to write the error message to
	fout.open("shader-error.txt");

	//Write out the error Message
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	//Close the file
	fout.close();

	//Release the error message
	errorMessage->Release();
	errorMessage = 0;

	//Pop a message up on the screen to notify the user to check the text file for compile errors
	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message.", shaderFilename, MB_OK);
	
	return;
}

//==============================================================================
//  関数名		 Render	
//  説明			 シェーダーの描画関数
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
bool CSpecularShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, 
	CTexture::TextureData textureData, 
	XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, 
	XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType* dataPtr;
	LightBufferType* dataPtr2;
	CameraBufferType* dataPtr3;

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
	//  カメラ位置を頂点にセットする
	//------------------------------------------

	result = deviceContext->Map(m_cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr3 = (CameraBufferType*)mappedResource.pData;

	dataPtr3->cameraPosition = cameraPosition;
	dataPtr3->padding = 0.0f;

	deviceContext->Unmap(m_cameraBuffer, 0);

	bufferNumber = 1;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_cameraBuffer);


	//------------------------------------------
	//  光の情報をピクセルバッファにセットする
	//------------------------------------------

	result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr2 = (LightBufferType*)mappedResource.pData;

	dataPtr2->ambientColor = ambientColor;
	dataPtr2->diffuseColor = diffuseColor;
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->specularColor = specularColor;
	dataPtr2->specularPower = specularPower;

	deviceContext->Unmap(m_lightBuffer, 0);

	bufferNumber = 0;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	//------------------------------------------
	//　　テクスチャをピクセルシェーダーにロードする
	//------------------------------------------

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
void CSpecularShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}