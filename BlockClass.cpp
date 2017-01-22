//*****************************************************************************
//	BlockClass.cpp
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************

//==============================================================================
//		インクルード
//==============================================================================
# include "BlockClass.h"
# include "ShaderManagerClass.h"
# include "MathUtility.h"
//# include "CDirectxGraphics.h"


//==============================================================================
//!	@fn		CBlock
//!	@brief	ブロックのコンストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CBlock::CBlock(BLOCK_COLOR color) : CGameObjectBase(GOBJ_BLOCK)
{
	//メッシュの作成
	//D3DXCreateBox(CDirectXGraphics::GetDXDevice(), BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE*2, &mesh, nullptr);
	m_model = nullptr;

	//色初期化
	//m_color = color;

	//マテリアルの初期化
	//InitMaterial();

	//色を更新する
	SetColor(color);

}


//==============================================================================
//!	@fn		~CBlock
//!	@brief	ブロックのデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CBlock::~CBlock(void)
{
	//今は空
}

bool CBlock::InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;

	m_model = new CModel;
	if (!m_model)
	{
		return false;
	}

	result = m_model->Initialize(device, "Resources/Model/block.txt");
	if (!result)
	{
		return false;
	}

	m_model->LoadColorMap(device, deviceContext, "Resources/Texture/blockColor.tga");
	m_model->LoadBumpMap(device, deviceContext, "Resources/Texture/blockBump.tga");

	return true;
}

void CBlock::Shutdown()
{
	m_model->Shutdown();

	return;
}

void  CBlock::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	if (!m_model)
		return;

	//TranslateMatrix(worldMatrix, XMFLOAT3(m_positionX, m_positionY, m_positionZ));

	CalculateWorldMatrix(worldMatrix);
	m_model->Render(deviceContext);// , worldMatrix, viewMatrix, projectionMatrix);
								   //CShaderManager::getInstance().RenderBumpMapShader(deviceContext, m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_model->GetColorTexture(), m_model->GetBumpTexture(), );
	CShaderManager::getInstance().RenderTextureShader(deviceContext, m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_model->GetColorTexture());
	//CShaderManager::getInstance().RenderColorShader(deviceContext, m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	return;
}
//==============================================================================
//!	@fn		GetColor
//!	@brief	ブロックの色を戻す関数
//!	@param	なし
//!	@retval	BLOCK_COLOR		ブロックの色
//!	@note	
//==============================================================================
//CBlock::BLOCK_COLOR CBlock::GetColor(void)
//{
//	return m_color;
//}


void CBlock::SetColor(BLOCK_COLOR colorID)
{
	switch (colorID)
	{
	case BLOCK_GREEN:
		m_color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		//m_model->LoadColorMap()
		break;

	case BLOCK_RED:
		m_color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		break;

	case BLOCK_INVISIBLE:
		m_color = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
		break;
	}
}
//******************************************************************************
//	End of file.
//******************************************************************************