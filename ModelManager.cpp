//*****************************************************************************
//!	@file	ModelManager.cpp
//!	@brief	���f���Ǘ��N���X�̊֐��Q
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
# include "ModelManager.h"
# include "D3DClass.h"
# include <string>

//-----------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPD3DXMESH ModelManager::models[ModelManager::MODEL_MAX];

static CModel::ModelType* modelList[MODEL_MAX];				//���f���f�[�^�̔z��
static LPCSTR modelName[MODEL_MAX];							//���f���̃t�@�C����


//==============================================================================
//!	@fn		ModelManager
//!	@brief	���f���Ǘ��N���X�̃R���X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
CModelManager::CModelManager()
{
	//�e�N�X�`�����p�̔z��
	char* temp_modelName[MODEL_MAX];

	//�|�C���^������������
	for (int modelNo = 0; modelNo < MODEL_MAX; modelNo++)
	{
		modelList[modelNo] = nullptr;
	}

	//�e�N�X�`��������͂���
	temp_modelName[MODEL_BLOCK]			= "Resources/Model/block.txt";
	temp_modelName[MODEL_HOOK]			= "Resources/Model/hook.txt";
	temp_modelName[MODEL_BEAD]			= "Resources/Model/bead.txt";
	temp_modelName[MODEL_SACK_NORMAL]	= "Resources/Model/Player/sack_normal.txt";
	temp_modelName[MODEL_SACK_SQUASH]	= "Resources/Model/Player/sack_squash.txt";
	temp_modelName[MODEL_SACK_JUMP]		= "Resources/Model/Player/sack_stretch_down.txt";
	temp_modelName[MODEL_SACK_FALL]		= "Resources/Model/Player/sack_stretch_up.txt";


	//�N���X�̕ϐ��ɃR�s�[����
	memcpy_s(modelList, sizeof(char*) * MODEL_MAX, temp_modelName, sizeof(char*) * MODEL_MAX);
}

//==============================================================================
//!	@fn		~ModelManager
//!	@brief	���f���Ǘ��N���X�̃f�X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
CModelManager::~CModelManager()
{
	//��
}

//==============================================================================
//!	@fn		Init
//!	@brief	�e�N�X�`���Ǘ��N���X�̏����֐�
//!	@param	HWND	�E�C���h�[�n���h��
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
bool CModelManager::LoadModels(HWND hwnd)
{
	//�e�N�X�`�������[�h����
	for (int modelNo = 0; modelNo < MODEL_MAX; modelNo++)
	{

	}
	return true;
}

//==============================================================================
//!	@fn		GetModel
//!	@brief	���f���̃|�C���^��߂��֐�
//!	@param	�Ȃ�
//!	@retval	LPD3DXMESH�@�@���f���̃|�C���^
//!	@note	
//==============================================================================
LPD3DXMESH ModelManager::GetModel(MODEL_ID modelId)
{
	return models[modelId];
}

//==============================================================================
//  �֐���        LoadModel
//  ����          ���f���f�[�^�̃��[�h�֐�
//------------------------------------------------------------------------------
//	����
//          char*                 filename     �@�@���f���t�@�C���ւ̃|�C���^
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CModelManager::LoadModel(char* filename, CModel::ModelType* model)
{
	ifstream fin;
	char input;
	int i;

	//���f���t�@�C����ǂݍ���
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

	//���f���f�[�^�����o��
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
