//************************************************************************//
//	ModelClass.cpp
//	2017-01-17
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "ModelClass.h"
//#include "ShaderManagerClass.h"

CModel::CModel()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	m_model = 0;

}
//==============================================================================
//  関数名		 Initialize	
//  説明			 モデルの初期関数
//------------------------------------------------------------------------------
//	引数
//			ID3D11Device*          device               デバイスへのポインタ
//          ID3D11DeviceContext*   deviceContext		デバイスコンテキストへのポインタ
//          char*                  modelFilename        モデルファイルへのポインタ
//	戻り値
//			bool	               true 成功　　       　false 失敗
//==============================================================================
bool CModel::Initialize(ID3D11Device* device, char* modelFilename)
{
	bool result;

	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

//==============================================================================
//  関数名        Shutdown
//  説明          モデルを解放する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CModel::Shutdown()
{
	//ReleaseTexture();
	ShutdownBuffers();
	ReleaseModel();

	return;
}

//==============================================================================
//  関数名        Render
//  説明          モデルの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*       deviceContext		デバイスコンテキストへのポインタ
//	戻り値
//          なし
//==============================================================================
void CModel::Render(ID3D11DeviceContext* deviceContext)//, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{

	RenderBuffersIndex(deviceContext);
	return;
}

//==============================================================================
//  関数名        Render
//  説明          モデルの描画関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*       deviceContext		デバイスコンテキストへのポインタ
//          ID3D11Buffer*              vertexBuffer		    頂点バッファ
//	戻り値
//          なし
//==============================================================================
void CModel::Render(ID3D11DeviceContext* deviceContext, ID3D11Buffer* vertexBuffer)
{
	RenderBuffersIndex(deviceContext, vertexBuffer);

	return;
}

//==============================================================================
//  関数名         GetVertexCount
//  説明	          頂点数を戻す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			int	           m_vertexCount        頂点数
//==============================================================================
int CModel::GetVertexCount()
{
	return m_vertexCount;
}

//==============================================================================
//  関数名         GetIndexCount
//  説明	          インデックス数を戻す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			int	           m_indexCount        インデックス数
//==============================================================================
int CModel::GetIndexCount()
{
	return m_indexCount;
}

//==============================================================================
//  関数名        InitializeBuffers
//  説明          バッファの初期化関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11Device*           device           デバイスへのポインタ
//	戻り値
//			bool	               true 成功　　       　false 失敗
//==============================================================================
bool CModel::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	for (i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}

	//静的な頂点バッファを設定する
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)* m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}


	//静的なインデックスバッファを設定する
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//データ解放
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

//==============================================================================
//  関数名        ShutdownBuffers
//  説明          バッファの解放関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CModel::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

//==============================================================================
//  関数名        RenderBuffersIndex
//  説明          バッファデータを描画する関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11DeviceContext*    deviceContext    デバイスコンテキストへのポインタ
//	戻り値
//          なし
//==============================================================================
void CModel::RenderBuffersIndex(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	return;
}

void CModel::RenderBuffersIndex(ID3D11DeviceContext* deviceContext, ID3D11Buffer* vertexBuffer)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	return;
}


//==============================================================================
//  関数名        LoadModel
//  説明          モデルデータのロード関数
//------------------------------------------------------------------------------
//	引数
//          char*                 filename     　　モデルファイルへのポインタ
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CModel::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;

	//モデルファイルを読み込む
	fin.open(filename);

	if (fin.fail())
	{
		return false;
	}

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	fin >> m_vertexCount;

	m_indexCount = m_vertexCount;

	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);

	}

	fin.get(input);
	fin.get(input);

	//モデルデータを取り出す
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	fin.close();

	return true;
}

//==============================================================================
//  関数名        ReleaseModel
//  説明          モデルデータを解放する関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CModel::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************