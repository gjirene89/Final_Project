//************************************************************************//
//	ModelClass.cpp
//	2017-01-17
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
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
//  �֐���		 Initialize	
//  ����			 ���f���̏����֐�
//------------------------------------------------------------------------------
//	����
//			ID3D11Device*          device               �f�o�C�X�ւ̃|�C���^
//          ID3D11DeviceContext*   deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          char*                  modelFilename        ���f���t�@�C���ւ̃|�C���^
//	�߂�l
//			bool	               true �����@�@       �@false ���s
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
//  �֐���        Shutdown
//  ����          ���f�����������֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CModel::Shutdown()
{
	//ReleaseTexture();
	ShutdownBuffers();
	ReleaseModel();

	return;
}

//==============================================================================
//  �֐���        Render
//  ����          ���f���̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//	�߂�l
//          �Ȃ�
//==============================================================================
void CModel::Render(ID3D11DeviceContext* deviceContext)//, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{

	RenderBuffersIndex(deviceContext);
	return;
}

//==============================================================================
//  �֐���        Render
//  ����          ���f���̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          ID3D11Buffer*              vertexBuffer		    ���_�o�b�t�@
//	�߂�l
//          �Ȃ�
//==============================================================================
void CModel::Render(ID3D11DeviceContext* deviceContext, ID3D11Buffer* vertexBuffer)
{
	RenderBuffersIndex(deviceContext, vertexBuffer);

	return;
}

//==============================================================================
//  �֐���         GetVertexCount
//  ����	          ���_����߂��֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			int	           m_vertexCount        ���_��
//==============================================================================
int CModel::GetVertexCount()
{
	return m_vertexCount;
}

//==============================================================================
//  �֐���         GetIndexCount
//  ����	          �C���f�b�N�X����߂��֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			int	           m_indexCount        �C���f�b�N�X��
//==============================================================================
int CModel::GetIndexCount()
{
	return m_indexCount;
}

//==============================================================================
//  �֐���        InitializeBuffers
//  ����          �o�b�t�@�̏������֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*           device           �f�o�C�X�ւ̃|�C���^
//	�߂�l
//			bool	               true �����@�@       �@false ���s
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

	//�ÓI�Ȓ��_�o�b�t�@��ݒ肷��
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


	//�ÓI�ȃC���f�b�N�X�o�b�t�@��ݒ肷��
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

	//�f�[�^���
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

//==============================================================================
//  �֐���        ShutdownBuffers
//  ����          �o�b�t�@�̉���֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
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
//  �֐���        RenderBuffersIndex
//  ����          �o�b�t�@�f�[�^��`�悷��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*    deviceContext    �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//	�߂�l
//          �Ȃ�
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
//  �֐���        LoadModel
//  ����          ���f���f�[�^�̃��[�h�֐�
//------------------------------------------------------------------------------
//	����
//          char*                 filename     �@�@���f���t�@�C���ւ̃|�C���^
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CModel::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;

	//���f���t�@�C����ǂݍ���
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

	//���f���f�[�^�����o��
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
//  �֐���        ReleaseModel
//  ����          ���f���f�[�^���������֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
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