//************************************************************************//
//	TextureClass.cpp
//	2016-11-09
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include "TextureClass.h"

//==============================================================================
//  �֐���        CTexture	
//  ����          CTexture�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CTexture::CTexture()
{
	m_targaData = 0;
	m_texture = 0;
	
	m_textureData.texture = 0;
	m_textureData.uRepeat = 1;
	m_textureData.vRepeat = 1;
}

//==============================================================================
//  �֐���        CTexture	
//  ����          CTexture�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CTexture& other			CTexture�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CTexture::CTexture(const CTexture& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CTexture	
//  ����          CTexture�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CTexture::~CTexture()
{
	//��
}

//==============================================================================
//  �֐���        Initialize
//  ����          CFontShader�̏����֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*         device           �f�o�C�X�ւ̃|�C���^
//          ID3D11DeviceContext*  deviceContext	   �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          char*                 filename         �e�N�X�`���ւ̃|�C���^
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CTexture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	result = LoadTarga(filename, height, width);
	if (!result)
	{
		return false;
	}

	//�e�N�X�`���̐ݒ�
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	//��̃e�N�X�`���쐬
	hResult = device->CreateTexture2D(&textureDesc, nullptr, &m_texture);
	if (FAILED(hResult))
	{
		return false;
	}

	rowPitch = (width * 4) * sizeof(unsigned char);

	deviceContext->UpdateSubresource(m_texture, 0, nullptr, m_targaData, rowPitch, 0);

	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureData.texture);
	if (FAILED(hResult))
	{
		return false;
	}

	deviceContext->GenerateMips(m_textureData.texture);

	delete[] m_targaData;
	m_targaData = 0;
	
	return true;

}

//==============================================================================
//  �֐���        Initialize
//  ����          CFontShader�̏����֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*         device           �f�o�C�X�ւ̃|�C���^
//          ID3D11DeviceContext*  deviceContext	   �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          char*                 filename         �e�N�X�`���ւ̃|�C���^
//          int                   uRepeat          �e�N�X�`����u���W�̌J��Ԃ�
//          int                   vRepeat          �e�N�X�`����V���W�̌J��Ԃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CTexture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, int uRepeat, int vRepeat)
{
	bool result;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	result = LoadTarga(filename, height, width);
	if (!result)
	{
		return false;
	}

	//�e�N�X�`���̐ݒ�
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	//��̃e�N�X�`���쐬
	hResult = device->CreateTexture2D(&textureDesc, nullptr, &m_texture);
	if (FAILED(hResult))
	{
		return false;
	}

	rowPitch = (width * 4) * sizeof(unsigned char);

	deviceContext->UpdateSubresource(m_texture, 0, nullptr, m_targaData, rowPitch, 0);

	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureData.texture);
	if (FAILED(hResult))
	{
		return false;
	}

	deviceContext->GenerateMips(m_textureData.texture);

	delete[] m_targaData;
	m_targaData = 0;

	return true;

}

//==============================================================================
//  �֐���        Shutdown
//  ����          �e�N�X�`���̉��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CTexture::Shutdown()
{
	if (m_textureData.texture)
	{
		m_textureData.texture->Release();
		m_textureData.texture = 0;
	}

	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	if (m_targaData)
	{
		delete[] m_targaData;
		m_targaData = 0;
	}

	return;
}

//==============================================================================
//  �֐���        GetTexture
//  ����          �e�N�X�`���̃|�C���^��߂��֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			ID3D11ShaderResourceView    texture              �e�N�X�`���ւ̃|�C���^
//==============================================================================
CTexture::TextureData CTexture::GetTextureData()
{
	return m_textureData;
}

//==============================================================================
//  �֐���        LoadTarga
//  ����          TGA�t�@�C����ǂݍ��ފ֐�
//------------------------------------------------------------------------------
//	����
//          char*                filename         �e�N�X�`���ւ̃|�C���^
//          int&                 height	          �e�N�X�`���̍���
//          int&                 width            �e�N�X�`���̕�
//	�߂�l
//			bool	             true �����@�@�@   false ���s
//==============================================================================
bool CTexture::LoadTarga(char* filename, int& height, int& width)
{
	int error, bpp, imageSize, index, i, j, k;
	FILE* filePtr;
	unsigned int count;
	TargaHeader targaFileHeader;
	unsigned char* targaImage;

	error = fopen_s(&filePtr, (char*)filename, "rb");
	if (error != 0)
	{
		return false;
	}

	count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	if (count != 1)
	{
		return false;	
	}
	
	height = (int)targaFileHeader.height;
	width = (int)targaFileHeader.width;
	bpp = (int)targaFileHeader.bpp;

	if (bpp != 32)
	{
		return false;
	}

	imageSize = width * height * 4;

	targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return false;
	}

	//TGA�摜�̃f�[�^��ǂݍ���
	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	//TGA�f�[�^�����z��̏�����
	m_targaData = new unsigned char[imageSize];
	if (!m_targaData)
	{
		return false;
	}

	index = 0;

	k = (width * height * 4) - (width * 4);

	//�f�[�^�̏��Ԃ𒼂�
	for (j = 0; j < height; j++) 
	{
		for (i = 0; i < width; i++)
		{
			m_targaData[index + 0] = targaImage[k + 2]; //��
			m_targaData[index + 1] = targaImage[k + 1]; //��
			m_targaData[index + 2] = targaImage[k + 0]; //��
			m_targaData[index + 3] = targaImage[k + 3]; //�A���t�@

			k += 4;
			index += 4;
		}

		k -= (width * 8);
	}

	//�|�C���^���
	delete[] targaImage;
	targaImage = 0;

	return true;
}

//==============================================================================
//  �֐���        SetRepeat
//  ����          �e�N�X�`����UV���s�[�g���Z�b�g����
//------------------------------------------------------------------------------
//	����
//          int                 m_uRepeat	         U���W�̌J��Ԃ�
//          int                 m_vRepeat            V���W�̌J��Ԃ�
//	�߂�l
//			bool	            true �����@�@�@   false ���s
//==============================================================================
void CTexture::SetUVRepeat(int uRepeat, int vRepeat)
{
	m_textureData.uRepeat = uRepeat;
	m_textureData.vRepeat = vRepeat;

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************
