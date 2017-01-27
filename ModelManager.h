//*****************************************************************************
//!	@file	ModelManager.h
//!	@brief	���f���Ǘ��N���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************
# ifndef __GM31_MODEL_MANAGER__
# define __GM31_MODEL_MANAGER__

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
# include "ModelClass.h"
# include <string.h>

//=============================================================================
//!	@class	ModelManager
//!	@brief	���f���Ǘ��N���X
//=============================================================================
class CModelManager
{
public:

	//���f��ID
	enum MODEL_ID
	{
		MODEL_BLOCK,
		MODEL_HOOK,
		MODEL_BEAD,
		MODEL_SACK_NORMAL,			//�v���C���[�̃��f��
		MODEL_SACK_SQUASH,
		MODEL_SACK_JUMP,
		MODEL_SACK_FALL,

		MODEL_MAX				//���f���̍ő吔
	};

	static CModelManager& getInstance()
	{
		static CModelManager* pInstance = new CModelManager;
		return *pInstance;
	}

	~CModelManager(void);									//�f�X�g���N�^

	bool InitializeModels(HWND hwnd);

	void Shutdown(void);
	void ReleaseTitleModels(void);
	void ReleaseSceneModels(void);

	CModel::ModelType* GetModel(MODEL_ID modelId);			//���f����߂��֐�

private:
	CModelManager(void);
	CModelManager(const CModelManager& other);
	CModelManager& operator=(const CModelManager& other);

	bool LoadModel(char* filename, CModel::ModelType* model);

private:
	CModel::ModelType* m_modelList[MODEL_MAX];				//���f���f�[�^�̔z��
	char* m_modelName[MODEL_MAX];							//���f���̃t�@�C����
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************
