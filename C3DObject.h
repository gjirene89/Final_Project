//*****************************************************************************
//!	@file	C3DGameObject.h
//!	@brief	3D�Q�[���I�u�W�F�N�g�N���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_C3DOBJECT__
#define __GM31_C3DOBJECT__

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
#include	"GameObjectBase.h"

//=============================================================================
//!	@class	C3DObject
//!	@brief	3D�Q�[���I�u�W�F�N�g�̃x�[�X
//=============================================================================
class C3DObject : public CGameObjectBase
{
protected:
	D3DXMATRIX			matrix;					//�ϊ��s��
	D3DXVECTOR3			WorldPos;				//���[���h�̈ʒu
	D3DXVECTOR3			LocPos;					//���[�J���̈ʒu
	LPD3DXMESH			mesh;					// ���b�V���C���^�[�t�F�C�X
	D3DMATERIAL9		*material;				//�}�e���A��

public:
	C3DObject(GAMEOBJTYPE gameObjType);			//�R���X�g���N�^
	~C3DObject(void);							//�f�X�g���N�^

	void RenderAxis(void);						//�R���̕`��֐�
	void RenderWithAxis(void);					//�R���t���̕`��֐�
	//void RenderWithBS(void);					//�o�E���f�B���O�X�t�B�A�t���̕`��

	inline virtual void Input(void);			//���͊֐�
	inline virtual void Init(void);				//�������֐�
	inline virtual void Action(void);			//�����֐�
	inline virtual void Render(void);			//�`��֐�
	inline virtual void PostAction(void);		//�㏈���֐�
	
	void InitMaterial(void);							//�}�e���A���̏������֐�

	void SetMatrix(D3DXMATRIX newMatrix);		//�}�g���b�N�X�̏����Z�b�g����֐�
	void SetPosition(D3DXVECTOR3 position);		//�ʒu��ݒ肷��֐�
	void SetMesh(LPD3DXMESH mesh);
	void SetSize(D3DXVECTOR3 size);

	//�}�e���A��
	void SetDiffuse(D3DCOLORVALUE diffuse);				//�g�U�F�̐ݒ�֐�
	void SetAmbient(D3DCOLORVALUE ambient);				//���F�̐ݒ�֐�
	void SetSpecular(D3DCOLORVALUE specular);			//���ːF�̐ݒ�֐�
	void SetEmissive(D3DCOLORVALUE emissive);			//���s�F�̐ݒ�֐�

	

	LPD3DXMESH GetMesh(void);					//���b�V����n���֐�
	D3DXVECTOR3 GetRotX(void);					//�I�u�W�F�N�g��X����]��߂��֐�
	D3DXVECTOR3 GetRotY(void);					//�I�u�W�F�N�g��Y����]��߂��֐�
	D3DXVECTOR3 GetRotZ(void);					//�I�u�W�F�N�g��Z����]��߂��֐�
	D3DXVECTOR3 GetLocPos(void);				//�I�u�W�F�N�g�̃��[�J�����W��߂��֐�
	D3DXVECTOR3 GetWorldPos(void);				//�I�u�W�F�N�g�̃��[���h���W��߂��֐�
	D3DXMATRIX  GetMatrix(void);				//�I�u�W�F�N�g�̕ϊ��s���߂��֐�

};

#endif
//******************************************************************************
//	End of file.
//******************************************************************************