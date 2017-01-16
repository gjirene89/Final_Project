//*****************************************************************************
//!	@file	C3DGameObject.h
//!	@brief	3D�Q�[���I�u�W�F�N�g�N���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
#include	"C3DObject.h"
#include	"CDirectxGraphics.h"
#include	"mathutil.h"
#include	"Debug.h"

//==============================================================================
//!	@fn		C3DObject
//!	@brief	3D�Q�[���I�u�W�F�N�g�x�[�X�̃R���X�g���N�^
//!	@param	3D�Q�[���I�u�W�F�N�g�̎��
//!	@retval	�Ȃ�
//==============================================================================
C3DObject::C3DObject(GAMEOBJTYPE gameObjType) : CGameObjectBase(gameObjType)
{
	//�ϊ��s��̏�����
	D3DXMatrixIdentity(&matrix);
	texture = nullptr;
	mesh = nullptr;
	material = new D3DMATERIAL9;				//�}�e���A���̏�����
	
}

//==============================================================================
//!	@fn		�`C3DObject
//!	@brief	3D�Q�[���I�u�W�F�N�g�x�[�X�̃f�X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
C3DObject::~C3DObject(void)
{	
	// �}�e���A���I�u�W�F�N�g�̉��
	if (material != nullptr)
	{	
		delete[] material;
		material = nullptr;
	}

	// ���b�V�����
	if (mesh != nullptr)
	{		
		mesh->Release();
		mesh = nullptr;
	}

	//�e�N�X�`�����
	if (texture != nullptr)
	{
		texture->Release();
		texture = nullptr;
	}
}

//==============================================================================
//!	@fn		Init
//!	@brief	3D�Q�[���I�u�W�F�N�̏������֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::Init(void)
{
	//���͋�
}

//==============================================================================
//!	@fn		Input
//!	@brief	3D�Q�[���I�u�W�F�N�̓��͊֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::Input(void)
{
	//���͋�
}

//==============================================================================
//!	@fn		Action
//!	@brief	3D�Q�[���I�u�W�F�N�̏����֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::Action(void)
{
	//���͋�
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	3D�Q�[���I�u�W�F�N�̌㏈���֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::PostAction(void)
{
	//���͋�
}

//==============================================================================
//!	@fn		Render
//!	@brief	3D���f����`�悷��
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void C3DObject::Render(void)
{
	if (mesh == nullptr || isHidden == true)
		return;

	CDirectXGraphics::GetDXDevice()->SetMaterial(material);
	CDirectXGraphics::GetDXDevice()->SetTexture(0, texture);
	CDirectXGraphics::GetDXDevice()->SetTransform(D3DTS_WORLD, &matrix);
	mesh->DrawSubset(0);

}

//==============================================================================
//!	@fn		RenderAxis
//!	@brief	3����`�悷��
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void C3DObject::RenderAxis(void)
{
	struct VERTEXDATA{
		float		x, y, z;
		D3DCOLOR	color;
	};

	// �R���̒��_�f�[�^
	struct	VERTEXDATA	linevertices[6] = {
		-400, 0, 0, D3DCOLOR_XRGB(255, 0, 0),	// �w���n�_ ��
		400, 0, 0, D3DCOLOR_XRGB(255, 0, 0),	// �w���I�_ ��
		0, -400, 0, D3DCOLOR_XRGB(0, 255, 0),	// �x���n�_ ��
		0, 400, 0, D3DCOLOR_XRGB(0, 255, 0),	// �x���I�_ ��
		0, 0, -400, D3DCOLOR_XRGB(0, 0, 255),	// �y���n�_ ��
		0, 0, 400, D3DCOLOR_XRGB(0, 0, 255)		// �y���I�_ ��
	};

	CDirectXGraphics::GetDXDevice()->SetTexture(0,nullptr);
	CDirectXGraphics::GetDXDevice()->SetFVF(FVF_TLVERTEX3D);	// ���_�t�H�[�}�b�g���Z�b�g
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_LIGHTING, false);	//   �����v�Z�I�t�i�����v�Z��؂��DIFFUSE�F�����̂܂܂ł�j

	CDirectXGraphics::GetDXDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 3, &linevertices[0], sizeof(VERTEXDATA));	// �R����`��
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_LIGHTING, true);	//   �����v�ZON
}

//==============================================================================
//!	@fn		RenderWithAxis
//!	@brief	X�t�@�C���`��(3����`�悷��)
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void C3DObject::RenderWithAxis(void)
{
	//���f���̕`��
	C3DObject::Render();
	//3���̕`��
	RenderAxis();
}

//==============================================================================
//!	@fn		GetMesh
//!	@brief	3D�Q�[���I�u�W�F�N�̃��b�V����߂��֐�
//!	@param	�Ȃ�
//!	@retval	LPD3DXMESH		�I�u�W�F�N�g�̃��b�V��
//==============================================================================
LPD3DXMESH C3DObject::GetMesh(void)
{
	return mesh;
}

void C3DObject::SetMesh(LPD3DXMESH mesh_)
{
	mesh = mesh_;
}

void C3DObject::SetSize(D3DXVECTOR3 size)
{
	SetSizeMatrix(matrix, size);
}

//==============================================================================
//!	@fn		GetRotX
//!	@brief	�I�u�W�F�N�g��X����]��߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetRotX(void)
{
	//�ϊ��s�񂩂�X����]�̏���߂�
	return{ matrix._11, matrix._12, matrix._13 };
}

//==============================================================================
//!	@fn		GetRotY
//!	@brief	�I�u�W�F�N�g��Z����]��߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetRotY(void)
{
	//�ϊ��s�񂩂�Y����]�̏���߂�
	return{ matrix._21, matrix._22, matrix._23 };
}

//==============================================================================
//!	@fn		GetRotZ
//!	@brief	�I�u�W�F�N�g��Z����]��߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetRotZ(void)
{
	//�ϊ��s�񂩂�Z����]�̏���߂�
	return{ matrix._31, matrix._32, matrix._33 };
}

//==============================================================================
//!	@fn		GetLocPos
//!	@brief	�I�u�W�F�N�g�̃��[�������W��߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetLocPos(void)
{
	//�ϊ��s�񂩂烍�[�J�����W�̏���߂�
	//return{ matrix._41, matrix._42, matrix._43 };
	return LocPos;
}

//==============================================================================
//!	@fn		GetWorldPos
//!	@brief	�I�u�W�F�N�g�̃��[���h���W��߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
D3DXVECTOR3 C3DObject::GetWorldPos(void)
{
	//���[���h���W��߂�
	return{ matrix._41, matrix._42, matrix._43 };
}

//==============================================================================
//!	@fn		GetMatrix
//!	@brief	�I�u�W�F�N�g�̕ϊ��s���߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
D3DXMATRIX C3DObject::GetMatrix(void)
{
	//�ϊ��s���߂�
	return matrix;
}

//==============================================================================
//!	@fn		SetMatrix
//!	@brief	�}�g���b�N�X�̏��̃Z�b�g�֐�
//!	@param�@D3DXMATRIX�@matrix
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::SetMatrix(D3DXMATRIX matrix_)
{
	matrix = matrix_;
}

//==============================================================================
//!	@fn		SetPosition
//!	@brief�@�I�u�W�F�N�g�̈ʒu��ݒ肷��
//!	@param�@D3DXVECTOR3 position
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::SetPosition(D3DXVECTOR3 position)
{
	matrix._41 = position.x;
	matrix._42 = position.y;
	matrix._43 = position.z;
}

//==============================================================================
//!	@fn		InitMaterial
//!	@brief	�}�e���A�����f�t�H���g�F�ɂ���
//!	@param�@�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::InitMaterial(void)
{
	if (material == nullptr)		material = new D3DMATERIAL9;				//�}�e���A���̏�����

	//�}�e���A�����f�t�H���g�l�ɂ���
	material->Diffuse.r = 1.0f;
	material->Diffuse.g = 1.0f;
	material->Diffuse.b = 1.0f;
	material->Diffuse.a = 1.0f;

	material->Ambient.r = 0.0f;
	material->Ambient.g = 0.0f;
	material->Ambient.b = 0.0f;
	material->Ambient.a = 0.0f;

	material->Specular.r = 1.0f;
	material->Specular.g = 1.0f;
	material->Specular.b = 1.0f;
	material->Specular.a = 1.0f;

	material->Emissive.r = 0.0f;
	material->Emissive.g = 0.0f;
	material->Emissive.b = 0.0f;
	material->Emissive.a = 1.0f;
}

//==============================================================================
//!	@fn		SetDiffuse
//!	@brief	�}�e���A�����g�U�F��ݒ肷��
//!	@param  D3DCOLORVALUE	color		�g�U�F
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::SetDiffuse(D3DCOLORVALUE color)
{
	//�g�U�F��ݒ肷��
	material->Diffuse = color;
}

//==============================================================================
//!	@fn		SetAmbient
//!	@brief	�}�e���A�����g�U�F��ݒ肷��
//!	@param  D3DCOLORVALUE	color		�g�U�F
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::SetAmbient(D3DCOLORVALUE color)
{
	//���F��ݒ肷��
	material->Ambient = color;
}

//==============================================================================
//!	@fn		SetSpecular
//!	@brief	�}�e���A�����g�U�F��ݒ肷��
//!	@param  D3DCOLORVALUE	color		���ːF
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::SetSpecular(D3DCOLORVALUE color)
{
	//���ːF��ݒ肷��
	material->Specular = color;
}

//==============================================================================
//!	@fn		SetEmissive
//!	@brief	�}�e���A�����g�U�F��ݒ肷��
//!	@param  D3DCOLORVALUE	color		�����F
//!	@retval	�Ȃ�
//==============================================================================
void C3DObject::SetEmissive(D3DCOLORVALUE color)
{
	//���s�F��ݒ肷��
	material->Emissive = color;
}


//******************************************************************************
//	End of file.
//******************************************************************************