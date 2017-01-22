//************************************************************************//
//	BumpMapShaderClass.h
//	2016-11-11
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include "BumpMapShaderClass.h"

//==============================================================================
//  �֐���        CBumpMapShader	
//  ����          CBumpMapShader�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
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
//  �֐���        CBumpMapShader	
//  ����          CBumpMapShader�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CBumpMapShader& other			CBumpMapShader�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CBumpMapShader::CBumpMapShader(const CBumpMapShader& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CBumpMapShader	
//  ����          CBumpMapShader�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CBumpMapShader::~CBumpMapShader()
{
	//��
}

//==============================================================================
//  �֐���        Initialize
//  ����          BumpMap�V�F�[�_�[�̏����֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*         device           �f�o�C�X�ւ̃|�C���^
//          HWND                  hwnd             �E�C���h�E �n���h��
//	�߂�l
//			bool	true �����@�@�@false ���s
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
//  �֐���		 Shutdown	
//  ����			 BumpMap�V�F�[�_�[�̉�����Ăяo���֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CBumpMapShader::Shutdown()
{
	ShutdownShader();

	return;
}

//==============================================================================
//  �֐���		 Render	
//  ����			 BumpMap�V�F�[�_�[�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                        indexCount           ���f���̃C���f�b�N�X�f�[�^
//          XMMATRIX                   worldMatrix          ���[���h�}�g���b�N�X
//          XMMATRIX                   viewMatrix           �r���[�}�g���b�N�X
//          XMMATRIX                   projectionMatrix     �v���W�F�N�V�����}�g���b�N�X
//          ID3D11ShaderResourceView*  colorTexture         �e�N�X�`��
//          ID3D11ShaderResourceView*  normalTexture        �@���e�N�X�`��
//          XMFLOAT3                   lightDirection       ��������
//          XMFLOAT4                   diffuseColor		    ���F
//	�߂�l
//			bool	true �����@�@�@false ���s
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
//  �֐���        InitializeShader
//  ����          BumpMap�V�F�[�_�[�̏�����
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*           device         �f�o�C�X�ւ̃|�C���^
//          HWND                    hwnd           �E�C���h�E�n���h��
//          WCHAR*                  vsFilename     ���_�V�F�[�_�[ �t�@�C�����ւ̃|�C���^
//          WCHAR*                  psFilename     �s�N�Z���V�F�[�_�[ �t�@�C�����ւ̃|�C���^
//	�߂�l
//			bool	                true �����@�@�@ false ���s
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

	//�|�C���^�̏�����
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//���_�V�F�[�_�[���R���p�C������
	result = D3DCompileFromFile(vsFilename, nullptr, nullptr, "BumpMapVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);

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
	result = D3DCompileFromFile(psFilename, nullptr, nullptr, "BumpMapPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
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
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	//�s�N�Z���V�F�[�_�[�𐶐�����
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_pixelShader);
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

	//���_�f�[�^�̃C���v�b�g���C�A�E�g�쐬
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	//�o�b�t�@�f�[�^���������
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

	//�e�N�X�`���T���v���[�̐ݒ�
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

	//�o�b�t�@�ւ̃|�C���^���擾
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	//���C�g�̃o�b�t�@�ݒ�
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	//�o�b�t�@�ւ̃|�C���^���擾
	result = device->CreateBuffer(&lightBufferDesc, nullptr, &m_lightBuffer);
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
//  �֐���        SetShaderParameters
//  ����          �V�F�[�_�[�p�����[�^��ݒ肷��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          ID3D11ShaderResourceView*   colorTexture         �e�N�X�`��
//          ID3D11ShaderResourceView*   normalTexture        �@���e�N�X�`��
//          XMFLOAT3                    lightDirection       ��������
//          XMFLOAT4                    diffuseColor         ���F
//	�߂�l
//			bool	                    true �����@�@�@       false ���s
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
	//  �}�g���b�N�X�f�[�^�𒸓_�o�b�t�@�ɃZ�b�g����
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
	//  ���̏����s�N�Z���o�b�t�@�ɃZ�b�g����
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

	//�e�N�X�`�����s�N�Z���V�F�[�_�[�Ƀ��[�h����
	deviceContext->PSSetShaderResources(0, 1, &colorTexture.texture);
	deviceContext->PSSetShaderResources(1, 1, &normalTexture.texture);


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
void CBumpMapShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}



