//*****************************************************************************
//!	@file	ModelManager.cpp
//!	@brief	モデル管理クラスの関数群
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
# include "ModelManager.h"
# include "D3DClass.h"
# include <string>

//-----------------------------------------------------------------------------
//	グローバル変数
//-----------------------------------------------------------------------------
LPD3DXMESH ModelManager::models[ModelManager::MODEL_MAX];

static CModel::ModelType* modelList[MODEL_MAX];				//モデルデータの配列
static LPCSTR modelName[MODEL_MAX];							//モデルのファイル名


//==============================================================================
//!	@fn		ModelManager
//!	@brief	モデル管理クラスのコンストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CModelManager::CModelManager()
{
	//テクスチャ名用の配列
	char* temp_modelName[MODEL_MAX];

	//ポインタを初期化する
	for (int modelNo = 0; modelNo < MODEL_MAX; modelNo++)
	{
		modelList[modelNo] = nullptr;
	}

	//テクスチャ名を入力する
	temp_modelName[MODEL_BLOCK]			= "Resources/Model/block.txt";
	temp_modelName[MODEL_HOOK]			= "Resources/Model/hook.txt";
	temp_modelName[MODEL_BEAD]			= "Resources/Model/bead.txt";
	temp_modelName[MODEL_SACK_NORMAL]	= "Resources/Model/Player/sack_normal.txt";
	temp_modelName[MODEL_SACK_SQUASH]	= "Resources/Model/Player/sack_squash.txt";
	temp_modelName[MODEL_SACK_JUMP]		= "Resources/Model/Player/sack_stretch_down.txt";
	temp_modelName[MODEL_SACK_FALL]		= "Resources/Model/Player/sack_stretch_up.txt";


	//クラスの変数にコピーする
	memcpy_s(modelList, sizeof(char*) * MODEL_MAX, temp_modelName, sizeof(char*) * MODEL_MAX);
}

//==============================================================================
//!	@fn		~ModelManager
//!	@brief	モデル管理クラスのデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CModelManager::~CModelManager()
{
	//空
}

//==============================================================================
//!	@fn		Init
//!	@brief	テクスチャ管理クラスの初期関数
//!	@param	HWND	ウインドーハンドル
//!	@retval	なし
//!	@note	
//==============================================================================
bool CModelManager::LoadModels(HWND hwnd)
{
	//テクスチャをロードする
	for (int modelNo = 0; modelNo < MODEL_MAX; modelNo++)
	{

	}
	return true;
}

//==============================================================================
//!	@fn		GetModel
//!	@brief	モデルのポインタを戻す関数
//!	@param	なし
//!	@retval	LPD3DXMESH　　モデルのポインタ
//!	@note	
//==============================================================================
LPD3DXMESH ModelManager::GetModel(MODEL_ID modelId)
{
	return models[modelId];
}

//==============================================================================
//  関数名        LoadModel
//  説明          モデルデータのロード関数
//------------------------------------------------------------------------------
//	引数
//          char*                 filename     　　モデルファイルへのポインタ
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CModelManager::LoadModel(char* filename, CModel::ModelType* model)
{
	ifstream fin;
	char input;
	int i;

	//モデルファイルを読み込む
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

	model = new CModel::ModelType[m_vertexCount];
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

	//モデルデータを取り出す
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	fin.close();

	return true;
}

//******************************************************************************
//	End of file.
//******************************************************************************
