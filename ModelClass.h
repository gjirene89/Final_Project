//************************************************************************//
//	ModelClass.h
//	2017-01-17
//	Irene Gersenowies
//************************************************************************//

#ifndef __MODEL_CLASS_H__
#define __MODEL_CLASS_H__

//=======================================================================//
//		インクルード
//=======================================================================//
# include <DirectXMath.h>
# include <d3d11.h>
# include <fstream>

using namespace DirectX;
using namespace std;

#include "TextureClass.h"

//=======================================================================//
//	クラス名		CModel
//=======================================================================//
class CModel
{
public:
	struct ColorVertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	CModel(void);
	CModel(const CModel& other) {};
	~CModel(void) {};

	bool Initialize(ID3D11Device* device, char* modelFilename);
	void Shutdown(void);

	void Render(ID3D11DeviceContext* deviceContext);// , XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);

	bool LoadColorMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename);
	bool LoadColorMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, int vRepeat, int uRepeat);
	bool LoadBumpMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* bumpMapFilename);
	bool LoadBumpMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* bumpMapFilename, int vRepeat, int uRepeat);
	bool LoadSpecMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* specMapFilename);
	bool LoadSpecMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* specMapFilename, int vRepeat, int uRepeat);

	//--------------
	//    取得関数
	//--------------

	CTexture::TextureData GetColorTexture(void);
	CTexture::TextureData GetBumpTexture(void);
	CTexture::TextureData GetSpecTexture(void);

	int GetVertexCount(void);
	int GetIndexCount(void);

	//ModelType* GetModelType(void) { return m_model; };

private:
	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers(void);
	void RenderBuffersIndex(ID3D11DeviceContext* deviceContext);
	void RenderBuffersIndex(ID3D11DeviceContext* deviceContext, ID3D11Buffer* vertexBuffer);

	void ReleaseTexture(void);

	bool LoadModel(char* filename);
	void ReleaseModel(void);


private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	int m_vertexCount;
	int m_indexCount;

	ModelType* m_model;

	CTexture* m_Texture;
	CTexture* m_BumpMap;
	CTexture* m_SpecMap;

};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************
