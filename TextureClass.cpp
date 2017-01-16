//************************************************************************//
//	TextureClass.cpp
//	2016-11-09
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "TextureClass.h"

//==============================================================================
//  関数名        CTexture	
//  説明          CTextureクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
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
//  関数名        CTexture	
//  説明          CTextureクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CTexture& other			CTextureのインスタンス
//	戻り値
//          なし
//==============================================================================
CTexture::CTexture(const CTexture& other)
{
	//空
}

//==============================================================================
//  関数名        ～CTexture	
//  説明          CTextureクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CTexture::~CTexture()
{
	//空
}

//==============================================================================
//  関数名        Initialize
//  説明          CFontShaderの初期関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11Device*         device           デバイスへのポインタ
//          ID3D11DeviceContext*  deviceContext	   デバイスコンテキストへのポインタ
//          char*                 filename         テクスチャへのポインタ
//	戻り値
//			bool	true 成功　　　false 失敗
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

	//テクスチャの設定
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

	//空のテクスチャ作成
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
//  関数名        Initialize
//  説明          CFontShaderの初期関数
//------------------------------------------------------------------------------
//	引数
//          ID3D11Device*         device           デバイスへのポインタ
//          ID3D11DeviceContext*  deviceContext	   デバイスコンテキストへのポインタ
//          char*                 filename         テクスチャへのポインタ
//          int                   uRepeat          テクスチャのu座標の繰り返し
//          int                   vRepeat          テクスチャのV座標の繰り返し
//	戻り値
//			bool	true 成功　　　false 失敗
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

	//テクスチャの設定
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

	//空のテクスチャ作成
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
//  関数名        Shutdown
//  説明          テクスチャの解放
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
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
//  関数名        GetTexture
//  説明          テクスチャのポインタを戻す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			ID3D11ShaderResourceView    texture              テクスチャへのポインタ
//==============================================================================
CTexture::TextureData CTexture::GetTextureData()
{
	return m_textureData;
}

//==============================================================================
//  関数名        LoadTarga
//  説明          TGAファイルを読み込む関数
//------------------------------------------------------------------------------
//	引数
//          char*                filename         テクスチャへのポインタ
//          int&                 height	          テクスチャの高さ
//          int&                 width            テクスチャの幅
//	戻り値
//			bool	             true 成功　　　   false 失敗
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

	//TGA画像のデータを読み込む
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

	//TGAデータを持つ配列の初期化
	m_targaData = new unsigned char[imageSize];
	if (!m_targaData)
	{
		return false;
	}

	index = 0;

	k = (width * height * 4) - (width * 4);

	//データの順番を直す
	for (j = 0; j < height; j++) 
	{
		for (i = 0; i < width; i++)
		{
			m_targaData[index + 0] = targaImage[k + 2]; //赤
			m_targaData[index + 1] = targaImage[k + 1]; //緑
			m_targaData[index + 2] = targaImage[k + 0]; //青
			m_targaData[index + 3] = targaImage[k + 3]; //アルファ

			k += 4;
			index += 4;
		}

		k -= (width * 8);
	}

	//ポインタ解放
	delete[] targaImage;
	targaImage = 0;

	return true;
}

//==============================================================================
//  関数名        SetRepeat
//  説明          テクスチャのUVリピートをセットする
//------------------------------------------------------------------------------
//	引数
//          int                 m_uRepeat	         U座標の繰り返し
//          int                 m_vRepeat            V座標の繰り返し
//	戻り値
//			bool	            true 成功　　　   false 失敗
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
