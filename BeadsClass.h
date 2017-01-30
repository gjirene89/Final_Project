//************************************************************************//
//	BeadsClass.h
//	2017-01-23
//	Irene Gersenowies
//************************************************************************//

#ifndef __CBEADS_H__
#define __CBEADS_H__

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
//# include "C3DObject.h"
# include "GameObjectBase.h"
# include "HitBaseClass.h"
# include "ModelClass.h"

//-----------------------------------------------------------------------------
//	�}�N���萔
//-----------------------------------------------------------------------------
//# define	BLOCK_SIZE	10.0f

//=============================================================================
//!	@class	CBeads
//!	@brief �S�[���N���X
//=============================================================================
class CBeads : public CGameObjectBase
{
public:

	CBeads();							//�R���X�g���N�^
	CBeads(const CBeads& other) {};
	~CBeads(void);						//�f�X�g���N�^

	virtual void Initialize(XMMATRIX& parent);							//�������֐�
	virtual void Action(XMMATRIX& parent);							//�����֐�
	virtual void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light);							//�`��֐�
	virtual void PostAction(void);						//�㏈���֐�

	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown(void);

	XMFLOAT3 GetResForce(void);						//���͂�߂��֐�
	void SetOppositeForce(XMFLOAT3 pullForce);		//��������͂��Z�b�g����֐�
	void SetSpringForce(XMFLOAT3 force);				//�o�l�̗͂��Z�b�g����
	void SetLocalPosition(float posX, float posY, float posZ);				//���[�J���ʒu���Z�b�g����

	void LockAngle(float angle);
	void UpdateAngle(XMFLOAT3 orientation);
	void LockBead(XMFLOAT3 hookPos);
	void UnLockBead(void);

private:
	
	float	m_k;
	float	m_lenght;
	float	m_angle;						//�p�x
	//D3DXVECTOR3 orientation;			//�o�l�̌���
	bool	m_isLocked;					//�ʒu���Œ肳��Ă��邩�ǂ���
	bool	m_isAngleLocked;
	//D3DXMATRIX	LocalMat;				//���[�J���s��
//	XMMATRIX		m_LocalMat;
	CHit_Base* m_pHit;					//�����蔻��

	float m_gravForce;					//�d��
	XMFLOAT3 m_pullForce;				//���������
	XMFLOAT3 m_resForce;				//����
	XMFLOAT3 m_springForce;			//�o�l�̗�

	XMFLOAT3 m_accel;					//�����x
	XMFLOAT3 m_velocity;				//���x
	
	static CModel* m_beadModel;			//�ʂ̃��f��

	void CalcResForce(void);			//���͂����߂�֐�
	void SetHit(void);					//�����蔻��̏����Z�b�g����

};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************