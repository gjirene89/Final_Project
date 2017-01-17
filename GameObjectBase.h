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

//=======================================================================//
//	�N���X��		CGameObjectBase
//=======================================================================//
class CGameObjectBase
{

public: 
	CGameObjectBase(void);
	CGameObjectBase(GAMEOBJTYPE objType);
	CGameObjectBase(const CGameObjectBase& other);
	~CGameObjectBase(void);


	virtual bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext) = 0;
	virtual void Shutdown() = 0;

	virtual void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)=0;
	//virtual void Render(ID3D11DeviceContext* deviceContext, ID3D11Buffer* vertexBuffer);

	virtual void Initialize(void);
	virtual void Input(void);
	virtual void Action(void);
	virtual void PostAction(void);

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void GetPosition(float& x, float& y, float& z);
	void GetRotation(float& x, float& y, float& z);

	void CalculateWorldMatrix(XMMATRIX& worldMatrix);

	//�|�C���^�p

	CGameObjectBase* GetNextObj();						//���̃I�u�W�F�N�g�̃f�[�^��߂��֐�
	void SetNextObj(CGameObjectBase* nextObj);			//���̃I�u�W�F�N�g�̃|�C���^���Z�b�g����֐�

private: 


protected:
	GAMEOBJTYPE			m_objType;							//�Q�[���I�u�W�F�N�g�̎��
	bool				m_isHidden;						//true: �`�悵�Ȃ�		false�F�`�悷��
	CGameObjectBase*	m_pNextObj;						//���̃I�u�W�F�N�g�ւ̃|�C���^

	float m_positionX;
	float m_positionY;
	float m_positionZ;

	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;
};

#endif


//******************************************************************************
//	End of file.
//******************************************************************************
