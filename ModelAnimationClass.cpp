# include "ModelAnimationClass.h"

CModelAnimation::CModelAnimation(void)
{

}

CModelAnimation::CModelAnimation(const CModelAnimation& other)
{

}

CModelAnimation::~CModelAnimation(void)
{

}

bool CModelAnimation::Initialize(ID3D11Device* device, CModel* startModel)
{
	bool result;

	m_startModel = startModel->GetModelType();
	m_vertexCnt = startModel->GetVertexCount();
	m_currTime = 0;
	m_endTime = 1;

	m_currModel = new CModel::ModelType[m_vertexCnt];
	if (!m_currModel)
	{
		return false;
	}

	result = InitializeBuffer(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void CModelAnimation::Shutdown(void)
{
	ShutdownBuffer();
}

void CModelAnimation::InterpolateModels()
{

	if (m_currTime >= m_endTime)
		return;

	float rate;

	rate = (float)m_currTime / (float)m_endTime;

	for (int i = 0; i < m_vertexCnt; i++)
	{
		m_currModel[i].x = m_startModel[i].x * (1 - rate) + m_targetModel[i].x * rate;
		m_currModel[i].y = m_startModel[i].y * (1 - rate) + m_targetModel[i].y * rate;
		m_currModel[i].z = m_startModel[i].z * (1 - rate) + m_targetModel[i].z * rate;

		m_currModel[i].nx = m_startModel[i].nx * (1 - rate) + m_targetModel[i].nx * rate;
		m_currModel[i].ny = m_startModel[i].ny * (1 - rate) + m_targetModel[i].ny * rate;
		m_currModel[i].nz = m_startModel[i].nz * (1 - rate) + m_targetModel[i].nz * rate;

		m_currModel[i].tu = m_startModel[i].tu * (1 - rate) + m_targetModel[i].tu * rate;
		m_currModel[i].tv = m_startModel[i].tv * (1 - rate) + m_targetModel[i].tv * rate;
	}
	
	m_currTime++;
}

void CModelAnimation::UpdateBuffer(ID3D11DeviceContext* deviceContext)
{
	int i;
	int modelVertexNo;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	CModel::VertexType* interpolVertex;

	deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	interpolVertex = (CModel::VertexType*)mappedResource.pData;

	for (i = 0; i < m_vertexCnt; i++)
	{
		interpolVertex[i].position.x = m_currModel[i].x;
		interpolVertex[i].position.y = m_currModel[i].y;
		interpolVertex[i].position.z = m_currModel[i].z;

		interpolVertex[i].texture.x = m_currModel[i].tu;
		interpolVertex[i].texture.y = m_currModel[i].tv;

		interpolVertex[i].normal.x = m_currModel[i].nx;
		interpolVertex[i].normal.y = m_currModel[i].ny;
		interpolVertex[i].normal.z = m_currModel[i].nz;
	}

	deviceContext->Unmap(m_vertexBuffer, 0);

}

ID3D11Buffer* CModelAnimation::GetVertexBuffer(ID3D11DeviceContext* deviceContext)
{
	UpdateBuffer(deviceContext);

	return m_vertexBuffer;
}

bool CModelAnimation::InitializeBuffer(ID3D11Device* device)
{
	HRESULT result;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	//静的な頂点バッファを設定する
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(CModel::VertexType) * m_vertexCnt;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&vertexBufferDesc, nullptr, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;

}

void CModelAnimation::ShutdownBuffer()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

}

void CModelAnimation::SetTarget(CModel* targetModel, int endTime)
{
	if (targetModel->GetVertexCount() != m_vertexCnt)
		return;

	m_startModel = m_targetModel;
	m_currTime = 0;

	m_targetModel = targetModel->GetModelType();
	m_endTime = endTime;

}

void CModelAnimation::SetCurrent(CModel* currModel)
{
	m_startModel = m_targetModel = currModel->GetModelType();
	m_currTime = m_endTime;
}