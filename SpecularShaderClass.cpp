//************************************************************************//
//	SpecularShaderClass.cpp
//	2016-11-09
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include "SpecularShaderClass.h"

//==============================================================================
//  �֐���        CSpecularShader	
//  ����          CSpecularShader�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
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
//  �֐���        CSpecularShader	
//  ����          CSpecularShader�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CSpecularShader& other			CSpecularShader�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CSpecularShader::CSpecularShader(const CSpecularShader& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CSpecularShader	
//  ����          CSpecularShader�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CSpecularShader::~CSpecularShader()
{
	//��
}

//==============================================================================
//  �֐���        Initialize
//  ����          �V�F�[�_�[�̏����֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*         device           �f�o�C�X�ւ̃|�C���^
//          HWND                  hwnd             �E�C���h�E �n���h��
//	�߂�l
//			bool	true �����@�@�@false ���s
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
//  �֐���		 Shutdown	
//  ����			 �V�F�[�_�[�̉�����Ăяo���֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CSpecularShader::Shutdown()
{
	ShutdownShader();

	return;
}

//==============================================================================
//  �֐���		 Render	
//  ����			 �V�F�[�_�[�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                        indexCount           ���f���̃C���f�b�N�X�f�[�^
//          XMMATRIX                   worldMatrix          ���[���h�}�g���b�N�X
//          XMMATRIX                   viewMatrix           �r���[�}�g���b�N�X
//          XMMATRIX                   projectionMatrix     �v���W�F�N�V�����}�g���b�N�X
//          TextureData                textureData         �e�N�X�`��
//          XMFLOAT3                   lightDirection       ���̌���
//          XMFLOAT4                   ambientColor         ���F
//          XMFLOAT4                   diffuseColor         �g�U�F
//          XMFLOAT3                   cameraPosition       �J�����ʒu
//          XMFLOAT4                   specularColor        ���ʐF
//          float                      specularPower        ���ʗ�
//	�߂�l
//			bool	true �����@�@�@false ���s
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

	//�|�C���^�̏�����
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//���_�V�F�[�_�[���R���p�C������
	result = D3DCompileFromFile(vsFilename, nullptr, nullptr, "SpecularVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
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
	result = D3DCompileFromFile(psFilename, nullptr, nullptr, "SpecularPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
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

	//Create the texture sampler state
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	//���_�V�F�[�_�[�̃o�b�t�@�̐ݒ�
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	//�o�b�t�@�ւ̃|�C���^���擾
	result = device->CreateBuffer(&matrixBufferDesc, nullptr, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//�J�����o�b�t�@�ݒ�
	cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.StructureByteStride = 0;

	//�o�b�t�@�ւ̃|�C���^���擾
	result = device->CreateBuffer(&cameraBufferDesc, NULL, &m_cameraBuffer);
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
//  �֐���		 Render	
//  ����			 �V�F�[�_�[�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          XMMATRIX                   worldMatrix          ���[���h�}�g���b�N�X
//          XMMATRIX                   viewMatrix           �r���[�}�g���b�N�X
//          XMMATRIX                   projectionMatrix     �v���W�F�N�V�����}�g���b�N�X
//          TextureData                textureData         �e�N�X�`��
//          XMFLOAT3                   lightDirection       ���̌���
//          XMFLOAT4                   ambientColor         ���F
//          XMFLOAT4                   diffuseColor         �g�U�F
//          XMFLOAT3                   cameraPosition       �J�����ʒu
//          XMFLOAT4                   specularColor        ���ʐF
//          float                      specularPower        ���ʗ�
//	�߂�l
//			bool	true �����@�@�@false ���s
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
	//  �J�����ʒu�𒸓_�ɃZ�b�g����
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
	//  ���̏����s�N�Z���o�b�t�@�ɃZ�b�g����
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
	//�@�@�e�N�X�`�����s�N�Z���V�F�[�_�[�Ƀ��[�h����
	//------------------------------------------

	deviceContext->PSSetShaderResources(0, 1, &textureData.texture);

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
void CSpecularShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}