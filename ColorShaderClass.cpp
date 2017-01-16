//************************************************************************//
//	ColorShaderClass.cpp
//	2016-11-08
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include "ColorShaderClass.h"

//==============================================================================
//  �֐���        CColorShader	
//  ����          CColorShader�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CColorShader::CColorShader()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
}

//==============================================================================
//  �֐���        CColorShader	
//  ����          CColorShader�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CColorShader& other			CColorShader�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CColorShader::CColorShader(const CColorShader& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CColorShader	
//  ����          CColorShader�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CColorShader::~CColorShader()
{
	//��
}

//==============================================================================
//  �֐���        Initialize
//  ����          Color�V�F�[�_�[�̏����֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*         device           �f�o�C�X�ւ̃|�C���^
//          HWND                  hwnd             �E�C���h�E �n���h��
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CColorShader::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeShader(device, hwnd, L"../Final_Project/Resources/Shader/Color.vs", L"../Final_Project/Resources/Shader/Color.ps");
	if (!result)
	{
		return false;
	}

	return true;
}

//==============================================================================
//  �֐���		 Shutdown	
//  ����			 Color�V�F�[�_�[���������֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CColorShader::Shutdown()
{
	ShutdownShader();

	return;
}

//==============================================================================
//  �֐���		 Render	
//  ����			 Color�V�F�[�_�[�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                        indexCount           ���f���̃C���f�b�N�X�f�[�^
//          XMMATRIX                   worldMatrix          ���[���h�}�g���b�N�X
//          XMMATRIX                   viewMatrix           �r���[�}�g���b�N�X
//          XMMATRIX                   projectionMatrix     �v���W�F�N�V�����}�g���b�N�X
//          XMFLOAT4                   vertexColor          ���_�F
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CColorShader::Render(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	XMFLOAT4 vertexColor)
{
	bool result;

	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, vertexColor);
	if (!result)
	{
		return false;
	}

	RenderShader(deviceContext, indexCount);

	return true;
}

//==============================================================================
//  �֐���        InitializeShader
//  ����          �V�F�[�_�[�̏�����
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*           device         �f�o�C�X�ւ̃|�C���^
//          HWND                    hwnd           �E�C���h�E�n���h��
//          WCHAR*                  vsFilename     ���_�V�F�[�_�[ �t�@�C�����ւ̃|�C���^
//          WCHAR*                  psFilename     �s�N�Z���V�F�[�_�[ �t�@�C�����ւ̃|�C���^
//	�߂�l
//			bool	                true �����@�@�@ false ���s
//==============================================================================
bool CColorShader::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC colorBufferDesc;

	//�|�C���^�̏�����
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//���_�V�F�[�_�[���R���p�C������
	result = D3DCompileFromFile(vsFilename, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			//�G���[���b�Z�[�W���o�͂���
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else
		{
			//�t�@�C����������Ȃ��Ƃ����񍐂��o��
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	//�s�N�Z���V�F�[�_�[���R���p�C������
	result = D3DCompileFromFile(psFilename, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			//�G���[���b�Z�[�W���o�͂���
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else
		{
			//�t�@�C����������Ȃ��Ƃ����񍐂��o��
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	//���_�V�F�[�_�[�𐶐�����
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	//�s�N�Z���V�F�[�_�[�𐶐�����
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	//���_�V�F�[�_�[�̃f�[�^�ݒ�
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//���_�f�[�^�̃C���v�b�g���C�A�E�g�쐬
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	//�o�b�t�@�[�f�[�^���������
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	//���_�V�F�[�_�[�̃o�b�t�@�̐ݒ�
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	//�o�b�t�@�[�ւ̃|�C���^���擾
	result = device->CreateBuffer(&matrixBufferDesc, nullptr, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//���_�V�F�[�_�[�̃o�b�t�@�̐ݒ�
	colorBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	colorBufferDesc.ByteWidth = sizeof(ColorBufferType);
	colorBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	colorBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	colorBufferDesc.MiscFlags = 0;
	colorBufferDesc.StructureByteStride = 0;

	//�o�b�t�@�[�ւ̃|�C���^���擾
	result = device->CreateBuffer(&colorBufferDesc, nullptr, &m_colorBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//==============================================================================
//  �֐���        ShutdownShader
//  ����          �V�F�[�_�[����֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CColorShader::ShutdownShader()
{
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
//  �֐���        OutputShaderErrorMessage
//  ����          �V�F�[�_�[�̃R���p�C���G���[���o�͂���֐�
//------------------------------------------------------------------------------
//	����
//          ID3D10Blob*      errorMessage        �G���[���b�Z�[�W�ւ̃|�C���^
//          HWND             hwnd                �E�C���h�E�n���h��
//          WCHAR*           shaderFilename      �V�F�[�_�[�t�@�C�����ւ̃|�C���^
//	�߂�l
//          �Ȃ�
//==============================================================================
void CColorShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
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
//  �֐���        SetShaderParameters
//  ����          �V�F�[�_�[�p�����[�^��ݒ肷��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          XMFLOAT4                    vertexColor          ���_�F
//	�߂�l
//			bool	                    true �����@�@�@       false ���s
//==============================================================================
bool CColorShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	XMFLOAT4 vertexColor)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	ColorBufferType* dataPtr2;
	unsigned int bufferNumber;

	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	//�}�g���b�N�X�f�[�^�𒸓_�o�b�t�@�ɃZ�b�g����
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

	//�F�����s�N�Z���o�b�t�@�ɃZ�b�g����
	result = deviceContext->Map(m_colorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr2 = (ColorBufferType*)mappedResource.pData;

	dataPtr2->color = vertexColor;

	deviceContext->Unmap(m_colorBuffer, 0);

	bufferNumber = 0;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_colorBuffer);

	return true;
}

//==============================================================================
//  �֐���        RenderShader
//  ����          �V�F�[�_�[�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                        indexCount           ���f���̃C���f�b�N�X�f�[�^
//	�߂�l
//          �Ȃ�
//==============================================================================
void CColorShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************