//*****************************************************************************
//	PlaneClass.cpp
//	2017-01-30
//	Irene Gersenowies
//******************************************************************************

//==============================================================================
//		インクルード
//==============================================================================
# include "PlaneClass.h"
# include "ShaderManager.h"
# include "MathUtility.h"


//==============================================================================
//!	@fn		CPLane
//!	@brief	板ポリのコンストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CPlane::CPlane(float sizeX, float sizeY) : CGameObjectBase(GOBJ_BLOCK)
{
	//メッシュの作成
	m_model = nullptr;

	m_colorTexture = nullptr;
	m_bumpTexture = nullptr;

	//サイズ
	m_sizeX = sizeX;
	m_sizeY = sizeY;
}


//==============================================================================
//!	@fn		~CPlane
//!	@brief	板ポリのデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CPlane::~CPlane(void)
{
	//今は空
}

bool CPlane::InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;

	//****************//
	// 　モデル		  //
	//****************//

	m_model = new CModel;
	if (!m_model)
	{
		return false;
	}

	result = m_model->Initialize(device, "Resources/Model/Primitives/square.txt");
	if (!result)
	{
		return false;
	}

	return true;
}

bool CPlane::LoadColorTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, int repeatU, int repeatV)
{
	bool result;

	m_colorTexture = new CTexture();
	if (!m_colorTexture)
	{
		return false;
	}

	result = m_colorTexture->Initialize(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}

	m_colorTexture->SetUVRepeat(repeatU, repeatV);

	return true;
}

bool CPlane::LoadBumpTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, int repeatU, int repeatV)
{
	bool result;

	m_bumpTexture = new CTexture();
	if (!m_bumpTexture)
	{
		return false;
	}

	result = m_bumpTexture->Initialize(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}
	m_colorTexture->SetUVRepeat(repeatU, repeatV);

	return true;
}


void CPlane::Shutdown()
{
	if (m_bumpTexture)
	{
		m_bumpTexture->Shutdown();
		delete m_bumpTexture;
		m_bumpTexture = nullptr;
	}

	if (m_colorTexture)
	{
		m_colorTexture->Shutdown();
		delete m_colorTexture;
		m_colorTexture = nullptr;
	}

	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = nullptr;
	}

	return;
}

void  CPlane::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light)
{
	if (!m_model)
		return;


	CalculateWorldMatrix(m_matrix, m_rotation.x, m_rotation.y, m_rotation.z, m_sizeX, m_sizeY, 1.0f);
	m_model->Render(deviceContext);
	//CShaderManager::getInstance().RenderColorShader(deviceContext, m_model->GetIndexCount(), m_matrix, viewMatrix, projectionMatrix, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	CShaderManager::getInstance().RenderTextureShader(deviceContext, m_model->GetIndexCount(), m_matrix, viewMatrix, projectionMatrix, m_colorTexture->GetTextureData());

	return;
}
//******************************************************************************
//	End of file.
//******************************************************************************