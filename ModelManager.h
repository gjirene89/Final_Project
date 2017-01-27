//*****************************************************************************
//!	@file	ModelManager.h
//!	@brief	モデル管理クラス
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************
# ifndef __GM31_MODEL_MANAGER__
# define __GM31_MODEL_MANAGER__

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
# include "ModelClass.h"
# include <string.h>

//=============================================================================
//!	@class	ModelManager
//!	@brief	モデル管理クラス
//=============================================================================
class CModelManager
{
public:

	//モデルID
	enum MODEL_ID
	{
		MODEL_BLOCK,
		MODEL_HOOK,
		MODEL_BEAD,
		MODEL_SACK_NORMAL,			//プレイヤーのモデル
		MODEL_SACK_SQUASH,
		MODEL_SACK_JUMP,
		MODEL_SACK_FALL,

		MODEL_MAX				//モデルの最大数
	};

	static CModelManager& getInstance()
	{
		static CModelManager* pInstance = new CModelManager;
		return *pInstance;
	}

	~CModelManager(void);									//デストラクタ

	bool InitializeModels(HWND hwnd);

	void Shutdown(void);
	void ReleaseTitleModels(void);
	void ReleaseSceneModels(void);

	CModel::ModelType* GetModel(MODEL_ID modelId);			//モデルを戻す関数

private:
	CModelManager(void);
	CModelManager(const CModelManager& other);
	CModelManager& operator=(const CModelManager& other);

	bool LoadModel(char* filename, CModel::ModelType* model);

private:
	CModel::ModelType* m_modelList[MODEL_MAX];				//モデルデータの配列
	char* m_modelName[MODEL_MAX];							//モデルのファイル名
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************
