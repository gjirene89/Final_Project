//************************************************************************//
//	GameObjectBase.h
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

#ifndef __GAME_OBJECT_BASE_H__
#define __GAME_OBJECT_BASE_H__

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

using namespace std;
using namespace DirectX;

#include "TextureClass.h"

//=======================================================================//
//	�}�N���萔
//=======================================================================//
enum GAMEOBJTYPE
{
	GOBJ_NONE,
	GOBJ_CAMERA,			//�J�����@�I�u�W�F�N�g
	GOBJ_PLAYER,			//�v���C���[�@�I�u�W�F�N�g
	GOBJ_UI,				//UI
	GOBJ_BOUNDS,			//���E���@�I�u�W�F�N�g
	GOBJ_BLOCK,				//���ā[�W�u���b�N
	GOBJ_SACK,
	GOBJ_GOAL,
	GOBJ_BEAD,
	GOBJ_SKYDOME,

	GAMEOBJ_MAX				//�I�u�W�F�N�g�̍ő吔
};

/*
//�I�u�W�F�N�g�̏��
enum OBJ_STATE
{
	STATE_ALIVE,			//�����Ă���
	STATE_DEAD,				//����ł���

	STATE_MAX				//�ő��Ԑ�

};
*/
//=============================================================================
//
//	�N���X
//
//=============================================================================

//=============================================================================
//!	@class	CGameObjectBase
//!	@brief	�Q�[���I�u�W�F�N�g�̃x�[�X
//=============================================================================

class CGameObjectBase
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
	CGameObjectBase(void);
	CGameObjectBase(GAMEOBJTYPE objType);
	CGameObjectBase(const CGameObjectBase& other);
	~CGameObjectBase(void);

	virtual bool Initialize(ID3D11Device* device, char* modelFilename);
	virtual void Shutdown(void);

	virtual void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	virtual void Render(ID3D11DeviceContext* deviceContext, ID3D11Buffer* vertexBuffer);

	virtual void Initialize(void);
	virtual void Input(void);
	virtual void Action(void);
	virtual void PostAction(void);

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	bool LoadColorMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename);
	bool LoadColorMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, int vRepeat, int uRepeat);
	bool LoadBumpMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* bumpMapFilename);
	bool LoadBumpMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* bumpMapFilename, int vRepeat, int uRepeat);
	bool LoadSpecMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* specMapFilename);
	bool LoadSpecMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* specMapFilename, int vRepeat, int uRepeat);

	//�擾�֐�

	CTexture::TextureData GetColorTexture(void);
	CTexture::TextureData GetBumpTexture(void);
	CTexture::TextureData GetSpecTexture(void);

	int GetVertexCount(void);
	int GetIndexCount(void);
	ModelType* GetModelType(void) { return m_model; };

	void GetPosition(float& x, float& y, float& z);
	void GetRotation(float& x, float& y, float& z);

	void CalculateWorldMatrix(XMMATRIX& worldMatrix);

	//�|�C���^�p

	CGameObjectBase* GetNextObj();						//���̃I�u�W�F�N�g�̃f�[�^��߂��֐�
	void SetNextObj(CGameObjectBase* nextObj);			//���̃I�u�W�F�N�g�̃|�C���^���Z�b�g����֐�

private: 
	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers(void);
	void RenderBuffersIndex(ID3D11DeviceContext* deviceContext);
	void RenderBuffersIndex(ID3D11DeviceContext* deviceContext, ID3D11Buffer* vertexBuffer);

	void ReleaseTexture(void);

	bool LoadModel(char* filename);
	void ReleaseModel(void);


private:
	GAMEOBJTYPE			m_objType;							//�Q�[���I�u�W�F�N�g�̎��
	bool				m_isHidden;						//true: �`�悵�Ȃ�		false�F�`�悷��
	CGameObjectBase*	m_pNextObj;						//���̃I�u�W�F�N�g�ւ̃|�C���^

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	int m_vertexCount;
	int m_indexCount;

	float m_positionX;
	float m_positionY;
	float m_positionZ;

	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;

	ModelType* m_model;

	CTexture* m_Texture;
	CTexture* m_BumpMap;
	CTexture* m_SpecMap;

};

#endif


//******************************************************************************
//	End of file.
//******************************************************************************
