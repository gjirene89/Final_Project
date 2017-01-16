//************************************************************************//
//	TextureClass.h
//	2016-11-09
//	Irene Gersenowies
//************************************************************************//

#ifndef __TEXTURE_CLASS_H_
#define __TEXTURE_CLASS_H_

//=======================================================================//
//		インクルード
//=======================================================================//
#include <d3d11.h>
#include <stdio.h>

//=======================================================================//
//	クラス名		CTexture
//=======================================================================//
class CTexture
{
public:
	struct TextureData
	{
		ID3D11ShaderResourceView* texture;
		int uRepeat;
		int vRepeat;
	};
private:
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	CTexture(void);
	CTexture(const CTexture& other);
	~CTexture(void);

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename);
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, int uRepeat, int vRepeat);
	void Shutdown(void);

	TextureData GetTextureData();

	void SetUVRepeat(int uRepeat, int vRepeat);

private:
	bool LoadTarga(char* textureFilename, int& height, int& width);

private:
	unsigned char*    m_targaData;
	ID3D11Texture2D*  m_texture;
	TextureData       m_textureData;

};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************
